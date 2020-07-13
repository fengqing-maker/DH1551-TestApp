#include "USBBackDoor.h"
#include "stdio.h"
#include "adi_flash.h"
#include "adi_toolset.h"
#include "adi_secure.h"
#include "adi_os.h"
#include "MSWindows.h"
#include "FactoryTestInit.h"

#define CRC_FLAG_32 (0xEDB88320)

static void USBDviceCheckCallBack(ADIFSEvent_E eType, int nDeviceId, const void * pvEventData, void * pvUserData);
extern int MSWideChar2MultiByte(const char* wcStr, char *MultiStr, int nMultiStrLen);

//DataLen (4B) + (Start Addr (4B) + UpgradeData (nB)) + CRC (4B)
USBBackDoor::USBBackDoor(unsigned int unByteFlag, unsigned int unFlashSize, char *pBacDoorFile):
APSafeThread(3 * 17, 16 * 1024, "USBBackDoor", strlen("USBBackDoor")),
m_unByteFlag(unByteFlag),m_unFlashSize(unFlashSize)
{
	m_unUSBFlush = 0;
	memset(m_acBackDoorFileName, 0, sizeof(m_acBackDoorFileName));
	if(pBacDoorFile != NULL)
	{
		int nCopyLen = (strlen(pBacDoorFile) > sizeof(m_acBackDoorFileName) - 1) ? (sizeof(m_acBackDoorFileName) - 1) : strlen(pBacDoorFile);
		memcpy(m_acBackDoorFileName, pBacDoorFile, nCopyLen);
	}
	
	m_unUSBStatus = EM_ADIFS_EVENT_UNKNOWN;

	ADIFSAddCallback(USBDviceCheckCallBack, this);

	StartRun();
}

USBBackDoor::~USBBackDoor()
{
}

void USBBackDoor::OnceProcess()
{
	if(m_unUSBStatus == EM_ADIFS_EVENT_READY && m_unUSBFlush == 1)
	{
		StartUpgradeUSBFile();
	}

	ADIOSThreadSleep(1000);
}

unsigned int USBBackDoor::StartUpgradeUSBFile(void)
{
	unsigned int unRe = 0;
	ADI_HANDLE  hEcosFile = NULL;
	unsigned int unBufLen = 0;
	unsigned char *pucTempBuf = NULL;
	unsigned int unStartAddr = 0;
	unsigned int unActReadLen = 0;
	unsigned int unRecordLen = 0;
	ADICHIPID_S sChip = { 0 };
	ADIGetChipID(&sChip);
	FactoryTestInterface *pFactoryTestInterface = GetFactoryTestInterface();

	do
	{
		hEcosFile = OpenFile(m_acBackDoorFileName, "rb+");
		if(hEcosFile == NULL)
		{			
			writeLog("[%s %d] Fail to OpenFile %s\r\n", __FUNCTION__, __LINE__, m_acBackDoorFileName);
			break;
		}
		
		if(pFactoryTestInterface != NULL)
		{
			pFactoryTestInterface->SetLedStatus(1);
		}
		
		if (0 != ADIFSSeek(hEcosFile, 0, ADIFS_SEEK_END))
		{
			writeLog("[%s %d] ADIFSSeek Fail\r\n", __FUNCTION__, __LINE__);
			break;
		}
		
		unBufLen = ADIFSTell(hEcosFile);
		if(unBufLen > m_unFlashSize + 16)
		{
			writeLog("[%s %d] unBufLen:0x%x error\r\n", __FUNCTION__, __LINE__, unBufLen);
			break;
		}

		pucTempBuf = (unsigned char*)ADIOSMalloc(unBufLen);
		if(pucTempBuf == 0)
		{
			writeLog("[%s %d] pucTempBuf 0 error,unBufLen:0x%x\n", __FUNCTION__, __LINE__, unBufLen);
			break;
		}
		
		ADIFSSeek(hEcosFile, 0, ADIFS_SEEK_SET);		
		unsigned int unActReadLen = (unsigned int )ADIFSRead(hEcosFile, (char*)pucTempBuf, unBufLen);		
		if(unBufLen != unActReadLen)
		{
			writeLog("[%s %d] unBufLen:0x%x, unActReadLen:0x%x error \n", __FUNCTION__, __LINE__, unBufLen, unActReadLen);
			break;
		}

		unRecordLen = (unsigned int)(pucTempBuf[0] << 24) | (pucTempBuf[1] << 16) | (pucTempBuf[2] << 8) | pucTempBuf[3];
		if(unRecordLen != unBufLen - 8)
		{
			writeLog("[%s %d] unBufLen:0x%x, unRecordLen:0x%x error \n", __FUNCTION__, __LINE__, unBufLen, unRecordLen);
			break;
		}

		if(CheckCRC32(pucTempBuf, unBufLen) == 0)
		{
			writeLog("[%s %d] CheckCRC32 error \n", __FUNCTION__, __LINE__);
			break;
		}

		unStartAddr = (unsigned int)(pucTempBuf[4] << 24) | (pucTempBuf[5] << 16) | (pucTempBuf[6] << 8) | pucTempBuf[7];
		if(unStartAddr + unRecordLen > m_unFlashSize + 8)
		{
			writeLog("[%s %d] unRecordLen:0x%x,unStartAddr:0x%x, m_unFlashSize:0x%x\r\n", __FUNCTION__, __LINE__, unRecordLen, unStartAddr, m_unFlashSize);
			break;
		}
		if (memcmp(&sChip.m_szChipID[4], &pucTempBuf[8], 4) == 0)
		{
			writeLog("[%s %d] unOrgChipID:0x%x error \n", __FUNCTION__, __LINE__);
			break;
		}
		else
		{
			pucTempBuf[8] = sChip.m_szChipID[4];
			pucTempBuf[9] = sChip.m_szChipID[5];
			pucTempBuf[10] = sChip.m_szChipID[6];
			pucTempBuf[11] = sChip.m_szChipID[7];

			unsigned int dwCRC32 = CalculateCRC32(pucTempBuf + 4, unBufLen - 8);
			pucTempBuf[unBufLen - 4] = (dwCRC32 >> 24) & 0xFF;
			pucTempBuf[unBufLen - 3] = (dwCRC32 >> 16) & 0xFF;
			pucTempBuf[unBufLen - 2] = (dwCRC32 >> 8) & 0xFF;
			pucTempBuf[unBufLen - 1] = dwCRC32 & 0xFF;

			ADI_HANDLE  hEcosFile2 = NULL;
			hEcosFile2 = OpenFile(m_acBackDoorFileName, "wb");
			ADIFSWrite(hEcosFile2, (char *)pucTempBuf, unBufLen);
			ADIFSClose(hEcosFile2);
		}
		if(ADIFlashWrite(unStartAddr, &pucTempBuf[12], unRecordLen - 8) != ADI_SUCCESS)
		{
			writeLog("[%s %d] ADIFlashWrite error \n", __FUNCTION__, __LINE__);
			break;
		}
		unRe = 1;
	}while(0);

	if(pucTempBuf != NULL)
	{
		ADIOSFree(pucTempBuf);
	}

	if(hEcosFile != NULL)
	{
		ADIFSClose(hEcosFile);
	}

	m_unUSBFlush =0;

	if(unRe == 1)
	{
		writeLog("[%s %d] WriteLen:0x%x,reboot... \n", __FUNCTION__, __LINE__, unBufLen - 4);		
		ADIOSThreadSleep(1000);
		ADISYSReboot();
	}
	else
	{
		writeLog("[%s %d] unRecordLen:0x%x,unStartAddr:0x%x,m_unFlashSize:0x%x\r\n", __FUNCTION__, __LINE__, unRecordLen, unStartAddr, m_unFlashSize);
		if(pFactoryTestInterface != NULL)
		{
			pFactoryTestInterface->SetLedStatus(0);
		}
	}

	return unRe;
}

void USBBackDoor::writeLog(char * format, ...)
{
	if(m_unUSBStatus == EM_ADIFS_EVENT_READY)
	{
		ADI_HANDLE hLogFile = 0;
		char acLoginfo[1024] = {0};
		va_list args;

		memset(acLoginfo, 0, sizeof(acLoginfo));

		va_start(args, format);
		vsprintf(acLoginfo, format, args);
		va_end(args);

		hLogFile = OpenFile("LogFile.txt", "ab+");
		if(0 != hLogFile)
		{
			printf("%s", acLoginfo);
			ADIFSWrite(hLogFile, acLoginfo, strlen(acLoginfo));
			ADIFSFlush(hLogFile);
			ADIFSClose(hLogFile);
		}
	}	
}

void USBBackDoor::USBMediaReady(unsigned int unUSBStatus, ADIFSDeviceInfo_S* psDeviceInfo)
{
	m_unUSBStatus = unUSBStatus;

	m_unUSBFlush = 1;

	memcpy(&m_stDeviceInfo, psDeviceInfo, sizeof(ADIFSDeviceInfo_S));
}

void USBBackDoor::USBMediaPlugOut(unsigned int unUSBStatus)
{
	m_unUSBStatus = unUSBStatus;
}

unsigned int USBBackDoor::GetUSBRootPath(char *pBuffer, int nLen)
{
	unsigned int unRe = 0;
	int nActLen = 0;

	if(m_unUSBStatus == EM_ADIFS_EVENT_READY)
	{
		if(m_unByteFlag == 1)
		{
			MSWideChar2MultiByte(m_stDeviceInfo.m_szMountPoint, pBuffer, nLen);
		}
		else
		{
			snprintf(pBuffer, nLen, "%s", m_stDeviceInfo.m_szMountPoint);
		}

		nActLen = strlen(pBuffer);
		if(nActLen < nLen)
		{
			if (pBuffer[nActLen] != '/')
			{
				pBuffer[nActLen] = '/';
				pBuffer[nActLen + 1] = '\0';
			}
		}
		unRe = strlen(pBuffer);
	}

	return unRe;
}

ADI_HANDLE USBBackDoor::OpenFile(char *pFileName, char *pOpenMode)
{
	ADI_HANDLE hLogFile = NULL;
	char acName[256] = {0};
	char wcName[512] = {0};
	char acMountPath[128] = {0};

	if(GetUSBRootPath(acMountPath, sizeof(acMountPath)) > 0)
	{
		snprintf(acName, sizeof(acName)-1, "%s%s", acMountPath, pFileName);
		if(m_unByteFlag == 1)
		{
			MSMultiByteToWideChar( 0, 0, acName, strlen(acName), (LPWSTR)wcName, sizeof(wcName) - 2);
		}
		else
		{
			snprintf(wcName, sizeof(wcName), "%s", acName);
		}

		hLogFile = ADIFSOpen((const char *)wcName, (const char *)pOpenMode);
	}

	return hLogFile;
}

unsigned int USBBackDoor::CalculateCRC32(unsigned char *pbData, unsigned int unLength)
{
	unsigned int ii = 0;
	unsigned int jj = 0;
	unsigned int dwCRC = 0;
	unsigned int dwCrc32 = 0xffffffff;

	for (ii = 0; ii<unLength; ii++)
	{
		for (jj = 0; jj<8; jj++)
		{
			if (((pbData[ii] >> (7 - jj)) & 0x01))
				dwCrc32 ^= 1;

			if (dwCrc32 & 1)
				dwCrc32 = ((dwCrc32 >> 1) ^ CRC_FLAG_32);
			else
				dwCrc32 >>= 1;
		}
	}

	for (ii = 0; ii<32; ii++)
	{
		if ((dwCrc32 >> ii) & 1)
		{
			dwCRC <<= 1;
			dwCRC |= 1;
		}
		else
		{
			dwCRC <<= 1;
		}
	}

	return dwCRC;
}

unsigned int USBBackDoor::CheckCRC32(unsigned char  *pbData, unsigned int unLength)
{
	unsigned int dwCRC32 = 0;
	unsigned int dwOrgCRC32 = 0;
	unsigned int unRet = 0;

	if (unLength < 8)
	{
		return unRet;
	}

	dwCRC32 = (unsigned int)((pbData[unLength - 4] << 24) | (pbData[unLength - 3] << 16) | (pbData[unLength - 2] << 8) | (pbData[unLength - 1]));
	
	dwOrgCRC32 = CalculateCRC32(pbData + 4, unLength - 8);
	
	if (dwOrgCRC32 == dwCRC32)
	{
		unRet = 1;
	}

	return unRet;
}

static void USBDviceCheckCallBack(ADIFSEvent_E eType, int nDeviceId, const void * pvEventData, void * pvUserData)
{
	USBBackDoor *pUSBBackDoor = (USBBackDoor*)pvUserData;

	if( pUSBBackDoor != NULL )
	{
		switch( eType )
		{
			case EM_ADIFS_EVENT_READY:
			{
				ADIFSDeviceInfo_S stDevInfo = { 0 };
				if (ADI_SUCCESS == ADIFSGetDeviceInfo((unsigned int)nDeviceId, &stDevInfo))
				{
					if(stDevInfo.m_eDeviceType == EM_ADIFS_DEVTYPE_VOLUME)
					{
						pUSBBackDoor->USBMediaReady(eType, &stDevInfo);
					}
				}
			}
			break;
			
			case EM_ADIFS_EVENT_PLUGOUT:
			{
				pUSBBackDoor->USBMediaPlugOut(eType);
			}
			break;
			
			default:
			break;
		}

		pUSBBackDoor->writeLog("-[%s,%d]***eType=%d***\n", __FUNCTION__, __LINE__, eType);
	}
}

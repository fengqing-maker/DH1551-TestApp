/*
 * OTASupport.cpp
 *
 *  Created on: 2015-8-20
 *      Author: Timothy
 */

#include <string.h>
#include "OTASupport.h"
#include "adi_flash.h"
#include "adi_toolset.h"
#include "adi_secure.h"
#include "adi_os.h"
#include "adi_castpal_bl.h"
#include "adi_irdeto_bl_v5.h"
#include "adi_irdeto_bl.h"
#include "FactoryTestInit.h"
#include "stdio.h"
#include "adi_tuner.h"
#include "GetOTASupport.h"
#include "adi_fs.h"

#define MAX_READ_OR_WRITE_FLASH_COUNT 3
#define CRC_FLAG 0xEDB88320
#define DATA_HEAD (16)
#define DATA_LEN_FLAG (4)
#define DATA_CRC_LEN (4)
#define MAX_CORE_FILED_SIZE (0x55000)
#define MAX_CORE_ONESEG_SIZE	( 0x60000 )
#define INIT (0xffffffffL)
#define XOROT (0xffffffffL)
#define USB_DEVICES_MAX_CNT (32)
#define USB_ATTEMPT_MAX  (3)


static unsigned int  g_aucCRC32[256] =
{
	0x00000000L, 0x77073096L, 0xEE0E612CL, 0x990951BAL,
	0x076DC419L, 0x706AF48FL, 0xE963A535L, 0x9E6495A3L,
	0x0EDB8832L, 0x79DCB8A4L, 0xE0D5E91EL, 0x97D2D988L,
	0x09B64C2BL, 0x7EB17CBDL, 0xE7B82D07L, 0x90BF1D91L,
	0x1DB71064L, 0x6AB020F2L, 0xF3B97148L, 0x84BE41DEL,
	0x1ADAD47DL, 0x6DDDE4EBL, 0xF4D4B551L, 0x83D385C7L,
	0x136C9856L, 0x646BA8C0L, 0xFD62F97AL, 0x8A65C9ECL,
	0x14015C4FL, 0x63066CD9L, 0xFA0F3D63L, 0x8D080DF5L,
	0x3B6E20C8L, 0x4C69105EL, 0xD56041E4L, 0xA2677172L,
	0x3C03E4D1L, 0x4B04D447L, 0xD20D85FDL, 0xA50AB56BL,
	0x35B5A8FAL, 0x42B2986CL, 0xDBBBC9D6L, 0xACBCF940L,
	0x32D86CE3L, 0x45DF5C75L, 0xDCD60DCFL, 0xABD13D59L,
	0x26D930ACL, 0x51DE003AL, 0xC8D75180L, 0xBFD06116L,
	0x21B4F4B5L, 0x56B3C423L, 0xCFBA9599L, 0xB8BDA50FL,
	0x2802B89EL, 0x5F058808L, 0xC60CD9B2L, 0xB10BE924L,
	0x2F6F7C87L, 0x58684C11L, 0xC1611DABL, 0xB6662D3DL,
	0x76DC4190L, 0x01DB7106L, 0x98D220BCL, 0xEFD5102AL,
	0x71B18589L, 0x06B6B51FL, 0x9FBFE4A5L, 0xE8B8D433L,
	0x7807C9A2L, 0x0F00F934L, 0x9609A88EL, 0xE10E9818L,
	0x7F6A0DBBL, 0x086D3D2DL, 0x91646C97L, 0xE6635C01L,
	0x6B6B51F4L, 0x1C6C6162L, 0x856530D8L, 0xF262004EL,
	0x6C0695EDL, 0x1B01A57BL, 0x8208F4C1L, 0xF50FC457L,
	0x65B0D9C6L, 0x12B7E950L, 0x8BBEB8EAL, 0xFCB9887CL,
	0x62DD1DDFL, 0x15DA2D49L, 0x8CD37CF3L, 0xFBD44C65L,
	0x4DB26158L, 0x3AB551CEL, 0xA3BC0074L, 0xD4BB30E2L,
	0x4ADFA541L, 0x3DD895D7L, 0xA4D1C46DL, 0xD3D6F4FBL,
	0x4369E96AL, 0x346ED9FCL, 0xAD678846L, 0xDA60B8D0L,
	0x44042D73L, 0x33031DE5L, 0xAA0A4C5FL, 0xDD0D7CC9L,
	0x5005713CL, 0x270241AAL, 0xBE0B1010L, 0xC90C2086L,
	0x5768B525L, 0x206F85B3L, 0xB966D409L, 0xCE61E49FL,
	0x5EDEF90EL, 0x29D9C998L, 0xB0D09822L, 0xC7D7A8B4L,
	0x59B33D17L, 0x2EB40D81L, 0xB7BD5C3BL, 0xC0BA6CADL,
	0xEDB88320L, 0x9ABFB3B6L, 0x03B6E20CL, 0x74B1D29AL,
	0xEAD54739L, 0x9DD277AFL, 0x04DB2615L, 0x73DC1683L,
	0xE3630B12L, 0x94643B84L, 0x0D6D6A3EL, 0x7A6A5AA8L,
	0xE40ECF0BL, 0x9309FF9DL, 0x0A00AE27L, 0x7D079EB1L,
	0xF00F9344L, 0x8708A3D2L, 0x1E01F268L, 0x6906C2FEL,
	0xF762575DL, 0x806567CBL, 0x196C3671L, 0x6E6B06E7L,
	0xFED41B76L, 0x89D32BE0L, 0x10DA7A5AL, 0x67DD4ACCL,
	0xF9B9DF6FL, 0x8EBEEFF9L, 0x17B7BE43L, 0x60B08ED5L,
	0xD6D6A3E8L, 0xA1D1937EL, 0x38D8C2C4L, 0x4FDFF252L,
	0xD1BB67F1L, 0xA6BC5767L, 0x3FB506DDL, 0x48B2364BL,
	0xD80D2BDAL, 0xAF0A1B4CL, 0x36034AF6L, 0x41047A60L,
	0xDF60EFC3L, 0xA867DF55L, 0x316E8EEFL, 0x4669BE79L,
	0xCB61B38CL, 0xBC66831AL, 0x256FD2A0L, 0x5268E236L,
	0xCC0C7795L, 0xBB0B4703L, 0x220216B9L, 0x5505262FL,
	0xC5BA3BBEL, 0xB2BD0B28L, 0x2BB45A92L, 0x5CB36A04L,
	0xC2D7FFA7L, 0xB5D0CF31L, 0x2CD99E8BL, 0x5BDEAE1DL,
	0x9B64C2B0L, 0xEC63F226L, 0x756AA39CL, 0x026D930AL,
	0x9C0906A9L, 0xEB0E363FL, 0x72076785L, 0x05005713L,
	0x95BF4A82L, 0xE2B87A14L, 0x7BB12BAEL, 0x0CB61B38L,
	0x92D28E9BL, 0xE5D5BE0DL, 0x7CDCEFB7L, 0x0BDBDF21L,
	0x86D3D2D4L, 0xF1D4E242L, 0x68DDB3F8L, 0x1FDA836EL,
	0x81BE16CDL, 0xF6B9265BL, 0x6FB077E1L, 0x18B74777L,
	0x88085AE6L, 0xFF0F6A70L, 0x66063BCAL, 0x11010B5CL,
	0x8F659EFFL, 0xF862AE69L, 0x616BFFD3L, 0x166CCF45L,
	0xA00AE278L, 0xD70DD2EEL, 0x4E048354L, 0x3903B3C2L,
	0xA7672661L, 0xD06016F7L, 0x4969474DL, 0x3E6E77DBL,
	0xAED16A4AL, 0xD9D65ADCL, 0x40DF0B66L, 0x37D83BF0L,
	0xA9BCAE53L, 0xDEBB9EC5L, 0x47B2CF7FL, 0x30B5FFE9L,
	0xBDBDF21CL, 0xCABAC28AL, 0x53B39330L, 0x24B4A3A6L,
	0xBAD03605L, 0xCDD70693L, 0x54DE5729L, 0x23D967BFL,
	0xB3667A2EL, 0xC4614AB8L, 0x5D681B02L, 0x2A6F2B94L,
	0xB40BBE37L, 0xC30C8EA1L, 0x5A05DF1BL, 0x2D02EF8DL
};

static unsigned int CRC_Code32(unsigned char* pvStartAddress, unsigned int dwSizeinbytes)
{
	unsigned int  dwCRC;
	unsigned char*  pucData = 0;

	if (pvStartAddress == 0)
	{
		return 0;
	}

	dwCRC = INIT;
	pucData = pvStartAddress;

	while (dwSizeinbytes--)
	{
		dwCRC = g_aucCRC32[(dwCRC ^ *pucData++) & 0xFFL] ^ (dwCRC >> 8);
	}

	return dwCRC ^ XOROT;
}

OTASupport::OTASupport() : APSafeThread(7*17 + 1, 64*1024, "OTA", strlen("OTA"))
{
	memset(&m_OTAConfig, 0, sizeof(OTAConfig));
}
 
OTASupport::~OTASupport()
{
	Exit();
}

void OTASupport::Init(OTAConfig csOTAConfig)
{
	memcpy(&m_OTAConfig, &csOTAConfig, sizeof(OTAConfig));

	StartRun();
}

void OTASupport::OnceProcess()
{
	FactoryTestInterface *pFactoryTestInterface = GetFactoryTestInterface();
	
	if(pFactoryTestInterface->IsReadyToOTA() > 0)
	{
		if(pFactoryTestInterface->CheckChipID() > 0)
		{
			StartOTA();
		}
	}
	
	ADIOSThreadSleep(1000);
}

void OTASupport::StartOTA( )
{
	do
	{
		if(GetFactoryTestInterface()->IsReadyToOTA() == 0)
		{
			break;
		}

		if(SetOptAndMarketID() == 0)
		{
			break;
		}

		if(WriteCoreAndCfg() == 0)
		{
			break;
		}

		if(HLSecureFuse() == 0)
		{
			break;
		}

		if(CheckOTATransponder(&m_OTAConfig.m_stOTADelivery) == 0)
		{
			break;
		}

		FlashEraseCABlock();
		
		TriggerOTA();
		
	}while(0);
}
unsigned int OTASupport::WriteCoreAndCfg(void)
{
	unsigned int unRet = 0;
	ADICHIPID_S sChip = { 0 };
	unsigned int unChipID = 0;
	unsigned int unCoreAndCfgFlag = 0;

	do
	{
		if(m_OTAConfig.m_CoreFlag == 0)
		{
			unRet = 1;
			break;
		}

		unCoreAndCfgFlag = GetOTACurSteps();
		if(unCoreAndCfgFlag == -1)
		{
			break;
		}

		if((unCoreAndCfgFlag & CORE_WRITED) != CORE_WRITED)
		{
			if (ADIGetChipID(&sChip) != ADI_SUCCESS)
			{
				break;
			}
			unChipID = (unsigned int)(sChip.m_szChipID[4] << 24) | (sChip.m_szChipID[5] << 16) | (sChip.m_szChipID[6] << 8) | (sChip.m_szChipID[7]);
			if(FlashCCACoreFileByUSB(unChipID) == 0)
			{
				printf("\n %s %d wt core file failed from USB\n",__FUNCTION__, __LINE__);
				if(FlashCCACoreFile(unChipID) == 0)
				{
					printf("\n %s %d wt core file failed from flash\n",__FUNCTION__, __LINE__);
					break;
				}
			printf("\n %s %d wt core successfully  from USB\n",__FUNCTION__, __LINE__);
				
			}
			else
			{
			printf("\n %s %d wt core and cfg successfully  from USB\n",__FUNCTION__, __LINE__);

				unCoreAndCfgFlag |=CFG_WRITED; 
			}
		}

		if((unCoreAndCfgFlag & CFG_WRITED) != CFG_WRITED)
		{
				if(FlashCFGFile() == 0)
				{
				printf("\n %s %d wt cfg file failed from flash\n",__FUNCTION__, __LINE__);
					break;
				}
				
			printf("\n %s %d wt cfg file successfully from flash\n",__FUNCTION__, __LINE__);
		}

		unRet = 1;
		
	}while(0);
	printf("---[%s][%d]--unRet=%d--\n", __FUNCTION__, __LINE__, unRet);

	return unRet;
}

unsigned int OTASupport::GetUSBRootPath(char *pBuffer, int nPathLen)
{
	//获取文件句柄
	int i = 0;
	int nLen = 0;
	int nIDCountt = 0;
	unsigned int adwId[USB_DEVICES_MAX_CNT];
	unsigned int unRet = 0;
	ADIFSDeviceInfo_S sDeviceInfo = {0};
	
	for(i=0; i<USB_ATTEMPT_MAX; i++)
	{
		unRet = ADIFSGetAllDeviceId((int*)adwId, 32, &nIDCountt);
		printf("[%s %d]ADIFSGetAllDeviceId i:%d dwRet:%d, nIdCnt:%d\n", __FUNCTION__, __LINE__,i,unRet, nIDCountt);

		if((nIDCountt > 0) && (0 == unRet)) // OK
		{			
			break;
		}
		
		ADIOSThreadSleep(1000);
	}
	
	if( (0!=unRet) || (nIDCountt<=0) )
	{
		printf("[%s %d] unRet:%d, nIDCountt:%d error!! \n", __FUNCTION__, __LINE__, unRet, nIDCountt);
		return -1;
	}
	
	for (i = 0; i < nIDCountt; i++)
	{
		printf("[%s %d]adwId[%d]:0x%x\n", __FUNCTION__, __LINE__,i, adwId[i]);
		unRet = ADIFSGetDeviceInfo(adwId[i], &sDeviceInfo);
		
		printf("[%s %d]ADIFSGetDeviceInfo, dwRet:%d, sDeviceInfo.m_szMountPoint %s\n", __FUNCTION__, __LINE__, unRet, sDeviceInfo.m_szMountPoint);
		if ( 0 != unRet)
		{
			continue;
		}

		nLen = strlen(sDeviceInfo.m_szMountPoint);		
		if ((nLen <= 0) || (nLen > ADI_MAX_FILE_NAME_LEN))
		{
			continue;
		}
		if (sDeviceInfo.m_szMountPoint[nLen - 1] != '/')
		{
			sDeviceInfo.m_szMountPoint[nLen] = '/';
			sDeviceInfo.m_szMountPoint[nLen + 1] = '\0';
			nLen++;
		}
	}
	
	sprintf(pBuffer, "%s",sDeviceInfo.m_szMountPoint);
}


unsigned int OTASupport::FlashCCACoreFileByUSB ( unsigned int unChipID )
{
    unsigned int unRet = 0;
	ADI_HANDLE hFile = 0;
	unsigned int unCoreEnd = unChipID  % 10;
	char cName[8] = { 0 };
	char acMountPath[128] = {0};
	unsigned char acCoreFileName[256];
	unsigned int unBufLen = 0;
	unsigned int unCoreLen = 0;
	
	do{
		//获取文件名
		if(GetUSBRootPath(acMountPath, sizeof(acMountPath)) > 0)
		{
			snprintf(acCoreFileName, sizeof(acCoreFileName)-1, "%s%s%d.bin", acMountPath, "Core&Cfg", unCoreEnd);
		}
		printf("[%s %d] acCoreFileName:%s\n",__FUNCTION__, __LINE__, acCoreFileName);
		unBufLen = 2*1024*1024;

		unsigned char * pucDataBuf = ( unsigned char * ) ADIOSMalloc (unBufLen);//写入到flash里面的数据
		memset(pucDataBuf,0x0,unBufLen);

		if ( pucDataBuf != NULL )
		{
			hFile = ADIFSOpen(acCoreFileName, "rb");
			if(hFile != NULL)
			{
				unCoreLen = ADIFSRead(hFile, pucDataBuf, unBufLen)	;
				if(unCoreLen != 0)
				{
					if(WriteFlash(m_OTAConfig.m_unCoreFileAddr, pucDataBuf, unCoreLen) == 1)
					{
						printf("[%s %d] Write core and cfg successs\n",__FUNCTION__, __LINE__);
						unRet = 1;
					}
				}
			}
			SetOTACurSteps(CFG_WRITED);			
		}
		if(pucDataBuf != NULL)
		{
			ADIOSFree ( pucDataBuf );
		}
	}while(0);
	
	printf("---[%s][%d]--unRet=%d--\n", __FUNCTION__, __LINE__, unRet);
		
    return unRet;	
}

unsigned int OTASupport::FlashCCACoreFile ( unsigned int unChipID )
{
    unsigned int unRet = 0;

	CoreDataInfo & inputCoreDataInfo( m_OTAConfig.m_CoreDataInfo [ ( unChipID + 1 ) % 10 ] );
	
	unsigned int unDataBufLen = GetBlockDataLen( inputCoreDataInfo );

	if ( unDataBufLen > 0 && unDataBufLen == inputCoreDataInfo.unDataSize )
	{
		unsigned char * pucDataBuf = ( unsigned char * ) ADIOSMalloc ( unDataBufLen );				
		
		if ( pucDataBuf != NULL )
		{
			unsigned int unDataLen = GetBlockData( inputCoreDataInfo, pucDataBuf, unDataBufLen );
			
			printf("[%s][%d] unDataLen %d\n", __FUNCTION__, __LINE__, unDataLen);
			
			if ( unDataLen > 0 )
			{
				unsigned int unWriteDataOff = 0;
				unsigned int unWriteAddrOff = 0;
				unsigned int unWriteLen = 0;
				int ii;

				//while( unWriteDataOff < unDataLen )
				{
					//unWriteLen = (( unDataLen - unWriteDataOff ) > MAX_CORE_FILED_SIZE ? MAX_CORE_FILED_SIZE : ( unDataLen - unWriteDataOff ));

					unsigned int nCRC = 0;
					unsigned int unCoreLen = 704 * 1024;
					unsigned char *pTempbuf = ( unsigned char * ) ADIOSMalloc ( unCoreLen );
					
					printf("[%s][%d] unWriteLen %d\n", __FUNCTION__, __LINE__, unWriteLen);

					if (pTempbuf != NULL)
					{
						memset(pTempbuf, 0xff, unCoreLen);
						memcpy(pTempbuf, pucDataBuf, unDataLen);
						
						nCRC = CRC_Code32((unsigned char *)pTempbuf, unCoreLen - 4);
						pTempbuf[unCoreLen - 4] = (nCRC & 0xff000000) >> 24;
						pTempbuf[unCoreLen - 3] = (nCRC & 0x00ff0000) >> 16;
						pTempbuf[unCoreLen - 2] = (nCRC & 0x0000ff00) >> 8;
						pTempbuf[unCoreLen - 1] = (nCRC & 0x000000ff);
						
						printf("[%s][%d]nCRC %x m_OTAConfig.m_unCoreFileAddr %x\n", __FUNCTION__, __LINE__, nCRC, m_OTAConfig.m_unCoreFileAddr);
	
						if ( WriteFlash ( m_OTAConfig.m_unCoreFileAddr, pTempbuf, unCoreLen ) == 1 )
						{
							printf("Write Core Success\n");
						}

						if ( WriteFlash ( m_OTAConfig.m_unCoreFileAddr + unCoreLen, pTempbuf, unCoreLen ) == 1 )
						{
							printf("Write Back Core Success\n");
						}
						
						if(pTempbuf != NULL)
						{
							ADIOSFree ( pTempbuf );
						}
					}
					/*for ( ii = 0; ii < MAX_READ_OR_WRITE_FLASH_COUNT; ii++ )
					{
						if ( WriteFlash ( m_OTAConfig.m_unCoreFileAddr + unWriteAddrOff, pucDataBuf + unWriteDataOff, unWriteLen ) == 1 )
						{
							break;
						}
					}

					if ( ii < MAX_READ_OR_WRITE_FLASH_COUNT )
					{
						unWriteDataOff += unWriteLen;
						unWriteAddrOff += m_OTAConfig.m_unCoreFileSize;
					}
					else
					{
						break;
					}*/
				}

				//if( unWriteDataOff == unDataLen )
				{
					unRet = 1;
					SetOTACurSteps(CORE_WRITED);
				}
			}

			ADIOSFree ( pucDataBuf );
		}		
	}
	printf("---[%s][%d]--unRet=%d--\n", __FUNCTION__, __LINE__, unRet);
		
    return unRet;	
}

unsigned int OTASupport::FlashCFGFile ( )
{
	unsigned int unRet = 0;

	unRet = ReadAndWriteBlockData( m_OTAConfig.m_CoreDataInfo [ 10 ], m_OTAConfig.m_unCFGFileAddr, m_OTAConfig.m_unCFGFileSize );

	if(unRet == 1)
	{
		SetOTACurSteps(CFG_WRITED);
	}
	printf("---[%s][%d]--unRet=%d--\n", __FUNCTION__, __LINE__, unRet);
	
	return unRet;
}

unsigned int OTASupport::ReadAndWriteBlockData( CoreDataInfo & inputCoreDataInfo, unsigned int unWriteAddre, unsigned int unFlashSize )
{
    unsigned int unRet = 0;

	unsigned int unDataBufLen = GetBlockDataLen( inputCoreDataInfo );

	if ( unDataBufLen > 0 && unDataBufLen == inputCoreDataInfo.unDataSize && unDataBufLen <= unFlashSize )
	{
		unsigned char * pucDataBuf = ( unsigned char * ) ADIOSMalloc ( unFlashSize );
		memset(pucDataBuf, 0xff, unFlashSize);

		if ( pucDataBuf != NULL )
		{
			unsigned int unDataLen = GetBlockData( inputCoreDataInfo, pucDataBuf, unFlashSize );

			if ( unDataLen > 0 )
			{
				unsigned int nCRC = 0;
				unsigned int unCfgLen = 10*1024;
				unsigned char *pTempCfg = ( unsigned char * ) ADIOSMalloc ( unCfgLen );

				printf("[%s][%d] unDataLen %d\n", __FUNCTION__, __LINE__, unDataLen);
				if(pTempCfg != NULL)
				{
					memset(pTempCfg, 0xff, unCfgLen);
					memcpy(pTempCfg, pucDataBuf, unDataLen);

					nCRC = CRC_Code32((unsigned char *)pTempCfg, unCfgLen - 4);
					pTempCfg[unCfgLen - 4] = (nCRC & 0xff000000) >> 24;
					pTempCfg[unCfgLen - 3] = (nCRC & 0x00ff0000) >> 16;
					pTempCfg[unCfgLen - 2] = (nCRC & 0x0000ff00) >> 8;
					pTempCfg[unCfgLen - 1] = (nCRC & 0x000000ff);
					
					printf("[%s][%d] unWriteAddre %x\n", __FUNCTION__, __LINE__, unWriteAddre);

					if ( WriteFlash ( unWriteAddre, pTempCfg, unCfgLen ) == 1 )
					{
						printf("Write Cfg Success1!\n");
						unRet = 1;
					}
					if ( WriteFlash ( unWriteAddre + unCfgLen, pTempCfg, unCfgLen ) == 1 )
					{
						printf("Write Cfg Success2!\n");
						unRet = 1;
					}
					if (pTempCfg != NULL)
					{
						ADIOSFree ( pTempCfg );
					}
				}
				/*int ii;
				for ( ii = 0; ii < MAX_READ_OR_WRITE_FLASH_COUNT; ii++ )
				{
					if ( WriteFlash ( unWriteAddre, pucDataBuf, unFlashSize ) == 1 )
					{
						unRet = 1;

						break;
					}
				}*/
			}

			ADIOSFree ( pucDataBuf );
		}		
	}
	
    return unRet;

}

unsigned int OTASupport::GetBlockDataLen( CoreDataInfo & inputCoreDataInfo )
{
    unsigned int unRet = 0;

    int ii;

    for ( ii = 0; ii < inputCoreDataInfo.unSegCount; ii++ )
    {
        unRet += inputCoreDataInfo.saSegInfo [ ii ].unSegSize;
    }

	return unRet;
}

unsigned int OTASupport::GetBlockData( CoreDataInfo & inputCoreDataInfo, unsigned char * pucDataBuf, unsigned int unDataBufLen )
{
	unsigned int unRet = 0;

	if ( pucDataBuf != NULL && unDataBufLen > 0 )
	{		
		unsigned char * pucData = ( unsigned char * ) ADIOSMalloc ( inputCoreDataInfo.unDataSize );

		if ( pucData != NULL )
		{	
			unsigned int unOffset = 0;
			int ii;

			for ( ii = 0; ii < inputCoreDataInfo.unSegCount; ii++ )
			{
				if ( ADIFlashRead ( inputCoreDataInfo.saSegInfo [ ii ].unSegAddr, pucData + unOffset, inputCoreDataInfo.saSegInfo [ ii ].unSegSize ) != ADI_SUCCESS )
				{
					break;
				}
		
				unOffset += inputCoreDataInfo.saSegInfo [ ii ].unSegSize;
			}

			if ( unOffset == inputCoreDataInfo.unDataSize )
			{		
				unsigned int unDataLen = ( ( ( ( unsigned int ) pucData[ 0 ] ) << 24 ) | ( ( ( unsigned int ) pucData[ 1 ] ) << 16 ) | ( ( ( unsigned int ) pucData[ 2 ] ) << 8 ) | pucData[ 3 ] );
				
				if ( unDataLen <= ( unOffset - DATA_HEAD - DATA_CRC_LEN ) )
				{
					if ( CheckSTBInfo( pucData + DATA_LEN_FLAG, unOffset ) > 0 && CheckCRC32( pucData + DATA_LEN_FLAG, unDataLen + DATA_HEAD + DATA_CRC_LEN - DATA_LEN_FLAG ) > 0 )
					{
						if ( unDataBufLen >= unDataLen )
						{
							memcpy( pucDataBuf, pucData + DATA_HEAD, unDataLen );

							unRet = unDataLen;
						}
					}
				}
			}

			ADIOSFree ( pucData );
		}
	}

	return unRet;
}

unsigned int OTASupport::HLSecureFuse()
{
	unsigned int unRet = 0;
	
	if (m_OTAConfig.m_unHLType == 0)
	{
		unRet = 1;
	}
	else if (m_OTAConfig.m_unHLType == 1)
	{
		if (OpenHLType(m_OTAConfig.m_nBoot, m_OTAConfig.m_nCW, m_OTAConfig.m_nJTag) == 1)
		{
			unRet = 1;
		}
	}
	printf("---[%s][%d]--unRet=%d--\n", __FUNCTION__, __LINE__, unRet);
	if(unRet == 1)
		SetOTACurSteps(OPEN_HL);

	return unRet;
}

unsigned int OTASupport::TriggerOTA()
{
	//OTAPid: load5.0(0x7D3), load3.2(0x402), castpal(undefined)
	//TableId: load3.2(0x80)
	ADIBLOtaLoaderPt_S stOtaLoaderPt;
	
	stOtaLoaderPt.ucOTATableId = m_OTAConfig.m_ucOTATableId;
	stOtaLoaderPt.usOTAPid = m_OTAConfig.m_usOTAPid;
	stOtaLoaderPt.eDLType = E_ADIBL_OTA_DL_DVB;

	memcpy(&stOtaLoaderPt.unionDeliver, &m_OTAConfig.m_stOTADelivery, sizeof(ADITunerSRCDeliver_U));

	ADIBLSaveOTALoaderPt(&stOtaLoaderPt, 1, 0);

	ADISYSReboot();

	return 1;
}

unsigned int OTASupport::CheckOTATransponder(ADITunerSRCDeliver_U* pDelivery)
{
	unsigned int unRet = 0;

	if (pDelivery != NULL)
	{
		ADITunerSRCDeliver_U tempADITunerSRCDeliver_U;

		memset(&tempADITunerSRCDeliver_U, 0, sizeof(ADITunerSRCDeliver_U));
		
		memcpy(&tempADITunerSRCDeliver_U, pDelivery, sizeof(ADITunerSRCDeliver_U));
		ADI_Error_Code errorCode = ADITunerConnect(0, &tempADITunerSRCDeliver_U);
		if (errorCode == ADI_SUCCESS)
		{
			int nStatus = 0;
			do
			{
				ADIOSThreadSleep(500);
				
				if (ADI_SUCCESS == ADITunerGetLockStatus(0, &nStatus))
				{
					if(nStatus == 0)
					{
						unRet = 1;
						break;
					}
				}
			} while (1);
		}
	}

	SetOTACurSteps(BEGIN_LOCKING);
	
	printf("--[%s][%d]---unRet:%d--\n", __FUNCTION__, __LINE__, unRet);

	return unRet;
}

void OTASupport::FlashEraseCABlock()
{
	if(m_OTAConfig.m_unCASize > 0)
	{
		ADIFlashEraseSpace(m_OTAConfig.m_unCAAddr , m_OTAConfig.m_unCASize);
	}
}

unsigned int OTASupport::WriteFlash(unsigned int unStartAddress, unsigned char * pucBuf, unsigned int uDataLength)
{
	unsigned int unRet = 0;

	if ( pucBuf != NULL && uDataLength > 0 )
	{
		if (ADIFlashWrite(unStartAddress, pucBuf, uDataLength) == ADI_SUCCESS)
		{
			unsigned int unOffset = 0;
			unsigned int unReadLength = 0;
			unsigned int unMaxReadLen = 128 * 1024;
			unsigned char * pucTmpBuf = (unsigned char *)ADIOSMalloc( unMaxReadLen );

			if ( pucTmpBuf != NULL )
			{	
				while (unOffset < uDataLength)
				{
					unReadLength = ( uDataLength - unOffset ) > unMaxReadLen ? unMaxReadLen : ( uDataLength - unOffset );
					if ( ADIFlashRead( unStartAddress + unOffset, pucTmpBuf, unReadLength ) == ADI_SUCCESS)
					{
						if ( memcmp( pucBuf + unOffset, pucTmpBuf, unReadLength ) != 0)
						{
							break;
						}
						
						unOffset += unReadLength;
					}
					else
					{
						break;
					}
				}

				if ( unOffset == uDataLength )
				{
					unRet = 1;
				}

				ADIOSFree(pucTmpBuf);
			}
		}
	}
	
	return unRet;
}

DWORD OTASupport::CalculateCRC32(unsigned char	* pbData, unsigned int unLength)
{
	unsigned int ii = 0;
	unsigned int jj = 0;
	DWORD dwCRC = 0;
	DWORD dwCrc32 = 0xffffffff;

	for (ii = 0; ii<unLength; ii++)
	{
		for (jj = 0; jj<8; jj++)
		{
			if (((pbData[ii] >> (7 - jj)) & 0x01))
				dwCrc32 ^= 1;

			if (dwCrc32 & 1)
				dwCrc32 = ((dwCrc32 >> 1) ^ CRC_FLAG);
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

unsigned int OTASupport::CheckCRC32(unsigned char  *pbData, unsigned int unLength)
{
	unsigned int unRet = 0;

	if (unLength >= 4)
	{
		unsigned int unDataIndex = unLength-4;
		DWORD dwCRC32 = ((DWORD)pbData[unDataIndex] << 24) | ((DWORD)pbData[unDataIndex + 1] << 16) | ((DWORD)pbData[unDataIndex + 2] << 8) | ((DWORD)pbData[unDataIndex + 3]);
		DWORD dwOrgCRC32 = CalculateCRC32(pbData, unLength - 4);
		
		if (dwOrgCRC32 == dwCRC32)
		{
			unRet = 1;
		}
	}

	return unRet;
}

unsigned int OTASupport::CheckSTBInfo(unsigned char *pBuffer, unsigned int unLen)
{
	unsigned int unRet = 0;

	if(unLen >= 12)
	{
		unsigned int unIndex = 0;
		unsigned int unManuF = (pBuffer[unIndex] << 24) | (pBuffer[unIndex + 1] << 16) | (pBuffer[unIndex + 2] << 8) | pBuffer[unIndex + 3];
		unsigned int unHW = (pBuffer[unIndex + 4] << 24) | (pBuffer[unIndex + 5] << 16) | (pBuffer[unIndex + 6] << 8) | pBuffer[unIndex + 7];
		unsigned int unVT = (pBuffer[unIndex + 8] << 24) | (pBuffer[unIndex + 9] << 16) | (pBuffer[unIndex + 10] << 8) | pBuffer[unIndex + 11];
		
		if ((unManuF == m_OTAConfig.m_unManuF) && (unHW == m_OTAConfig.m_unHW) && (unVT == m_OTAConfig.m_unVT))
		{
			unRet = 1;
		}
	}

	return unRet;
}

unsigned int OTASupport::SetOptAndMarketID(void)
{
	return TS_SetOptAndMarketID( m_OTAConfig.m_unMarkIDFlag );
}

unsigned int OTASupport::GetHLType(void)
{
	return m_OTAConfig.m_unHLType;
}

void OTASupport::SetOTACurSteps(int nStatus)
{	
	FactoryTestInterface *pFactoryTestInterface = GetFactoryTestInterface();

	if(pFactoryTestInterface != NULL)
	{
		pFactoryTestInterface->SetOTAStatus(nStatus);
	}
}

unsigned int OTASupport::GetOTACurSteps(void)
{
	unsigned int unRet = -1;
	int nCount = 2;
	TestResult_S stTestResult = {0};
	FactoryTestInterface *pFactoryTestInterface = GetFactoryTestInterface();
	
	if(pFactoryTestInterface != NULL)
	{
		pFactoryTestInterface->GetTestResult(&stTestResult);
		unRet = stTestResult.nOTAResult;
	}
	else
	{
		printf("[%s][%d] pFactoryTestInterface == NULL", __FUNCTION__, __LINE__);
	}

	return unRet;
}


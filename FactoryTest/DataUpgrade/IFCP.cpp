#include "string.h"
#include <stdio.h>
#include "IFCP.h"
#include "adi_public.h"
#include "adi_os.h"
#include "adi_fs.h"
#include "adi_typedef.h"

#define IFCP_FILE "IFCP.stb"

#define IFCP_PS_HEADER_BINARY_LEN 16
#define IFCP_PS_IMAGE_HEADER_BINARY_LEN 32
#define USB_DEVICES_MAX_CNT (32)
#define USB_ATTEMPT_MAX  (3)

static unsigned short g_ImageVersion = 0;
static ADI_BOOL g_IsTestImage = ADI_FALSE;

char ADIFSGets(char *Des, int Len, FILE *hFile)
{
	char ch[2] = {0};
	int ActReadLen = 0;
	int nCount = Len;
	char *pTemp = Des;
	
	while(--nCount > 0 && (ActReadLen = ADIFSRead(hFile, ch, 1) != 0))
	{
		if((*pTemp++ = ch[0]) == '\n')
		{
			break;
		}
	}
	*pTemp = '\0';

	return (pTemp == Des && ActReadLen == 0)? NULL:Des;
}

IFCP::IFCP()
{
	memset(m_ucIPCP_cwodd, 0, sizeof(m_ucIPCP_cwodd));
	memset(m_unIFCP_cweven, 0, sizeof(m_unIFCP_cweven));
	memset(m_ucIFCP_Image, 0, sizeof(m_ucIFCP_Image));
	memset(m_ucIFCP_k2, 0, sizeof(m_ucIFCP_k2));

	memset(m_acLastChipID, 0, sizeof(m_acLastChipID));
	ClearAllData();
}

IFCP::~IFCP()
{
}

unsigned int IFCP::ParseAllData(unsigned char *pucChipID, unsigned char *pBuffer, unsigned int unLen)
{
	unsigned int unRet = 0;
	unsigned char aucChipID[10] = { 0 };
	unsigned int unChipID = 0;
	unsigned int unIndex = 0;
	unsigned int pos = 0;

	do
	{
		unChipID = (pucChipID[0] << 24) | (pucChipID[1] << 16) | (pucChipID[2] << 8) | pucChipID[3];
		sprintf((char*)aucChipID, "%02x%02x%02x%02x", pucChipID[0], pucChipID[1], pucChipID[2], pucChipID[3]);
		LittleToBig(aucChipID, sizeof(aucChipID));

		if (memcmp(m_acLastChipID, aucChipID, 4) != 0)
		{
			if (IFCPInit((char*)aucChipID, strlen((char*)aucChipID)) == 0)
			{
				break;
			}
		}

		if (ParseIFCPData(aucChipID, unChipID) == 0)
		{
			break;
		}

		pos = 0;
		unIndex = GetIFCPData(&pBuffer[2], unLen - 2);
		if (unIndex == 0)
		{
			break;
		}
		pBuffer[pos] = (unIndex >> 8) & 0xff;
		pBuffer[pos + 1] = unIndex & 0xff;
		pos += 2;
		pos += unIndex;
		
		//unLen = pos;

		unRet = pos;
	} while (0);

	return unRet;
}

unsigned int IFCP::IFCPInit(unsigned char *pcChipID, int nLen)
{
	unsigned int unRet = 0;

	do
	{
		if (GetFileName(pcChipID, nLen) == 0)
		{
			break;
		}

		if (GetSTHFileInfo() == 0)
		{
			break;
		}

		if (GetFileInfo(m_acIFCPFileName, m_stSTHFile) == 0)
		{
			break;
		}
		
		unRet = 1;
	} while (0);

	if (unRet == 0)
	{
		memset(m_acLastChipID, 0, sizeof(m_acLastChipID));
	}

	return unRet;
}

unsigned int IFCP::GetIFCPData(unsigned char *pucBuffer, unsigned int unLen)
{
	unsigned int unRet = 0;

	if (pucBuffer != NULL || unLen >= m_unIFCPDataLen)
	{
		memcpy(pucBuffer, m_ucIFCPHexData, m_unIFCPDataLen);
		unRet = m_unIFCPDataLen;
	}

	return unRet;
}

unsigned int IFCP::ParseIFCPData(unsigned char *pucChipID, unsigned int unChipID)
{
	unsigned int unRet = 0;
	unsigned int unIndex = 0;
	char *pTemp = NULL;
	char pcStr[1024] = { 0 };
	char acActMsgData[256] = { 0 };

	FILE *pFILE = NULL;

	do
	{
		pFILE = ADIFSOpen((const char *)m_acIFCPFileName, "rb");
		if (pFILE == NULL)
		{
			break;
		}

		if (unChipID < m_stSTHFile.unFirstChip)
		{
			break;
		}
		unIndex = unChipID - m_stSTHFile.unFirstChip;
		ADIFSSeek(pFILE, m_stSTHFile.unFirstPos + m_stSTHFile.unItemSize * unIndex, ADIFS_SEEK_SET);
		
		if (ADIFSRead(pFILE, pcStr, m_stSTHFile.unItemSize) == 0)
		{
			break;
		}
		
		pTemp = strstr(pcStr, (char*)pucChipID);
		if (pTemp == NULL)
		{
			break;
		}
		
		if (GetFileItem(pTemp, strlen(pTemp), acActMsgData, sizeof(acActMsgData), "<ACT_MSG>", "</ACT_MSG>") == 0)
		{
			break;
		}
		
		if (ConstructIFCPData((unsigned char*)acActMsgData, strlen(acActMsgData)) == 0)
		{
			break;
		}
		
		unRet = 1;
	} while (0);

	if (pFILE != NULL)
	{
		ADIFSClose(pFILE);
	}

	return unRet;
}

unsigned int IFCP::ConstructIFCPData(unsigned char *pucActMeg, unsigned int unLen)
{
	int pos = 0;
	unsigned int unRet = 0;
	unsigned int unActMsgLen = 0;
	unsigned int unImageLen = 0;
	unsigned int unDataLen = 0;
	unsigned int payloadLength = 0;
	unsigned int unCrc = 0;

	do
	{
		if (unLen / 2 + strlen((char*)m_ucIFCP_Image) / 2 + IFCP_PS_HEADER_BINARY_LEN + IFCP_PS_IMAGE_HEADER_BINARY_LEN > sizeof(m_ucIFCPHexData))
		{
			break;
		}
		pos = 0;
		/*(4B) CRC32_H, Update header CRC later. */
		pos += 4;

		/*(1B) Version: currently fixed to 1 */
		m_ucIFCPHexData[pos++] = 1;

		/*(3B) Magic Number: "CCA" */
		m_ucIFCPHexData[pos++] = 'C';
		m_ucIFCPHexData[pos++] = 'C';
		m_ucIFCPHexData[pos++] = 'A';

		/*(4B) Length, Update this payload length later. */
		pos += 4;

		/*(4B) CRC32_D, Update IFCP Data CRC later. */
		pos += 4;

		/* --------Payload-------- */
		/*(4B) Version: currently fixed to 1 */
		m_ucIFCPHexData[pos++] = 1;

		/*(15B) Reserved */
		pos += 15;

		/*(2B) Image Version */
		m_ucIFCPHexData[pos++] = (g_ImageVersion >> 8) & 0xff;
		m_ucIFCPHexData[pos++] = g_ImageVersion & 0xff;

		/*(1B) Flag1 */
		m_ucIFCPHexData[pos] = 0;
		if (ADI_TRUE == g_IsTestImage)
		{
			m_ucIFCPHexData[pos] |= 0x01;
		}
		pos++;

		/*(7B) Reserved */
		pos += 7;

		/*(2B) AM length */
		/* AM */
		unActMsgLen = IRDCCA_Char2Hex(pucActMeg, unLen, &m_ucIFCPHexData[pos + 2]);
		m_ucIFCPHexData[pos++] = (unActMsgLen >> 8) & 0xff;
		m_ucIFCPHexData[pos++] = unActMsgLen & 0xff;
		pos += unActMsgLen;

		/*(4B) Image length */
		/* Image */
		unImageLen = IRDCCA_Char2Hex(m_ucIFCP_Image, strlen((char*)m_ucIFCP_Image), &m_ucIFCPHexData[pos + 4]);
		m_ucIFCPHexData[pos++] = (unImageLen >> 24) & 0xff;
		m_ucIFCPHexData[pos++] = (unImageLen >> 16) & 0xff;
		m_ucIFCPHexData[pos++] = (unImageLen >> 8) & 0xff;
		m_ucIFCPHexData[pos++] = unImageLen & 0xff;
		pos += unImageLen;

		unDataLen = pos;
		m_unIFCPDataLen = unDataLen;
		payloadLength = unDataLen - IFCP_PS_HEADER_BINARY_LEN;

		//crc head
		pos = 8;

		m_ucIFCPHexData[pos++] = (payloadLength >> 24) & 0xff;
		m_ucIFCPHexData[pos++] = (payloadLength >> 16) & 0xff;
		m_ucIFCPHexData[pos++] = (payloadLength >> 8) & 0xff;
		m_ucIFCPHexData[pos++] = payloadLength & 0xff;

		unCrc = GetCrc32(&m_ucIFCPHexData[IFCP_PS_HEADER_BINARY_LEN], payloadLength);

		m_ucIFCPHexData[pos++] = (unCrc >> 24) & 0xff;
		m_ucIFCPHexData[pos++] = (unCrc >> 16) & 0xff;
		m_ucIFCPHexData[pos++] = (unCrc >> 8) & 0xff;
		m_ucIFCPHexData[pos++] = unCrc & 0xff;

		unCrc = GetCrc32(&m_ucIFCPHexData[4], IFCP_PS_HEADER_BINARY_LEN - 4);
		pos = 0;
		m_ucIFCPHexData[pos++] = (unCrc >> 24) & 0xff;
		m_ucIFCPHexData[pos++] = (unCrc >> 16) & 0xff;
		m_ucIFCPHexData[pos++] = (unCrc >> 8) & 0xff;
		m_ucIFCPHexData[pos++] = unCrc & 0xff;
		//m_ucIFCPHexData

		unRet = 1;
	} while (0);

	return unRet;
}

unsigned int IFCP::IRDCCA_Char2Hex(const unsigned char* pucSource, unsigned int nlength, unsigned char *pucDes)
{
	unsigned int ii = 0;
	unsigned int jj = 0;

	if ((NULL == pucSource) || (NULL == pucDes))
	{
		return 0;
	}

	for (ii = 0; ii<nlength; ii += 2)
	{
		if (ii + 1<nlength)
		{
			pucDes[jj++] = (ChartoNum(pucSource[ii]) << 4) | ChartoNum(pucSource[ii + 1]);
		}
		else
		{
			pucDes[jj++] = ChartoNum(pucSource[ii]);
			break;
		}
	}
	return jj;
}

unsigned char IFCP::ChartoNum(unsigned char ch)
{
	char base = 0;;

	if (ch >= 0x61)
	{
		base = 0x61 - 10;
	}
	else if (ch >= 0x41)
	{
		base = 0x41 - 10;
	}
	else if (ch >= 0x30)
	{
		base = 0x30;
	}

	return (ch - base);
}

unsigned int IFCP::LittleToBig(unsigned char *pBuffer, unsigned int unLen)
{
	int i = 0;
	unsigned int unRet = 1;

	for (i = 0; i < unLen; i++)
	{
		if (pBuffer[i] >= 'a' && pBuffer[i] <= 'f')
		{
			pBuffer[i] = pBuffer[i] - ('a' - 'A');
		}
	}

	return unRet;
}

unsigned int IFCP::GetFileInfo(char *pFileName, File_Info_S & stFileInfo)
{
	FILE *pFILE = NULL;
	char aucStr[1024] = { 0 };
	unsigned int unRet = 0;
	unsigned int unCurPos = 0;
	char *pTemp = NULL;
	unsigned char aucChipID[10] = { 0 };

	do
	{
		pFILE = ADIFSOpen((const char *)pFileName, "rb");
		if (pFILE == NULL)
		{
			break;
		}
		
		while ((pTemp == NULL) && (!feof(pFILE)))
		{
			if (ADIFSGets(aucStr, sizeof(aucStr), pFILE) == 0)
			{
				break;
			}
			pTemp = strstr(aucStr, "<CHIP>");
		}
		
		if (pTemp == NULL)
		{
			break;
		}
		stFileInfo.unFirstPos = ADIFSTell(pFILE) - strlen(pTemp) ;

		pTemp = NULL;
		while ((pTemp == NULL) && (!feof(pFILE)))
		{
			if (ADIFSGets(aucStr, sizeof(aucStr), pFILE) == 0)
			{
				break;
			}
			pTemp = strstr(aucStr, "<SERIAL>");
		}
		if (pTemp == NULL)
		{
			break;
		}

		pTemp += strlen("<SERIAL>");
		int i = 0;
		while (pTemp[i] != '<' && i < sizeof(aucChipID))
		{
			aucChipID[i] = pTemp[i];
			i++;
		}
		stFileInfo.unFirstChip = 0;
		GetChipId(aucChipID, strlen((char*)aucChipID), stFileInfo.unFirstChip);
		
		pTemp = NULL;
		while ((pTemp == NULL) && (!feof(pFILE)))
		{
			if (ADIFSGets( aucStr, sizeof(aucStr), pFILE) == 0)
			{
				break;
			}
			pTemp = strstr(aucStr, "<CHIP>");
		}
		
		if (pTemp == NULL)
		{
			break;
		}
		
		unCurPos = ADIFSTell(pFILE) - strlen(pTemp);
		stFileInfo.unItemSize = unCurPos - stFileInfo.unFirstPos;

		unRet = 1;
	} while (0);

	if (pFILE != NULL)
	{
		ADIFSClose(pFILE);
	}

	return unRet;
}

unsigned int IFCP::GetSTHFileInfo()
{
	FILE *pFILE = NULL;
	char cVersion[8] = { 0 };
	char cBuffer[16] = { 0 };
	char acIFCPTag[128] = { 0 };
	char *pcStr = NULL;
	int nStrSize = 64*1024;
	unsigned int unRet = 0;

	do
	{
		pcStr = ADIOSMalloc(nStrSize);
		if(0 == pcStr)
		{
			break;
		}
		pFILE = ADIFSOpen((const char *)m_acIFCPFileName, "rb");
		if (pFILE == NULL)
		{
			break;
		}
		
		if (ADIFSRead(pFILE, pcStr, nStrSize) == 0)
		{
			break;
		}
		
		if (GetFileItem(pcStr, nStrSize, (char*)m_ucIPCP_cwodd, sizeof(m_ucIPCP_cwodd), "<CW_ODD>", "</CW_ODD>") == 0)
		{
			break;
		}
		
		if (GetFileItem(pcStr, nStrSize, (char*)m_unIFCP_cweven, sizeof(m_unIFCP_cweven), "<CW_EVEN>", "</CW_EVEN>") == 0)
		{
			break;
		}
		
		if (GetFileItem(pcStr, nStrSize, (char*)m_ucIFCP_k2, sizeof(m_ucIFCP_k2), "<K2>", "</K2>") == 0)
		{
			break;
		}
		
		if (GetFileItem(pcStr, nStrSize, cVersion, sizeof(cVersion), "<IFCP_IMAGE image_version=\"", "\" test_image=\"") == 0)
		{
			break;
		}

		if (GetVersion(cVersion, strlen(cVersion)) == 0)
		{
			break;
		}
		//printf("cVersion:%s\n", cVersion);
		sprintf(acIFCPTag, "<IFCP_IMAGE image_version=\"%s\" test_image=\"", cVersion);
		
		if (GetFileItem(pcStr, nStrSize, cBuffer, sizeof(cBuffer), acIFCPTag, "\">") == 0)
		{
			break;
		}

		if (GetIsTestImage(cBuffer, strlen(cBuffer)) == 0)
		{
			break;
		}
		sprintf(acIFCPTag, "<IFCP_IMAGE image_version=\"%s\" test_image=\"%s\">", cVersion, cBuffer);

		if (GetFileItem(pcStr, nStrSize, (char*)m_ucIFCP_Image, sizeof(m_ucIFCP_Image), acIFCPTag, "</IFCP_IMAGE>") == 0)
		{
			break;
		}
		
		unRet = 1;
	} while (0);

	if(pcStr != 0)
	{
		ADIOSFree(pcStr);
	}

	if (pFILE != NULL)
	{
		ADIFSClose(pFILE);
	}

	return unRet;
}

unsigned int IFCP::GetFileItem(char *pBuffer, int nBufLen, char *pDest, int nDestLen, char *pStartData, char *pEndData)
{
	unsigned int unRet = 0;
	char *pStart = NULL;
	char *pEnd = NULL;
	int i = 0;

	do
	{
		pStart = strstr(pBuffer, pStartData);
		if (pStart == NULL)
		{
			break;
		}

		pEnd = strstr(pStart, pEndData);
		if (pEnd == NULL)
		{
			break;
		}

		pStart += strlen(pStartData);
		while (((pStart + i) != pEnd) && (i < nDestLen))
		{
			pDest[i] = pStart[i];
			i++;
		}

		if ((pStart + i) != pEnd)
		{
			break;
		}

		unRet = 1;
	} while (0);

	return unRet;
}

unsigned int IFCP::GetChipId(unsigned char *pBuffer, unsigned int unLen, unsigned int & unChipID)
{
	int i = 0;
	unsigned int unRet = 0;

	for (i = 0; i < unLen; i++)
	{
		if (pBuffer[i] >= '0' && pBuffer[i] <= '9')
		{
			unChipID = unChipID * 16 + pBuffer[i] - '0';
		}
		else if (pBuffer[i] >= 'a' && pBuffer[i] <= 'f')
		{
			unChipID = unChipID * 16 + pBuffer[i] - 'a' + 10;
		}
		else if (pBuffer[i] >= 'A' && pBuffer[i] <= 'F')
		{
			unChipID = unChipID * 16 + pBuffer[i] - 'A' + 10;
		}
		else
		{
			break;
		}
	}

	if (i == unLen)
	{
		unRet = 1;
	}

	return unRet;
}

unsigned int IFCP::GetCrc32(const unsigned char *pDataBuffer, unsigned int dataLength)
{
	unsigned int crcResult = 0xffffffff;

	while (dataLength--)
	{
		crcResult = crc32Table[((crcResult >> 24) ^ *pDataBuffer++) & 0xFFL] ^ (crcResult << 8);
	}

	return crcResult;
}

void IFCP::ClearAllData(void)
{
	m_unIFCPDataLen = 0;
	memset(m_ucIFCPHexData, 0, sizeof(m_ucIFCPHexData));
}

unsigned int IFCP::GetVersion(char *pacBuffer, int nLen)
{
	unsigned int unRet = 0;

	if (pacBuffer != NULL && nLen > 0)
	{
		g_ImageVersion = 0;
		for (int ii = 0; ii < nLen; ii++)
		{
			g_ImageVersion = ChartoNum(pacBuffer[ii]) + g_ImageVersion * 10;
		}
		unRet = 1;
	}

	return unRet;
}

unsigned int IFCP::GetIsTestImage(char *pacBuffer, int nLen)
{
	unsigned int unRet = 0;

	if (pacBuffer != NULL && nLen > 0)
	{
		if (memcmp(pacBuffer, "false", strlen("false")) == 0 || memcmp(pacBuffer, "ADI_FALSE", strlen("ADI_FALSE")) == 0)
		{
			g_IsTestImage = ADI_FALSE;
		}
		else
		{
			g_IsTestImage = ADI_TRUE;
		}

		unRet = 1;
	}

	return unRet;
}

unsigned int IFCP::GetFileName(unsigned char *cChipID, int nLen)
{
	char cName[8] = { 0 };
	unsigned int unRet = 0;
	char acMountPath[128] = {0};

	if (cChipID != NULL && nLen > 0)
	{
		LittleToBig((unsigned char*)cChipID, sizeof(cChipID));
		
		memset(m_acIFCPFileName, 0, sizeof(m_acIFCPFileName));
		memset(m_acLastChipID, 0, sizeof(m_acLastChipID));
		
		memcpy(m_acLastChipID, cChipID, 4);
		
		if(GetUSBRootPath(acMountPath, sizeof(acMountPath)) > 0)
		{
			snprintf(m_acIFCPFileName, sizeof(m_acIFCPFileName)-1, "%s%s_%s", acMountPath, m_acLastChipID,IFCP_FILE);
		}

		unRet = 1;
		
		printf("[%s %d] m_acIFCPFileName:%s unRet:%d\n",__FUNCTION__, __LINE__, m_acIFCPFileName, unRet);
	}

	return unRet;
}

unsigned int IFCP::GetUSBRootPath(char *pBuffer, int nPathLen)
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

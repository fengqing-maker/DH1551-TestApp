#include "FlashCheck.h"
#include "adi_os.h"
#include "adi_flash.h"
#include <stdio.h>

#define CHECK_CRC_FLAG (0xEDB88320)
#define MAX_BLOCK_SIZE (0x10000)
#define CRC_ADAPTER_SIZE (4)

FlashCheck::FlashCheck()
{
}

FlashCheck::~FlashCheck()
{
}

int FlashCheck::Init(FlashCheckInfo *pFlashCheckInfo)
{
	int nRe = 0;

	if (pFlashCheckInfo != NULL)
	{
		m_FlashCheckInfo.m_nCheckFlag = pFlashCheckInfo->m_nCheckFlag;
		m_FlashCheckInfo.m_nCheckCount = pFlashCheckInfo->m_nCheckCount;

		for (int ii = 0; ii < pFlashCheckInfo->m_nCheckCount; ii++)
		{
			m_FlashCheckInfo.m_vtCheck.push_back(pFlashCheckInfo->m_vtCheck[ii]);
		}
		nRe = 1;
	}

	return nRe;
}

int FlashCheck::GetFlashConfig(FlashCheckInfo *pFlashCheckInfo)
{
	int nRe = 0;

	if (pFlashCheckInfo != NULL)
	{
		pFlashCheckInfo->m_nCheckFlag = m_FlashCheckInfo.m_nCheckFlag;
		pFlashCheckInfo->m_nCheckCount = m_FlashCheckInfo.m_nCheckCount;

		for (int ii = 0; ii < m_FlashCheckInfo.m_nCheckCount; ii++)
		{
			pFlashCheckInfo->m_vtCheck.push_back(m_FlashCheckInfo.m_vtCheck[ii]);
		}
		nRe = 1;
	}

	return nRe;
}

int FlashCheck::SetOneCheckBlock( XMLNode *pXMLNode, CheckInfo_s *pCheckInfo, int nIndex)
{
	int nRe = 0;
	char acCheckTag[32] = { 0 };

	sprintf(acCheckTag, "FLASHNODE%d", nIndex);

	XMLNode *pTemp = pXMLNode->GetXMLNode(acCheckTag, strlen(acCheckTag));

	if( pTemp != NULL )
	{
		nRe = pTemp->GetValue("STARTADDR", strlen("STARTADDR"), (int*)(&(pCheckInfo->m_unStartAddr)));
		nRe &= pTemp->GetValue("FLASHSIZE", strlen("FLASHSIZE"), (int*)(&(pCheckInfo->m_unFlashSize)));
		nRe &= pTemp->GetValue("ORICRC", strlen("ORICRC"), (int*)(&(pCheckInfo->m_unOriCrc)));
	}

	return nRe;
}

int FlashCheck::SetCrcCheckInfo(XMLNode *pXMLNode)
{
	int nRe = 0;

	if (pXMLNode->IsSameTag("FACTORYTEST", strlen("FACTORYTEST")))
	{
		nRe = pXMLNode->GetValue("CHECKFLASH", strlen("CHECKFLASH"), &m_FlashCheckInfo.m_nCheckFlag);
		if(m_FlashCheckInfo.m_nCheckFlag == 1 && nRe == 1)
		{
			XMLNode *pTemp = pXMLNode->GetXMLNode("CHECKCRC", strlen("CHECKCRC"));
			if(pTemp != NULL)
			{
				CheckInfo_s tempCheckInfo = {0};
				nRe &= pTemp->GetValue("CHECKCOUNT", strlen("CHECKCOUNT"), &m_FlashCheckInfo.m_nCheckCount);
				for(int ii = 1; ii <= m_FlashCheckInfo.m_nCheckCount; ii++)
				{
					if (SetOneCheckBlock(pTemp, &tempCheckInfo, ii) == 0)
					{
						printf("--[%s][%d]--ii:%d--\n", __FUNCTION__, __LINE__, ii);
						nRe = 0;
						break;
					}

					m_FlashCheckInfo.m_vtCheck.push_back(tempCheckInfo);
				}
			}
			else
			{
				nRe = 0;
			}
		}
	}

	return nRe;
}

int FlashCheck::StartCheck(void)
{
	int nRe = 1;

	if(m_FlashCheckInfo.m_nCheckFlag > 0)
	{
		unsigned int unStartAddr = 0;
		unsigned int unFlashSize = 0;
		unsigned int unOriCrc = 0;
		for (int ii = 0; ii < m_FlashCheckInfo.m_nCheckCount; ii++)
		{
			unStartAddr = m_FlashCheckInfo.m_vtCheck[ii].m_unStartAddr;
			unFlashSize = m_FlashCheckInfo.m_vtCheck[ii].m_unFlashSize;
			unOriCrc = m_FlashCheckInfo.m_vtCheck[ii].m_unOriCrc;
			if (CheckOneItem(unStartAddr, unFlashSize, unOriCrc) == 0)
			{
				printf("CHECK CRC FAIL Index=%d, unStartAddr:0x%x, unFlashSize:0x%x, unOriCrc:0x%x\n", ii, unStartAddr, unFlashSize,unOriCrc);
				nRe = 0;
				break;
			}
		}
	}

	return nRe;
}

unsigned int FlashCheck::CheckOneItem(unsigned int unStartAddr, unsigned int unSize, unsigned int unCrc)
{
	unsigned int unRe = 0;
	unsigned char *pucTemp = NULL;
	unsigned int unActCrc = 0;
	unsigned int unIndex = 0;
	unsigned int unAdaptLen = 0;
	unsigned int unReadLen = 0;
	
	pucTemp = (unsigned char*)ADIOSMalloc(MAX_BLOCK_SIZE + CRC_ADAPTER_SIZE);
	if(pucTemp == NULL)
	{
		printf("ADIOSMalloc Fail size:0x%x, unStartAddr:0x%x\n", MAX_BLOCK_SIZE + CRC_ADAPTER_SIZE, unStartAddr);
		return unRe;
	}

	while (unSize > unIndex)
	{
		if(unAdaptLen > 0)
		{
			pucTemp[0] = (unsigned char)((unActCrc >> 24) & 0xff);
			pucTemp[1] = (unsigned char)((unActCrc >> 16) & 0xff);
			pucTemp[2] = (unsigned char)((unActCrc >> 8) & 0xff);
			pucTemp[3] = (unsigned char)(unActCrc & 0xff);
		}		
		unReadLen = (unSize > MAX_BLOCK_SIZE + unIndex) ? MAX_BLOCK_SIZE : ( unSize - unIndex );
		if(ADIFlashRead( unStartAddr + unIndex, &pucTemp[unAdaptLen], unReadLen ) != ADI_SUCCESS)
		{
			printf("ADIFlashRead Fail StartAddr:0x%x\n", unStartAddr + unIndex);
			break;
		}

		unActCrc = CalculateCRC32( pucTemp, unReadLen + unAdaptLen );
		unAdaptLen = CRC_ADAPTER_SIZE;
		unIndex += unReadLen;
	}

	if ( unSize == unIndex && unActCrc == unCrc )
	{
		unRe = 1;
	}
	else
	{
		printf("CRC ERROR unStartAddr:0x%x, ActCrc:0x%x, OriCrc:0x%x\n", unStartAddr, unActCrc, unCrc);
	}

	if(pucTemp != NULL)
	{
		ADIOSFree(pucTemp);
	}

	return unRe;
}

unsigned int FlashCheck::CalculateCRC32(unsigned char *pbData, unsigned int unLength)
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
				dwCrc32 = ((dwCrc32 >> 1) ^ CHECK_CRC_FLAG);
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

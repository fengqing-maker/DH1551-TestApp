/*
 * STBData.cpp
 *
 *  Created on: 2015-9-21
 *      Author: linc
 */

#include "STBData.h"
#include "adi_flash.h"
#include "stdio.h"
#include "string.h"
#include "APAssert.h"
#include "adi_debug.h"

#define CRC_FLAG (0xEDB88320)


STBData::STBData(unsigned int unStartAddr, unsigned int unDataSize, int nDebugLevel)
{
	m_unSNMaxSize = MAX_SN_LEN;	
	m_unHDCPKeyMaxSize = MAX_HDCP_LEN;
	m_unMACMaxSize = MAX_MAC_LEN;
	m_unChipIDMaxSize = MAX_CHIPID_LEN;
	m_unSTBDataMaxSize = MAX_INDIVI_RETURN_LEN;
	m_unPVRFlagMaxSize = MAX_PVR_FLAG_LEN;
	m_unCustomerCodeMaxSize = MAX_CUSTOMER_CODE_LEN;
	m_unPefDataMaxSize = MAX_PEFDATA_LEN;
	
	APAssert(unDataSize > (m_unSNMaxSize + m_unMACMaxSize + m_unHDCPKeyMaxSize + m_unChipIDMaxSize + m_unSTBDataMaxSize + m_unPVRFlagMaxSize));
	
	m_unSNStartAddr = unStartAddr;
	m_unHDCPStartAddr = m_unSNStartAddr + m_unSNMaxSize;
	m_unMACStartAddr = m_unHDCPStartAddr + m_unHDCPKeyMaxSize;
	m_unChipIDAddr = m_unMACStartAddr + m_unMACMaxSize;
	m_unSTBDataAddr = m_unChipIDAddr + m_unChipIDMaxSize;
	m_unPVRFlagAddr = m_unSTBDataAddr + m_unSTBDataMaxSize;
	m_unCustomerCodeAddr = m_unPVRFlagAddr + m_unPVRFlagMaxSize;

	m_unPefDataAddr = unStartAddr + (0x10000 - m_unPefDataMaxSize);
	SetIFCPAddress(0, 0);
	m_unAllWriteSize = m_unSNMaxSize + m_unHDCPKeyMaxSize + m_unMACMaxSize + m_unChipIDMaxSize + m_unSTBDataMaxSize;

	ADIDebugSetLevel(STB_DATA_DEBUG_MODULE, nDebugLevel);
	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]m_unSNStartAddr=0x%x,m_unHDCPStartAddr=0x%x,m_unMACStartAddr=0x%x\n", __FUNCTION__, __LINE__, m_unSNStartAddr, m_unHDCPStartAddr, m_unMACStartAddr);
}

STBData::STBData(STBDataInfo_S *pSTBDataInfo_S, int nDebugLevel)
{
	if(pSTBDataInfo_S != NULL)
	{
		m_unSNMaxSize = pSTBDataInfo_S->m_unSNMaxSize;	
		m_unHDCPKeyMaxSize = pSTBDataInfo_S->m_unHDCPKeyMaxSize;
		m_unMACMaxSize = pSTBDataInfo_S->m_unMACMaxSize;
		m_unChipIDMaxSize = MAX_CHIPID_LEN;
		m_unSTBDataMaxSize = MAX_INDIVI_RETURN_LEN;
		m_unPVRFlagMaxSize = pSTBDataInfo_S->m_unPVRFlagMaxSize;
		m_unCustomerCodeMaxSize = pSTBDataInfo_S->m_unCustomerCodeMaxSize;
		m_unPefDataMaxSize = pSTBDataInfo_S->m_unPefDataMaxSize;
		
		APAssert(pSTBDataInfo_S->m_unDataSize > (m_unSNMaxSize + m_unMACMaxSize + m_unHDCPKeyMaxSize + m_unChipIDMaxSize + m_unSTBDataMaxSize + m_unPVRFlagMaxSize));
		
		m_unSNStartAddr = pSTBDataInfo_S->m_unStartAddress;
		m_unHDCPStartAddr = m_unSNStartAddr + m_unSNMaxSize;
		m_unMACStartAddr = m_unHDCPStartAddr + m_unHDCPKeyMaxSize;
		m_unChipIDAddr = m_unMACStartAddr + m_unMACMaxSize;
		m_unSTBDataAddr = m_unChipIDAddr + m_unChipIDMaxSize;		
		m_unPVRFlagAddr = m_unSTBDataAddr + m_unSTBDataMaxSize;		
		m_unCustomerCodeAddr = m_unPVRFlagAddr + m_unPVRFlagMaxSize;
		m_unPefDataAddr = pSTBDataInfo_S->m_unStartAddress + (0x10000 - m_unPefDataMaxSize);
		
		SetIFCPAddress( 0, 0 );
		m_unAllWriteSize = m_unSNMaxSize + m_unHDCPKeyMaxSize + m_unMACMaxSize + m_unChipIDMaxSize + m_unSTBDataMaxSize;

		ADIDebugSetLevel(STB_DATA_DEBUG_MODULE, nDebugLevel);
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]m_unSNStartAddr=0x%x,m_unHDCPStartAddr=0x%x,m_unMACStartAddr=0x%x, m_unPVRFlagAddr=0x%x, m_unCustomerCodeAddr=0x%x\n", __FUNCTION__, __LINE__, m_unSNStartAddr, m_unHDCPStartAddr, m_unMACStartAddr, m_unPVRFlagAddr, m_unCustomerCodeAddr);
	}
	else
	{
		APAssert(pSTBDataInfo_S != NULL);
	}
}

STBData::~STBData()
{
	
}

EN_STB_DATA STBData::WriteSN(unsigned char * pucSNBuf, unsigned int unSNLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucSN = NULL;
	unsigned int dwCRC = 0;

	pucSN = new unsigned char[m_unSNMaxSize];
	APAssert(pucSNBuf != NULL && pucSN != NULL);
		
	do{		
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]SN=%s,SNLen=%d\n", __FUNCTION__, __LINE__, pucSNBuf, unSNLen);

		if(pucSN == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		
		if(unSNLen >= (m_unSNMaxSize - 6))
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}
		memset(pucSN, 0, m_unSNMaxSize);
		pucSN[0] = (unSNLen >> 8) & 0xFF;
		pucSN[1] = unSNLen & 0xFF;
		memcpy(pucSN + 2, pucSNBuf, unSNLen);
		dwCRC = CalculateCRC32(pucSN, unSNLen + 2);
		pucSN[unSNLen + 2] = (dwCRC >> 24) & 0xFF;
		pucSN[unSNLen + 3] = (dwCRC >> 16) & 0xFF;
		pucSN[unSNLen + 4] = (dwCRC >> 8) & 0xFF;
		pucSN[unSNLen + 5] = dwCRC & 0xFF;
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]SN CRC=0x%x\n", __FUNCTION__, __LINE__, dwCRC);
		if (WriteFlash(m_unSNStartAddr, pucSN, (unSNLen + 6)) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucSN != NULL)
	{
		delete [] pucSN;
		pucSN = NULL;
	}
	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);
	
	return en_Err;
}

EN_STB_DATA STBData::ReadSN(char * pSNBuf, unsigned int unSNLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucSN = NULL;
	unsigned int unSNActLen = 0;
	unsigned int unIndex = 0;
	unsigned int dwSNCRC = 0;
	unsigned int dwSNOrgCRC = 0;

	pucSN = new unsigned char[m_unSNMaxSize];
	APAssert(pSNBuf != NULL && pucSN != NULL);
		
	do{
		if(pucSN == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		
		memset(pucSN, 0, m_unSNMaxSize);
		if(ADIFlashRead(m_unSNStartAddr, pucSN, m_unSNMaxSize) != ADI_SUCCESS)
		{
			en_Err = E_DATA_READ_FLASH_FAIL;
			break;
		}

		unSNActLen = (pucSN[unIndex] << 8) | pucSN[unIndex + 1];
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]unSNActLen=%d,unSNLen=%d\n", __FUNCTION__, __LINE__, unSNActLen, unSNLen);
		if(unSNLen <= unSNActLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		dwSNCRC = CalculateCRC32(pucSN, unSNActLen + 2);
		unIndex += unSNActLen + 2;
		dwSNOrgCRC = (pucSN[unIndex] << 24) | (pucSN[unIndex + 1] << 16) | (pucSN[unIndex + 2] << 8) | pucSN[unIndex + 3];
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]dwSNCRC=0x%x,dwSNOrgCRC=0x%x\n", __FUNCTION__, __LINE__, dwSNCRC, dwSNOrgCRC);
		if(dwSNCRC != dwSNOrgCRC)
		{
			en_Err = E_DATA_CRC_CHECK_FAIL;
			break;
		}

		memcpy(pSNBuf, pucSN + 2, unSNActLen);
		pSNBuf[unSNActLen] = '\0';
		en_Err = E_DATA_SUCCESS;
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]SN=%s\n", __FUNCTION__, __LINE__, pSNBuf);
	}while(0);

	if(pucSN != NULL)
	{
		delete [] pucSN;
		pucSN = NULL;
	}


	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);
	
	return en_Err;
}

EN_STB_DATA STBData::WriteHDCPKey(unsigned char * pucHDCPBuf, unsigned int unHDCPLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucHDCP = NULL;
	unsigned int dwCRC = 0;

	pucHDCP = new unsigned char [m_unHDCPKeyMaxSize];
	APAssert(pucHDCPBuf != NULL && pucHDCP != NULL);

	do{
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]HDCPLen=%d\n", __FUNCTION__, __LINE__, unHDCPLen);
		if(pucHDCP == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		if(unHDCPLen >= (m_unHDCPKeyMaxSize - 6))
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}
		memset(pucHDCP, 0, m_unHDCPKeyMaxSize);
		pucHDCP[0] = (unHDCPLen >> 8) & 0xFF;
		pucHDCP[1] = unHDCPLen & 0xFF;
		memcpy(pucHDCP + 2, pucHDCPBuf, unHDCPLen);
		dwCRC = CalculateCRC32(pucHDCP, unHDCPLen + 2);
		pucHDCP[unHDCPLen + 2] = (dwCRC >> 24) & 0xFF;
		pucHDCP[unHDCPLen + 3] = (dwCRC >> 16) & 0xFF;
		pucHDCP[unHDCPLen + 4] = (dwCRC >> 8) & 0xFF;
		pucHDCP[unHDCPLen + 5] = dwCRC & 0xFF;

		if (WriteFlash(m_unHDCPStartAddr, pucHDCP, (unHDCPLen + 6)) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucHDCP != NULL)
	{
		delete [] pucHDCP;
	}
	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);
	
	return en_Err;
}

EN_STB_DATA STBData::ReadHDCPKey(unsigned char * pucHDCPBuf, unsigned int unHDCPLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucHDCP = NULL;
	unsigned int unHDCPActLen = 0;
	unsigned int unIndex = 0;
	unsigned int dwHDCPCRC = 0;
	unsigned int dwHDCPOrgCRC = 0;

	pucHDCP = new unsigned char [m_unHDCPKeyMaxSize];
	APAssert(pucHDCPBuf != NULL && pucHDCP != NULL);
		
	do{
		if(pucHDCP == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucHDCP, 0, m_unHDCPKeyMaxSize);
		if(ADIFlashRead(m_unHDCPStartAddr, pucHDCP, m_unHDCPKeyMaxSize) != ADI_SUCCESS)
		{
			en_Err = E_DATA_READ_FLASH_FAIL;
			break;
		}

		unHDCPActLen = (pucHDCP[unIndex] << 8) | pucHDCP[unIndex + 1];
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]unHDCPActLen=%d,unHDCPLen=%d\n", __FUNCTION__, __LINE__, unHDCPActLen, unHDCPLen);
		if(unHDCPLen < unHDCPActLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		dwHDCPCRC = CalculateCRC32(pucHDCP, unHDCPActLen + 2);
		unIndex += (unHDCPActLen + 2);
		dwHDCPOrgCRC = (pucHDCP[unIndex] << 24) | (pucHDCP[unIndex + 1] << 16) | (pucHDCP[unIndex + 2] << 8) | pucHDCP[unIndex + 3];
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]dwHDCPCRC=0x%x,dwHDCPOrgCRC=0x%x\n", __FUNCTION__, __LINE__, dwHDCPCRC, dwHDCPOrgCRC);
		if(dwHDCPCRC != dwHDCPOrgCRC)
		{
			en_Err = E_DATA_CRC_CHECK_FAIL;
			break;
		}

		memcpy(pucHDCPBuf, pucHDCP + 2, unHDCPActLen);
		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucHDCP != NULL)
	{
		delete [] pucHDCP;
	}

	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);
	
	return en_Err;
}

EN_STB_DATA STBData::WriteMAC(unsigned char * pucMACBuf, unsigned int unMACLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucMAC = NULL;
	unsigned int dwCRC = 0;

	pucMAC = new unsigned char [m_unMACMaxSize];
	APAssert(pucMACBuf != NULL);
			
	do{
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]MACLen=%d\n", __FUNCTION__, __LINE__, unMACLen);
		if(pucMAC == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		
		if(unMACLen >= (m_unMACMaxSize - 6))
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}
		memset(pucMAC, 0, m_unMACMaxSize);
		pucMAC[0] = (unMACLen >> 8) & 0xFF;
		pucMAC[1] = unMACLen & 0xFF;
		memcpy(pucMAC + 2, pucMACBuf, unMACLen);
		dwCRC = CalculateCRC32(pucMAC, unMACLen + 2);
		pucMAC[unMACLen + 2] = (dwCRC >> 24) & 0xFF;
		pucMAC[unMACLen + 3] = (dwCRC >> 16) & 0xFF;
		pucMAC[unMACLen + 4] = (dwCRC >> 8) & 0xFF;
		pucMAC[unMACLen + 5] = dwCRC & 0xFF;

		if (WriteFlash(m_unMACStartAddr, pucMAC, (unMACLen + 6)) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucMAC != NULL)
	{
		delete [] pucMAC;
	}

	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);

	return en_Err;
}

EN_STB_DATA STBData::ReadMAC(char * pMACBuf, unsigned int unMACLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucMAC = NULL;
	unsigned int unMACActLen = 0;
	unsigned int unIndex = 0;
	unsigned int dwMACCRC = 0;
	unsigned int dwMACOrgCRC = 0;

	pucMAC = new unsigned char [m_unMACMaxSize];
	APAssert(pMACBuf != NULL && pucMAC != NULL);
			
	do{
		if(pucMAC == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucMAC, 0, m_unMACMaxSize);
		if(ADIFlashRead(m_unMACStartAddr, pucMAC, m_unMACMaxSize) != ADI_SUCCESS)
		{
			en_Err = E_DATA_READ_FLASH_FAIL;
			break;
		}

		unMACActLen = (pucMAC[unIndex] << 8) | pucMAC[unIndex + 1];
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]unMACActLen=%d,unMACLen=%d\n", __FUNCTION__, __LINE__, unMACActLen, unMACLen);
		if(unMACLen <= unMACActLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		dwMACCRC = CalculateCRC32(pucMAC, unMACActLen + 2);
		unIndex += (unMACActLen + 2);
		dwMACOrgCRC = (pucMAC[unIndex] << 24) | (pucMAC[unIndex + 1] << 16) | (pucMAC[unIndex + 2] << 8) | pucMAC[unIndex + 3];
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]dwMACCRC=0x%x,dwMACOrgCRC=0x%x\n", __FUNCTION__, __LINE__, dwMACCRC, dwMACOrgCRC);
		if(dwMACCRC != dwMACOrgCRC)
		{
			en_Err = E_DATA_CRC_CHECK_FAIL;
			break;
		}

		memcpy(pMACBuf, pucMAC + 2, unMACActLen);
		pMACBuf[unMACActLen] = '\0';
		en_Err = E_DATA_SUCCESS;
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]MAC=%s\\n", __FUNCTION__, __LINE__, pMACBuf);
	}while(0);

	if(pucMAC != NULL)
	{
		delete [] pucMAC;
	}

	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);

	return en_Err;
}

EN_STB_DATA STBData::WritePEFAndIFCP(unsigned char * pucBuf, unsigned int unLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucPEF = NULL;
	unsigned int unPEFLen = 0;
	unsigned int unIFCPLen = 0;
	int pos = 0;
	DWORD dwCRC = 0;

	pucPEF = new unsigned char[m_unPefDataMaxSize];
	APAssert(pucBuf != NULL && pucPEF != NULL);

			
	do{
		if(pucPEF == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucPEF, 0, m_unPefDataMaxSize);
		
		//unPEFLen(2B) + PEFData + unIFCPLen(4B) + IFCPData
		unPEFLen = (pucBuf[pos] << 8) | pucBuf[pos+1];
		pos += (unPEFLen + 2);
		unIFCPLen = (pucBuf[pos] << 8) | pucBuf[pos+1];
		pos += (unIFCPLen + 2);
		if(pos > unLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		if(unPEFLen > (m_unPefDataMaxSize - 6) || unIFCPLen > m_unIFCPSize)
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}

		memcpy(pucPEF, pucBuf, unPEFLen + 2);
		dwCRC = CalculateCRC32(pucPEF, unPEFLen + 2);
		pucPEF[unPEFLen+2] = (dwCRC >> 24) & 0xFF;
		pucPEF[unPEFLen+3] = (dwCRC >> 16) & 0xFF;
		pucPEF[unPEFLen+4] = (dwCRC >> 8) & 0xFF;
		pucPEF[unPEFLen+5] = dwCRC & 0xFF;

		if (WriteFlash(m_unPefDataAddr, pucPEF, (unPEFLen+6)) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		if (WriteFlash(m_unIFCPAddr, &pucBuf[2+unPEFLen+2], unIFCPLen) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucPEF != NULL)
	{
		delete[] pucPEF;
	}
	
	return en_Err;
}

EN_STB_DATA STBData::WritePEF(unsigned char * pucBuf, unsigned int unLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	int pos = 0;
	unsigned int unPEFLen = 0;
	unsigned char *pucPEF = NULL;
	DWORD dwCRC = 0;
	
	pucPEF = new unsigned char[m_unPefDataMaxSize];
	APAssert(pucBuf != NULL && pucPEF != NULL);

			
	do{
		//unPEFLen(2B) + PEFData
		unPEFLen = (pucBuf[pos] << 8) | pucBuf[pos+1];
		pos += (unPEFLen + 2);
		if(pos > unLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		if(unPEFLen > (m_unPefDataMaxSize - 6))
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}
		
		memcpy(pucPEF, pucBuf, unPEFLen + 2);
		dwCRC = CalculateCRC32(pucBuf, unPEFLen + 2);
		pucPEF[unPEFLen+2] = (dwCRC >> 24) & 0xFF;
		pucPEF[unPEFLen+3] = (dwCRC >> 16) & 0xFF;
		pucPEF[unPEFLen+4] = (dwCRC >> 8) & 0xFF;
		pucPEF[unPEFLen+5] = dwCRC & 0xFF;

		if (WriteFlash(m_unPefDataAddr, pucPEF, (unPEFLen+6)) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucPEF != NULL)
	{
		delete[] pucPEF;
	}
	
	return en_Err;
}


EN_STB_DATA STBData::WriteIFCP(unsigned char * pucBuf, unsigned int unLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned int unIFCPLen = 0;
	int pos = 0;
	DWORD dwCRC = 0;

	APAssert(pucBuf != NULL);

			
	do{
		//unIFCPLen(4B) + IFCPData		
		unIFCPLen = (pucBuf[pos] << 8) | pucBuf[pos+1];
		pos += (unIFCPLen + 2);
		if(pos > unLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		if( unIFCPLen > m_unIFCPSize)
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}

		if (WriteFlash(m_unIFCPAddr, &pucBuf[2], unIFCPLen) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);

		if (WriteFlash(m_unIFCPAddr + m_unIFCPSize, &pucBuf[2], unIFCPLen) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}
		
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);

		en_Err = E_DATA_SUCCESS;
	}while(0);

	return en_Err;
}


EN_STB_DATA STBData::ReadPEF(unsigned char * pPEFBuf, unsigned int unPEFLen, unsigned int & unPEFActLen )
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucPEF = NULL;
	unsigned int unIndex = 0;
	DWORD dwPEFCRC = 0;
	DWORD dwPEFOrgCRC = 0;

	pucPEF = new unsigned char[m_unPefDataMaxSize];
	APAssert(pPEFBuf != NULL && pucPEF != NULL);
			
	do{
		if(pucPEF == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucPEF, 0, m_unPefDataMaxSize);
		
		if(ADIFlashRead(m_unPefDataAddr, pucPEF, m_unPefDataMaxSize) != ADI_SUCCESS)
		{
			en_Err = E_DATA_READ_FLASH_FAIL;
			break;
		}

		unPEFActLen = (pucPEF[unIndex] << 8) | pucPEF[unIndex + 1];
		
		if(unPEFLen <= unPEFActLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		dwPEFCRC = CalculateCRC32(pucPEF, unPEFActLen + 2);
		unIndex += (unPEFActLen + 2);
		dwPEFOrgCRC = (pucPEF[unIndex] << 24) | (pucPEF[unIndex + 1] << 16) | (pucPEF[unIndex + 2] << 8) | pucPEF[unIndex + 3];
		
		if(dwPEFCRC != dwPEFOrgCRC)
		{
			en_Err = E_DATA_CRC_CHECK_FAIL;
			break;
		}

		memcpy(pPEFBuf, &pucPEF[2], unPEFActLen);
		pPEFBuf[unPEFActLen] = '\0';
		en_Err = E_DATA_SUCCESS;		
	}while(0);

	if(pucPEF != NULL)
	{
		delete[] pucPEF;
	}

	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);

	return en_Err;
}

EN_STB_DATA STBData::WriteChipID(unsigned char * pucChipIDBuf, unsigned int unChipIDLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucChipID = NULL;
	DWORD dwCRC = 0;

	pucChipID = new unsigned char[m_unChipIDMaxSize];
	APAssert(pucChipIDBuf != NULL && pucChipID != NULL);
			
	do{
		if(pucChipID == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucChipID, 0, m_unChipIDMaxSize);
		
		ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]unChipIDLen=%d\n", __FUNCTION__, __LINE__, unChipIDLen);
		
		if(unChipIDLen >= (m_unChipIDMaxSize - 6))
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}
		
		pucChipID[0] = (unChipIDLen >> 8) & 0xFF;
		pucChipID[1] = unChipIDLen & 0xFF;
		memcpy(&pucChipID[2], pucChipIDBuf, unChipIDLen);
		dwCRC = CalculateCRC32(pucChipID, unChipIDLen + 2);
		pucChipID[unChipIDLen + 2] = (dwCRC >> 24) & 0xFF;
		pucChipID[unChipIDLen + 3] = (dwCRC >> 16) & 0xFF;
		pucChipID[unChipIDLen + 4] = (dwCRC >> 8) & 0xFF;
		pucChipID[unChipIDLen + 5] = dwCRC & 0xFF;

		if (WriteFlash(m_unChipIDAddr, pucChipID, (unChipIDLen + 6)) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucChipID != NULL)
	{
		delete[] pucChipID;
	}

	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);

	return en_Err;
}

EN_STB_DATA STBData::ReadChipID(unsigned char * pChipIDBuf, unsigned int unChipIDLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucChipID = NULL;
	unsigned int unChipIDActLen = 0;
	unsigned int unIndex = 0;
	DWORD dwChipIDCRC = 0;
	DWORD dwChipIDOrgCRC = 0;

	pucChipID = new unsigned char[m_unChipIDMaxSize];
	APAssert(pChipIDBuf != NULL && pucChipID != NULL);

	do{
		if(pucChipID == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucChipID, 0, m_unChipIDMaxSize);
		
		if(ADIFlashRead(m_unChipIDAddr, pucChipID, m_unChipIDMaxSize) != ADI_SUCCESS)
		{
			en_Err = E_DATA_READ_FLASH_FAIL;
			break;
		}

		unChipIDActLen = (pucChipID[unIndex] << 8) | pucChipID[unIndex + 1];
		if(unChipIDLen <= unChipIDActLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		dwChipIDCRC = CalculateCRC32(pucChipID, unChipIDActLen + 2);
		unIndex += (unChipIDActLen + 2);
		dwChipIDOrgCRC = (pucChipID[unIndex] << 24) | (pucChipID[unIndex + 1] << 16) | (pucChipID[unIndex + 2] << 8) | pucChipID[unIndex + 3];

		if(dwChipIDCRC != dwChipIDOrgCRC)
		{
			en_Err = E_DATA_CRC_CHECK_FAIL;
			break;
		}

		memcpy(pChipIDBuf, &pucChipID[2], unChipIDActLen);
		pChipIDBuf[unChipIDActLen] = '\0';
		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucChipID != NULL)
	{
		delete[] pucChipID;
	}

	ADIDebug(STB_DATA_DEBUG_MODULE, STB_DATA_DEBUG_LEVEL, "[%s][%d]en_Err=%d\n", __FUNCTION__, __LINE__, en_Err);

	return en_Err;
}

EN_STB_DATA STBData::WriteSTBData(unsigned char * pucSTBDataBuf, unsigned int unSTBDataLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucSTBData = NULL;
	DWORD dwCRC = 0;

	pucSTBData = new unsigned char[m_unSTBDataMaxSize];
	APAssert(pucSTBDataBuf != NULL && pucSTBData != NULL);

	do{
		if(pucSTBData == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucSTBData, 0, m_unSTBDataMaxSize);
		
		if(unSTBDataLen >= (m_unSTBDataMaxSize - 6))
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}
		
		pucSTBData[0] = (unSTBDataLen >> 8) & 0xFF;
		pucSTBData[1] = unSTBDataLen & 0xFF;
		memcpy(&pucSTBData[2], pucSTBDataBuf, unSTBDataLen);
		dwCRC = CalculateCRC32(pucSTBData, unSTBDataLen + 2);
		pucSTBData[unSTBDataLen + 2] = (dwCRC >> 24) & 0xFF;
		pucSTBData[unSTBDataLen + 3] = (dwCRC >> 16) & 0xFF;
		pucSTBData[unSTBDataLen + 4] = (dwCRC >> 8) & 0xFF;
		pucSTBData[unSTBDataLen + 5] = dwCRC & 0xFF;

		if (WriteFlash(m_unSTBDataAddr, pucSTBData, (unSTBDataLen + 6)) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucSTBData != NULL)
	{
		delete[] pucSTBData;
	}
	
	return en_Err;
}

EN_STB_DATA STBData::ReadSTBData(unsigned char * pSTBDataBuf, unsigned int unSTBDataLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucSTBData = NULL;
	unsigned int unSTBDataActLen = 0;
	unsigned int unIndex = 0;
	DWORD dwSTBDataCRC = 0;
	DWORD dwSTBDataOrgCRC = 0;

	pucSTBData = new unsigned char[m_unSTBDataMaxSize];
	APAssert(pSTBDataBuf != NULL && pucSTBData != NULL);

	do{
		if(pucSTBData == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucSTBData, 0, m_unSTBDataMaxSize);
		
		if(ADIFlashRead(m_unSTBDataAddr, pucSTBData, m_unSTBDataMaxSize) != ADI_SUCCESS)
		{
			en_Err = E_DATA_READ_FLASH_FAIL;
			break;
		}

		unSTBDataActLen = (pucSTBData[unIndex] << 8) | pucSTBData[unIndex + 1];
		if(unSTBDataLen <= unSTBDataActLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}

		dwSTBDataCRC = CalculateCRC32(pucSTBData, unSTBDataActLen + 2);
		unIndex += (unSTBDataActLen + 2);
		dwSTBDataOrgCRC = (pucSTBData[unIndex] << 24) | (pucSTBData[unIndex + 1] << 16) | (pucSTBData[unIndex + 2] << 8) | pucSTBData[unIndex + 3];
		if(dwSTBDataCRC != dwSTBDataOrgCRC)
		{
			en_Err = E_DATA_CRC_CHECK_FAIL;
			break;
		}

		memcpy(pSTBDataBuf, &pucSTBData[2], unSTBDataActLen);
		pSTBDataBuf[unSTBDataActLen] = '\0';
		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucSTBData != NULL)
	{
		delete[] pucSTBData;
	}

	return en_Err;
}

EN_STB_DATA STBData::WritePVRFlag(unsigned char * pucPVRFlagBuf, unsigned int unPVRFlagLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucPVRFlag = NULL;
	DWORD dwCRC = 0;
	
	pucPVRFlag = new unsigned char[m_unPVRFlagMaxSize];
	APAssert(pucPVRFlagBuf != NULL);
	do
	{
		if(pucPVRFlag == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucPVRFlag, 0, m_unPVRFlagMaxSize);
		
		if(unPVRFlagLen > MAX_PVR_FLAG_LEN - 6)
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}

		pucPVRFlag[0] = (unPVRFlagLen >> 8) & 0xff;
		pucPVRFlag[1] = unPVRFlagLen & 0xff;
		memcpy(&pucPVRFlag[2], pucPVRFlagBuf, unPVRFlagLen);
		dwCRC = CalculateCRC32(pucPVRFlag, unPVRFlagLen+2);
		pucPVRFlag[unPVRFlagLen+2] = (dwCRC >> 24) & 0xff;
		pucPVRFlag[unPVRFlagLen+3] = (dwCRC >> 16) & 0xff;
		pucPVRFlag[unPVRFlagLen+4] = (dwCRC >> 8) & 0xff;
		pucPVRFlag[unPVRFlagLen+5] = dwCRC & 0xff;

		if(WriteFlash(m_unPVRFlagAddr, pucPVRFlag, unPVRFlagLen+6) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucPVRFlag != NULL)
	{
		delete[] pucPVRFlag;
	}

	return en_Err;
}

EN_STB_DATA STBData::ReadPVRFlag(unsigned char * pPVRFlagBuf, unsigned int unPVRFlagLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucPVRFlag = NULL;
	unsigned int unPVRFlagActLen = 0;
	DWORD dwActCRC = 0;
	DWORD dwCRC = 0;

	pucPVRFlag = new unsigned char[m_unPVRFlagMaxSize];
	APAssert(pPVRFlagBuf != NULL && pucPVRFlag != NULL);
	do
	{
		if(pucPVRFlag == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucPVRFlag, 0, m_unPVRFlagMaxSize);
		
		if(ADIFlashRead(m_unPVRFlagAddr, pucPVRFlag, m_unPVRFlagMaxSize) != ADI_SUCCESS)
		{
			en_Err = E_DATA_READ_FLASH_FAIL;
			break;
		}
		unPVRFlagActLen = (pucPVRFlag[0] << 8) | pucPVRFlag[1];
		if(unPVRFlagActLen > unPVRFlagLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}
		dwCRC = CalculateCRC32(pucPVRFlag, unPVRFlagActLen+2);
		dwActCRC = (pucPVRFlag[unPVRFlagActLen+2] << 24) | (pucPVRFlag[unPVRFlagActLen+3] << 16) | (pucPVRFlag[unPVRFlagActLen+4] << 8) | pucPVRFlag[unPVRFlagActLen+5];
		if(dwActCRC != dwCRC)
		{
			en_Err = E_DATA_CRC_CHECK_FAIL;
			break;
		}

		memcpy(pPVRFlagBuf, &pucPVRFlag[2], unPVRFlagActLen);
		en_Err = E_DATA_SUCCESS;
	}while(0);

	if(pucPVRFlag != NULL)
	{
		delete[] pucPVRFlag;
	}

	return en_Err;
}

EN_STB_DATA STBData::WriteCustomerCode(unsigned char * pucCustomerCodeBuf, unsigned int unCustomerCodeLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucCustomerCode = NULL;
	unsigned int dwCRC = 0;

	pucCustomerCode = new unsigned char[m_unCustomerCodeMaxSize];
	APAssert(pucCustomerCodeBuf != NULL && pucCustomerCode != NULL);
	
	do
	{
		if(pucCustomerCode == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		
		if (unCustomerCodeLen > m_unCustomerCodeMaxSize - 6)
		{
			en_Err = E_DATA_LENGTH_TOO_LONG;
			break;
		}
		memset(pucCustomerCode, 0, m_unCustomerCodeMaxSize);
		pucCustomerCode[0] = (unCustomerCodeLen >> 8) & 0xff;
		pucCustomerCode[1] = unCustomerCodeLen & 0xff;
		memcpy(pucCustomerCode + 2, pucCustomerCodeBuf, unCustomerCodeLen);
		dwCRC = CalculateCRC32(pucCustomerCode, unCustomerCodeLen + 2);
		pucCustomerCode[unCustomerCodeLen + 2] = (dwCRC >> 24) & 0xff;
		pucCustomerCode[unCustomerCodeLen + 3] = (dwCRC >> 16) & 0xff;
		pucCustomerCode[unCustomerCodeLen + 4] = (dwCRC >> 8) & 0xff;
		pucCustomerCode[unCustomerCodeLen + 5] = dwCRC & 0xff;

		if (WriteFlash(m_unCustomerCodeAddr, pucCustomerCode, unCustomerCodeLen + 6) == 0)
		{
			en_Err = E_DATA_WRITE_FLASH_FAIL;
			break;
		}

		en_Err = E_DATA_SUCCESS;
	} while (0);

	if(pucCustomerCode != NULL)
	{
		delete [] pucCustomerCode;
	}
	
	return en_Err;
}

EN_STB_DATA STBData::ReadCustomerCode(unsigned char * pucCustomerCodeBuf, unsigned int unCustomerCodeLen)
{
	EN_STB_DATA en_Err = E_DATA_MAX;
	unsigned char *pucCustomerCode = NULL;
	unsigned int unCustomerCodeActLen = 0;
	unsigned int dwActCRC = 0;
	unsigned int dwCRC = 0;

	pucCustomerCode = new unsigned char[m_unCustomerCodeMaxSize];
	APAssert(pucCustomerCodeBuf != NULL && pucCustomerCode != NULL);
	do
	{
		if(pucCustomerCode == NULL)
		{
			en_Err = E_DATA_OUT_OF_MEMORY;
			break;
		}
		memset(pucCustomerCode, 0, m_unCustomerCodeMaxSize);
		if (ADIFlashRead(m_unCustomerCodeAddr, pucCustomerCode, m_unCustomerCodeMaxSize) != ADI_SUCCESS)
		{
			en_Err = E_DATA_READ_FLASH_FAIL;
			break;
		}

		unCustomerCodeActLen = (pucCustomerCode[0] << 8) | pucCustomerCode[1];
		if (unCustomerCodeActLen > unCustomerCodeLen)
		{
			en_Err = E_DATA_LENGTH_NOT_ENOUGH;
			break;
		}
		dwCRC = CalculateCRC32(pucCustomerCode, unCustomerCodeActLen + 2);
		dwActCRC = (pucCustomerCode[unCustomerCodeActLen + 2] << 24) | (pucCustomerCode[unCustomerCodeActLen + 3] << 16) | (pucCustomerCode[unCustomerCodeActLen + 4] << 8) | pucCustomerCode[unCustomerCodeActLen + 5];
		if (dwActCRC != dwCRC)
		{
			en_Err = E_DATA_CRC_CHECK_FAIL;
			break;
		}

		memcpy(pucCustomerCodeBuf, pucCustomerCode + 2, unCustomerCodeActLen);
		en_Err = E_DATA_SUCCESS;
	} while (0);

	if(pucCustomerCode != NULL)
	{
		delete [] pucCustomerCode;
	}

	return en_Err;
}

unsigned int STBData::CalculateCRC32 ( unsigned char* pbData, unsigned int unSize )
{
	unsigned int ii = 0;
	unsigned int jj = 0;
	unsigned int dwCRC = 0;
	unsigned int dwCrc32 = 0xffffffff;
  
	for(ii=0; ii<unSize; ii++)
	{
		for(jj=0; jj<8; jj++)
		{
			if(((pbData[ii]>>(7-jj))&0x01))
				dwCrc32 ^= 1;

			if(dwCrc32 & 1)
				dwCrc32 = ((dwCrc32 >> 1) ^ CRC_FLAG);
			else
				dwCrc32 >>= 1;
		}
	}
  
	for(ii=0; ii<32; ii++)
	{
		if((dwCrc32 >> ii) & 1)
		{
			dwCRC <<= 1;
			dwCRC |= 1;
		}
		else
		{
			dwCRC <<=1;
		}
	}

	return dwCRC;		
}

unsigned int STBData::WriteFlash(unsigned int unStartAddress, unsigned char * pucBuf, unsigned int uDataLength)
{
	unsigned int unRet = 0;

	if (ADIFlashWrite(unStartAddress, pucBuf, uDataLength) == ADI_SUCCESS)
	{
		unsigned int unOffset = 0;
		unsigned int unReadLength = 0;
		unsigned char aucTmpBuf[256] = {0};

		while (unOffset < uDataLength)
		{
			unReadLength = uDataLength - unOffset > 256 ? 256 : uDataLength - unOffset;
			if (ADIFlashRead(unStartAddress + unOffset, aucTmpBuf, unReadLength) == ADI_SUCCESS)
			{
				if (memcmp(pucBuf + unOffset, aucTmpBuf, unReadLength) != 0)
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

		if (unOffset == uDataLength)
		{
			unRet = 1;
		}
	}

	return unRet;
}

EN_STB_DATA STBData::EraseFlashSpace(void)
{
	EN_STB_DATA enRet = E_DATA_FAIL;

	ADIFlashEraseSpace(m_unSNStartAddr , m_unAllWriteSize);
	enRet = E_DATA_SUCCESS;


	return enRet;
}

void STBData::SetIFCPAddress(unsigned int unAddr, unsigned int unSize)
{
	m_unIFCPAddr = unAddr;
	m_unIFCPSize = unSize;
}


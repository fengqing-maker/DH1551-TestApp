#include <stdio.h>
#include <string.h>
#include "adi_toolset.h"
#include "adi_secure.h"
#include "AuraTypedef.h"
#include "STBDataInterface.h"
#include "adi_hdmi.h"
#include "adi_fs.h"
#include "ReturnfileType.h"

extern void WriteLog1(char * format, ...);

unsigned int ConstructReturnFile(unsigned char aucStr[], unsigned int unLen)
{
	unsigned int unDataLen = 0;
	unsigned int unSNLen = 0;
	unsigned int unChipIDLen = 0;
	unsigned int unMacLen = 0;
	char acSN[32] = {0};
	ADICHIPID_S stChipID = {0};
	char acMac[32] = {0};
	static unsigned char aucTsc[128] = {0};
	static unsigned int unTscLen = 0;
	
	if (aucStr != NULL)
	{
		if(E_DATA_SUCCESS == ReadSN(acSN, sizeof(acSN)))
		{
			unSNLen = strlen(acSN);			
		}
		
		if(ADIGetChipID(&stChipID)== ADI_SUCCESS)
		{
			unChipIDLen = stChipID.m_nLength - 4;
		}
		//WriteLog1("ConstructReturnFile-->Get Chip Length = %d\r\n",unChipIDLen);

		if ( unTscLen == 0 )
		{
			unsigned char aucCcc[128] = {0};
			unsigned int unCccLen = 0;
			if(ADI_SUCCESS != ADISecureGetMACData(aucTsc, &unTscLen))
			//if(ADI_SUCCESS != ADISecureGetCCCKDataAndMACData(aucCcc,&unCccLen, aucTsc, &unTscLen))
			{
				unTscLen = 0;
			}
		}

		if(unSNLen > 0 && unChipIDLen > 0 && unTscLen > 0)
		{
			//ChipIDLen(2B) + ChipID + SNLen(2B) + SN + TscLen + TscData
			
			aucStr[unDataLen] = (BYTE)((unChipIDLen >> 8) & 0xFF);
			aucStr[unDataLen + 1] = (BYTE)(unChipIDLen & 0xFF);
			memcpy(&aucStr[unDataLen + 2], &stChipID.m_szChipID[4], unChipIDLen);
			unDataLen += (unChipIDLen + 2);
			
			//WriteLog1("ConstructReturnFile After Chip, unDataLen = %d\r\n",unDataLen);
			aucStr[unDataLen] = (BYTE)((unSNLen >> 8) & 0xFF);
			aucStr[unDataLen + 1] = (BYTE)(unSNLen & 0xFF);
			memcpy(&aucStr[unDataLen + 2], acSN, unSNLen);
			unDataLen += (unSNLen + 2);
			
			//WriteLog1("ConstructReturnFile After SN, unDataLen = %d\r\n",unDataLen);
			aucStr[unDataLen] = (BYTE)((unTscLen >> 8) & 0xFF);
			aucStr[unDataLen + 1] = (BYTE)(unTscLen & 0xFF);
			memcpy(&aucStr[unDataLen + 2], aucTsc, unTscLen);
			unDataLen += (unTscLen + 2);
			
			//WriteLog1("ConstructReturnFile After TS, unDataLen = %d\r\n",unDataLen);
		}
	}

	return unDataLen;
}

unsigned int HDMIKeyEncrypt(unsigned char *pBuffer, unsigned int unLen)
{	
	unsigned int unRet = 0;

	if( pBuffer != NULL && unLen <= 512 )
	{		
		ADIHDMIEncryptHdcpKey_S sHdmiEncryptHdcpKey;
		memset(&sHdmiEncryptHdcpKey, 0x00, sizeof(ADIHDMIEncryptHdcpKey_S));

		memcpy(sHdmiEncryptHdcpKey.ucInEncryptKey, pBuffer, unLen);

		if( ADIHDMIEncryptHdcpKey(&sHdmiEncryptHdcpKey) == ADI_SUCCESS )//maxlen=312
		{
			memset(pBuffer, 0, unLen);
			
			memcpy(pBuffer, "CASTPAL", strlen("CASTPAL"));

			memcpy(pBuffer + strlen("CASTPAL"), sHdmiEncryptHdcpKey.ucOutEncryptKey, unLen - strlen("CASTPAL"));

			unRet = 1;
		}
	}

	return unRet;
}

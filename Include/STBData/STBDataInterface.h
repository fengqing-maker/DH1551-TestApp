/*
 * STBDataInterface.h
 *
 *  Created on: 2015-9-21
 *      Author: linc
 */

#ifndef STBDATAINTERFACE_H_
#define STBDATAINTERFACE_H_

#define MAX_SN_LEN (32)
#define MAX_MAC_LEN (32)
#define MAX_HDCP_LEN (520)
#define MAX_CHIPID_LEN (32)
#define MAX_INDIVI_RETURN_LEN (128)
#define MAX_PVR_FLAG_LEN (32)
#define MAX_CUSTOMER_CODE_LEN (32)
#define MAX_PEFDATA_LEN (0x400)

#define STB_DATA_DEBUG_MODULE "STB_DATA"
#define STB_DATA_DEBUG_LEVEL ERROR_LEVEL

typedef enum
{
	E_DATA_SUCCESS = 0,
	E_DATA_PARAM_ERROR,
	E_DATA_NOT_CONFIG_ADDRESS,
	E_DATA_READ_FLASH_FAIL,
	E_DATA_WRITE_FLASH_FAIL,
	E_DATA_LENGTH_NOT_ENOUGH,
	E_DATA_LENGTH_TOO_LONG,
	E_DATA_CRC_CHECK_FAIL,
	E_DATA_FAIL,
	E_DATA_OUT_OF_MEMORY,
	E_DATA_MAX
}EN_STB_DATA;

typedef struct _STBDataInfo{
	unsigned int m_unStartAddress;
	unsigned int m_unDataSize;
	unsigned int m_unSNMaxSize;	
	unsigned int m_unHDCPKeyMaxSize;
	unsigned int m_unMACMaxSize;
	unsigned int m_unPVRFlagMaxSize;
	unsigned int m_unCustomerCodeMaxSize;
	unsigned int m_unPefDataMaxSize;
}STBDataInfo_S;

EN_STB_DATA ConfigSTBDataInfo(unsigned int unStartAddr, unsigned int unDataSize, int nDebugLevel);
EN_STB_DATA ConfigSTBDataInfo(STBDataInfo_S *pSTBDataInfo_S, int nDebugLevel);

void SetIFCPAddress(unsigned int unAddr, unsigned int unSize);

/******************调用以下接口前,必须先调用ConfigSNDataInfo配置好地址,否则会失败*******************/
EN_STB_DATA WriteSN(unsigned char * pucSNBuf, unsigned int unSNLen);

EN_STB_DATA ReadSN(char * pSNBuf, unsigned int unSNLen);

EN_STB_DATA WriteHDCPKey(unsigned char * pucHDCPBuf, unsigned int unHDCPLen);

EN_STB_DATA ReadHDCPKey(unsigned char * pucHDCPBuf, unsigned int unHDCPLen);

EN_STB_DATA WriteMAC(unsigned char * pucMACBuf, unsigned int unMACLen);

EN_STB_DATA ReadMAC(char * pMACBuf, unsigned int unMACLen);

EN_STB_DATA WritePEFAndIFCP(unsigned char * pucBuf, unsigned int unLen);

EN_STB_DATA WritePEF(unsigned char * pucBuf, unsigned int unLen);

EN_STB_DATA WriteIFCP(unsigned char * pucBuf, unsigned int unLen);

EN_STB_DATA ReadPEF(unsigned char * pBuf, unsigned int unLen, unsigned int & unPEFActLen );

EN_STB_DATA WriteChipID(unsigned char * pucChipIDBuf, unsigned int unChipIDLen);

EN_STB_DATA ReadChipID(unsigned char * pChipIDBuf, unsigned int unChipIDLen);

EN_STB_DATA WriteSTBData(unsigned char * pucSTBDataBuf, unsigned int unSTBDataLen);

EN_STB_DATA ReadSTBData(unsigned char * pSTBDataBuf, unsigned int unSTBDataLen);

EN_STB_DATA WritePVRFlag(unsigned char * pucPVRFlagBuf, unsigned int unPVRFlagLen);

EN_STB_DATA ReadPVRFlag(unsigned char * pPVRFlagBuf, unsigned int unPVRFlagLen);

EN_STB_DATA WriteCustomerCode(unsigned char * pucCustomerCodeBuf, unsigned int unCustomerCodeLen);

EN_STB_DATA ReadCustomerCode(unsigned char * pucCustomerCodeBuf, unsigned int unCustomerCodeLen);

EN_STB_DATA EraseFlashSpace();


#endif /* STBDATAINTERFACE_H_ */

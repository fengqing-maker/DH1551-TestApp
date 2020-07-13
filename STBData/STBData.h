/*
 * STBData.h
 *
 *  Created on: 2015-9-21
 *      Author: linc
 */

#ifndef STBDATA_H_
#define STBDATA_H_

#include "STBDataInterface.h"
#include "AuraTypedef.h"

class STBData
{
public:
	STBData(unsigned int unStartAddr, unsigned int unDataSize, int nDebugLevel);
	
	STBData(STBDataInfo_S *pSTBDataInfo_S, int nDebugLevel);
	
	virtual ~STBData();

public:
	EN_STB_DATA WriteSN(unsigned char * pucSNBuf, unsigned int unSNLen);

	EN_STB_DATA ReadSN(char * pSNBuf, unsigned int unSNLen);

	EN_STB_DATA WriteHDCPKey(unsigned char * pucHDCPBuf, unsigned int unHDCPLen);

	EN_STB_DATA ReadHDCPKey(unsigned char * pucHDCPBuf, unsigned int unHDCPLen);

	EN_STB_DATA WriteMAC(unsigned char * pucMACBuf, unsigned int unMACLen);

	EN_STB_DATA ReadMAC(char * pMACBuf, unsigned int unMACLen);

	EN_STB_DATA WritePEFAndIFCP(unsigned char * pucBuf, unsigned int unLen);

	EN_STB_DATA WritePEF(unsigned char * pucBuf, unsigned int unLen);
	
	EN_STB_DATA WriteIFCP(unsigned char * pucBuf, unsigned int unLen);

	EN_STB_DATA ReadPEF(unsigned char * pPEFBuf, unsigned int unPEFLen, unsigned int & unPEFActLen );

	EN_STB_DATA WriteChipID(unsigned char * pucChipIDBuf, unsigned int unChipIDLen);

	EN_STB_DATA ReadChipID(unsigned char * pChipIDBuf, unsigned int unChipIDLen);

	EN_STB_DATA WriteSTBData(unsigned char * pucSTBDataBuf, unsigned int unSTBDataLen);

	EN_STB_DATA ReadSTBData(unsigned char * pSTBDataBuf, unsigned int unSTBDataLen);

	EN_STB_DATA WritePVRFlag(unsigned char * pucPVRFlagBuf, unsigned int unPVRFlagLen);

	EN_STB_DATA ReadPVRFlag(unsigned char * pPVRFlagBuf, unsigned int unPVRFlagLen);

	EN_STB_DATA WriteCustomerCode(unsigned char * pucCustomerCodeBuf, unsigned int unCustomerCodeLen);
	
	EN_STB_DATA ReadCustomerCode(unsigned char * pucCustomerCodeBuf, unsigned int unCustomerCodeLen);

	EN_STB_DATA EraseFlashSpace(void);

	void SetIFCPAddress(unsigned int unAddr, unsigned int unSize);
	
private:
	unsigned int CalculateCRC32(unsigned char* pbData, unsigned int unSize);
	unsigned int WriteFlash(unsigned int unStartAddress, unsigned char * pucBuf, unsigned int uDataLength);

private:
	unsigned int m_unSNStartAddr;
	unsigned int m_unHDCPStartAddr;
	unsigned int m_unMACStartAddr;
	unsigned int m_unChipIDAddr;
	unsigned int m_unSTBDataAddr;
	unsigned int m_unPVRFlagAddr;
	unsigned int m_unPefDataAddr;
	unsigned int m_unCustomerCodeAddr;

	unsigned int m_unAllWriteSize;

	unsigned int m_unIFCPAddr;
	unsigned int m_unIFCPSize;
	
	unsigned int m_unSNMaxSize;	
	unsigned int m_unHDCPKeyMaxSize;
	unsigned int m_unMACMaxSize;
	unsigned int m_unChipIDMaxSize;
	unsigned int m_unSTBDataMaxSize;
	unsigned int m_unPVRFlagMaxSize;
	unsigned int m_unCustomerCodeMaxSize;
	unsigned int m_unPefDataMaxSize;
};

#endif /* SERIALUPGRADE_H_ */


#ifndef _ADI_FLASH_H_
#define _ADI_FLASH_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADI_FLASH_MAX_PT_NAME_LEN (32)

enum
{
	ADIFLASH_ERROR_BAD_PARAMETER = ADI_FLASH_ERROR_BASE,   
	ADIFLASH_ERROR_INVALID_ADDR,
	ADIFLASH_ERROR_UNKNOWN
};

typedef struct 
{
	char         m_szPTName[ADI_FLASH_MAX_PT_NAME_LEN];        // ��������
    unsigned int m_uOffset;                                    //Flash������ƫ�ƣ���0��ʼ
	unsigned int m_uPTSize;                                    // ���������С������spare_size�Ĵ�С����λΪBYTE 
	unsigned int m_uSpareSize;                                 // ��������ռ�Ĵ�С����λΪBYTE	
	unsigned int m_uReserved0;       // ��������0   
	unsigned int m_uReserved1;       // ��������1

} ADIFLASHPartition_S;


typedef struct 
{
	unsigned int m_uVPPGPIOIndex;    // Ӳ��������·GPIO�������� 
	unsigned int m_uBaseAddress;     // FLASH�Ļ���ַ�߽磺������ż��ַ
	unsigned int m_uChipSize;        // FLASH������ռ��С
	unsigned int m_uReserved0;       // ��������0 
	unsigned int m_uReserved1;       // ��������1
}ADIFLASHInitParams_S;


typedef struct 
{
	unsigned int m_uBaseAddress;     // FLASH�Ļ���ַ�߽磺������ż��ַ
	unsigned int m_uChipSize;        // FLASH������ռ��С 
}ADIFLASHFlashInfo_S;



ADI_Error_Code ADIFLASHInitNor(int nIndex, const ADIFLASHInitParams_S* psInitParams);


ADI_Error_Code ADIFLASHInitSpi(int nIndex, const ADIFLASHInitParams_S* psInitParams);


ADI_Error_Code ADIFLASHInitNand(int nIndex, const ADIFLASHInitParams_S* psInitParams);


ADI_Error_Code ADIFLASHInitEmmc(int index, const ADIFLASHInitParams_S* psInitParams);


ADI_Error_Code ADIFLASHSetNandPartition(int nIndex, const ADIFLASHPartition_S *psPartitionInfo, int nPartitionCnt);


ADI_Error_Code ADIFLASHGetFlashInfo(int nIndex, ADIFLASHFlashInfo_S* psInfo);

								 	    
ADI_Error_Code ADIFLASHBlockLock(unsigned int dwStartAddr, unsigned int dwSpaceSize);


ADI_Error_Code ADIFLASHBlockUnLock(unsigned int dwStartAddr, unsigned int dwSpaceSize);


ADI_Error_Code ADIFLASHBlockLockDown(unsigned int dwStartAddr, unsigned int dwSpaceSize);

ADI_Error_Code ADIFLASHSetBlockToOtp(unsigned int dwStartAddr, unsigned int dwOTPSize);


ADI_Error_Code ADIFlashRead (unsigned int unStartAddress, unsigned char * pucBuf,  unsigned int uDataLength);


ADI_Error_Code ADIFlashWrite(unsigned int unStartAddress, unsigned char * pucBuf, unsigned int uDataLength);

ADI_Error_Code ADIFlashEraseSpace(unsigned int unStartAddress, unsigned int uSpaceSize);

ADI_Error_Code ADIFlashWriteWithoutErase( unsigned int unStartAddress, unsigned char * pucBuf, unsigned int uDataLength);

#ifdef __cplusplus
}
#endif

#endif

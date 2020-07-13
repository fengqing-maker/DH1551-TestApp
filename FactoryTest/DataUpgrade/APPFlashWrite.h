#ifndef APP_FLASH_WRITE_H
#define FLASH_WRITE_H

#define MAX_SERIAL_SIZE 1024

class APPFlashWrite{
public:
	APPFlashWrite();
	~APPFlashWrite();
	void SetADDR(unsigned int unADDR);
	unsigned int HandleTheReceiveData(unsigned char *pucCommandData, unsigned int unCommandDataLen);
	void SetCurrentCount(unsigned int unCurrenCount);
	unsigned int GetCurrentCount(void);
	void SetLastCount(unsigned int unLastCount);
	void SetAPPDataLength(unsigned int unAPPDataLength);
	unsigned int GetLastCount(void);
	unsigned int SetData(unsigned char *pucData, unsigned int unDataLen);
	unsigned int IsDataReceiveOver();
	unsigned int WriteDataToFlash();
private:
	unsigned int m_ADDR;
	unsigned int m_APPDataLength;
	unsigned char *m_pData;
	unsigned int m_DataLen;
	unsigned int m_CurrentCount;
	unsigned int m_LastCount;
};

#endif
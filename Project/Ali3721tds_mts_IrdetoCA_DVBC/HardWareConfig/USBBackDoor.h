#ifndef USB_BACK_DOOR_H_
#define USB_BACK_DOOR_H_

#include "APSafeThread.h"
#include "adi_fs.h"
#include "stdarg.h"
#include "string.h"


class USBBackDoor : public APSafeThread
{
public:
	USBBackDoor(unsigned int unByteFlag, unsigned int unFlashSize, char *pBacDoorFile);
	~USBBackDoor();

public:
	void OnceProcess();
	unsigned int StartUpgradeUSBFile(void);
	void writeLog(char * format, ...);
	void USBMediaReady(unsigned int unUSBStatus, ADIFSDeviceInfo_S* psDeviceInfo);
	void USBMediaPlugOut(unsigned int unUSBStatus);
	unsigned int GetUSBRootPath(char *pBuffer, int nLen);
	ADI_HANDLE OpenFile(char *pFileName, char *pOpenMode);
	unsigned int CheckCRC32(unsigned char *pbData, unsigned int unLength);
	unsigned int CalculateCRC32(unsigned char *pbData, unsigned int unLength);

private:
	ADIFSDeviceInfo_S m_stDeviceInfo;
	char m_acBackDoorFileName[256];
	unsigned int m_unByteFlag;
	unsigned int m_unFlashSize;
	unsigned int m_unUSBStatus;
	ADI_HANDLE  m_hLogFile;
	unsigned int m_unUSBFlush;
};

#endif/*USB_BACK_DOOR_H_*/

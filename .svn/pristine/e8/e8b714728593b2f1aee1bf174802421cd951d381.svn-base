/*
 * USBTest.h
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#ifndef USBTEST_H_
#define USBTEST_H_
#include "USBNotify.h"
#include "AuraTypedef.h"
#include "USBConfig.h"


typedef enum
{
	NONE_USB = 0x0,
	FISRT_USB = 0x1,
	SECOND_USB = 0x2,
	DOUBLE_USB = 0x3
};

class USBTest
{
public:
	USBTest(USBNotify* pNotify);
	virtual ~USBTest();

public:
	void Init(USBConfig csUSBConfig);
	unsigned int Start();
	unsigned int Stop();
	void USBMediaReady(unsigned int unDevice, ADIFSDeviceInfo_S* psDeviceInfo);
	void USBMediaPlugOut(unsigned int unDevice);

	BOOL IsCheckUSBSuccess(unsigned int unDeviceID);

private:

	USBNotify* m_pNotify;

	unsigned int m_unCheckStatus;

	USBConfig m_USBConfig;
};

#endif /* USBTEST_H_ */

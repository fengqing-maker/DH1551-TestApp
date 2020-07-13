/*
 * USBNotify.h
 *
 *  Created on: 2015-8-15
 *      Author: timothy.liao
 */

#ifndef USBNOTIFY_H_
#define USBNOTIFY_H_
#include "adi_fs.h"

class USBNotify
{
public:
	USBNotify();
	virtual ~USBNotify();

public:

	virtual void USBReady(unsigned int unDeviceId, ADIFSDeviceInfo_S* psDeviceInfo) = 0;
	virtual void USBPlugOut(unsigned int unDeviceId) = 0;
	virtual void NoUSBNotify(unsigned int unCheckStatus) = 0;
};

#endif /* USBNOTIFY_H_ */

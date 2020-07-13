#ifndef STORAGE_DEVICE_FORMAT_INTERFACE_H
#define STORAGE_DEVICE_FORMAT_INTERFACE_H

#include "StorageDeviceStatusType.h"

class StorageDeviceFormatInterface
{
public:
	StorageDeviceFormatInterface();
	virtual ~StorageDeviceFormatInterface();

public:

	virtual unsigned int GetMountPath(char acMountPath[], int nMountPathLen) = 0;

	virtual unsigned int GetDeviceName(char acDeviceName[], int nDeviceNameLen) = 0;

	virtual unsigned int updateShorageDevice ( void ) = 0;

	virtual unsigned int GetDeviceID(void) = 0;

	virtual unsigned int GetFSType(void) = 0;

	virtual unsigned int GetTotalSize(void) = 0;

	virtual unsigned int GetFreeSize(void) = 0;

	virtual unsigned int SetUsableStatus(StorageDeviceStatusType eStorageDeviceStatus) = 0;

	virtual StorageDeviceStatusType GetUsableStatus(void) = 0;

};


#endif //STORAGE_DEVICE_FORMAT_INTERFACE_H

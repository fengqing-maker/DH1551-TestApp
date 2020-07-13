#ifndef STORAGE_DEVICE_MANAGEMENT_INTERFACE_H
#define STORAGE_DEVICE_MANAGEMENT_INTERFACE_H

#include "StorageDeviceFormatInterface.h"
#include "FileListScanPublicType.h"
#include "StorageDeviceManagementInterface.h"
#include "StorageDeviceUpdateNotify.h"
#include "FileSystemCharacterType.h"

class  StorageDeviceManagementInterface
{
public:
	StorageDeviceManagementInterface();

	virtual ~StorageDeviceManagementInterface();

public:

	virtual unsigned int RegisterStorageDeviceUpdateNotify(StorageDeviceUpdateNotify * inputStorageDeviceUpdateNotify) = 0;

	virtual unsigned int UnregisterStorageDeviceUpdateNotify(StorageDeviceUpdateNotify * inputStorageDeviceUpdateNotify) = 0 ;

	virtual unsigned int CheckStorageDeviceSTBStarting ( void ) = 0;

	virtual unsigned int GetAllStorageDeviceCount ( ) = 0;

	virtual unsigned int GetStoragePortUniqueIDByIndex ( unsigned int & unStoragePortID, unsigned int & unDeviceID, unsigned int unIndex ) = 0;

	virtual unsigned int GetStoragePortPartition ( unsigned int & unStroragePartition, unsigned int unStoragePortID, unsigned int unDeviceID ) = 0;

	virtual unsigned int GetStoragePortCount ( ) = 0;

	virtual unsigned int GetStoragePortIDByIndex ( unsigned int unIndex ) = 0;

	virtual unsigned int GetStorageDeviceCount ( unsigned int unStoragePortID ) = 0;

	virtual unsigned int FindDeviceIDByDeviceIndex ( unsigned int & unDeviceID, unsigned int unStoragePortID, int nDeviceIndex ) = 0;

	virtual unsigned int FormatStorageDeviceByDeviceID ( unsigned int unStoragePortID, int nDeviceID, unsigned int unFormatType ) = 0;

	virtual unsigned int FormatStorageDeviceRemoveDevice ( unsigned int unStoragePortID, int nDeviceID ) = 0;

	virtual unsigned int GetStorageDeviceMountPath(char acMountPath[], unsigned int unMountPathLen, int nDeviceID) = 0;

	virtual unsigned int GetStorageDeviceDeviceName(char acDeviceName[], unsigned int unDeviceNameLen, int nDeviceID) = 0;

	virtual unsigned int GetStorageDeviceMountPathAscii ( char acMountPath [ ], unsigned int unMountPathLen, int nDeviceID ) = 0;

	virtual unsigned int GetStorageDeviceDeviceNameAscii ( char acDeviceName [ ], unsigned int unDeviceNameLen, int nDeviceID ) = 0;

	virtual unsigned int GetStorageDeviceFSType(int nDeviceID) = 0;

	virtual unsigned int GetStorageDeviceTotalSize(int nDeviceID) = 0;

	virtual unsigned int GetStorageDeviceFreeSize(int nDeviceID) = 0;

	virtual StorageDeviceStatusType	CheckStorageDeviceStatus ( unsigned int unMinNeedSizeMB ) = 0;

	virtual unsigned int SetStorageDeviceUsableStatusByDeviceID(int nDeviceID, StorageDeviceStatusType eStorageDeviceStatusType) = 0;

	virtual unsigned int GetStorageDeviceUsableStatusByDeviceID(int nDeviceID, StorageDeviceStatusType & E_StorageDeviceStatusType) = 0;

	virtual unsigned int GetUsableMuntPort ( unsigned int & unStoragePortID, unsigned int & unStorageDeviceID ) = 0;

	virtual unsigned int SetUsableMuntPort ( unsigned int unStoragePortID, unsigned int unUSBPortPartition ) = 0;

	//找到了默认的StoragePortID 并且 剩余空间大于用户传下下来的Size MB 就返回 1.
	//找到了默认的StoragePortID 并且 剩余空间小于等于用户传下下来的Size MB 就返回 .
	//没有找默认的，去找空间大于用户传下来的Size MB 找到了就返回 1. 如果没有找到大于用户用户传下来的Size MB，就找大于0M，返回2.
	//没有插Storage 就返回0.

	virtual unsigned int FindUsableMountDevice ( unsigned int & unStoragePortID, unsigned int & unDeviceID, unsigned int unMinNeedSizeMB ) = 0;

	virtual unsigned int FindStorageDeviceByDeviceID(int nDeviceID) = 0;

	virtual unsigned int StorageDeviceCallback( void ) = 0;

	virtual unsigned int GetUnicodeFlag ( unsigned int & unIsUnicode ) = 0;

	virtual unsigned int GetFileSystemCharacterType ( FileSystemCharacterType & eFileSystemCharacterType ) = 0;

	virtual unsigned int FileScanLock ( ) = 0;

	virtual unsigned int FileScanUnlock ( ) = 0;

};


#endif

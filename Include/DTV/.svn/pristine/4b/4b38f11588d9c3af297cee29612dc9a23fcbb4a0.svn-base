#ifndef STORAGEDEVICEUPDATENOTIFY_H_
#define STORAGEDEVICEUPDATENOTIFY_H_

class StorageDeviceUpdateNotify 
{
public:
	StorageDeviceUpdateNotify();
	virtual ~StorageDeviceUpdateNotify();

public:
	virtual void StorageDeviceUnkown(int nDeviceId, const void * pvEventData) = 0;
	virtual void StorageDeviceFound(int nDeviceId, const void * pvEventData) = 0;
	virtual void StorageDeviceChecking(int nDeviceId, const void * pvEventData) = 0;
	virtual void StorageDeviceReady(int nDeviceId, const void * pvEventData) = 0;
	virtual void StorageDeviceError(int nDeviceId, const void * pvEventData) = 0;
	virtual void StorageDevicePlugout(int nDeviceId, const void * pvEventData) = 0;
	virtual void StorageDeviceNoPartition(int nDeviceId, const void * pvEventData) = 0;
	virtual void StorageDeviceAvailable ( int nDeviceId , const void * pvEventData ) = 0;
};

#endif /* STORAGEDEVICEUPDATENOTIFY_H_ */

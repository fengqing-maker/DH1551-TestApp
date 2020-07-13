#ifndef FILESCANNOTIFYMANAGEMENTINTERFACE_H_
#define FILESCANNOTIFYMANAGEMENTINTERFACE_H_

#include "FileListScanNotify.h"

class FileScanNotifyManagementInterface
{
public:
	FileScanNotifyManagementInterface();
	virtual ~FileScanNotifyManagementInterface();

public:

	virtual unsigned int RegisterFileListScanNotify(FileListScanNotify * inputFileListScanNotify) = 0;

	virtual unsigned int UnregisterFileListScanNotify(FileListScanNotify * inputFileListScanNotify) = 0;

	virtual unsigned int FileListScanningNotify(int nDeviceID) = 0;

	virtual unsigned int FileListScanFinishedNotify(int nDeviceID) = 0;

	virtual unsigned int CreateDirNotify(int nDeviceID) = 0;

	virtual unsigned int DeleteDirNotify(int nDeviceID) = 0;

	virtual unsigned int CreateFileNotify(int nDeviceID) = 0;

	virtual unsigned int DeleteFileNotify(int nDeviceID) = 0;

	virtual unsigned int SortFileListFinished( void ) = 0;

	virtual unsigned int ConstructFileListFinished( void ) = 0;

	virtual unsigned int FindUpdateFileNotify ( int nDeviceID ) = 0;

	virtual unsigned int DeviceNeedFormatNotify(int nDeviceID) = 0;
};

#endif /* FILESCANNOTIFYMANAGEMENT_H_ */

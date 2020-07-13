#ifndef FILELISTSCANNOTIFY_H_
#define FILELISTSCANNOTIFY_H_

class FileListScanNotify
{
public:
	FileListScanNotify();
	virtual ~FileListScanNotify();

public:
	virtual void FileListScanningNotify(int nDeviceID) = 0;

	virtual void FileListScanFinishedNotify(int nDeviceID) = 0;

	virtual void CreateDirNotify(int nDeviceID)  = 0;
	
	virtual void DeleteDirNotify(int nDeviceID)  = 0;

	virtual void CreateFileNotify(int nDeviceID) = 0;

	virtual void DeleteFileNotify(int nDeviceID) = 0;

	virtual void FindUpdateFileNotify ( int nDeviceID ) = 0;

	virtual void DeviceNeedFormatNotify(int nDeviceID) = 0;

	virtual void SortFileListFinished( void ) = 0;

	virtual void ConstructFileListFinished( void ) = 0;
};

#endif /* FILELISTSCANNOTIFY_H_ */

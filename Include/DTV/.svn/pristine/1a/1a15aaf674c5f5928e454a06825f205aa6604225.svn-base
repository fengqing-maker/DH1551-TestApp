#ifndef MEDIAFILELISTSCANINTERFACE_H_
#define MEDIAFILELISTSCANINTERFACE_H_

#include "FileListFilterContainerInterface.h"
#include "StorageDeviceUpdateNotify.h"
#include "FileListScanNotify.h"
#include "StorageDeviceStatusType.h"

class MediaFileListScanInterface
{
public:
	MediaFileListScanInterface ( );
	virtual ~MediaFileListScanInterface ( );

public:
	virtual unsigned int CreateMediaFileListFilterContainer ( FileFilterSpecInterface *pFileFilterSpecInterface, FileSortCompareSpec *pFileSortCompareSpec, unsigned int unSortType ) = 0;

	virtual unsigned int ContsructMediaFileListFilterContainerFilterSpec ( int nDeviceID, char aucFileNodeName [ ], int nFileNodeNameLen, FileFilterSpecInterface *pFileFilterSpecInterface, unsigned int unErgodicFlag ) = 0;

	virtual unsigned int ClearMediaFileListFilterContainer ( int nDeviceID ) = 0;

	virtual unsigned int ClearMediaFileListFilterContainer ( void ) = 0;

	virtual unsigned int GetMediaFileListFileTypeCount ( int nDeviceID, char aucFileNodeName [ ], int nFileNodeNameLen, FileType eFileType, unsigned int unErgodicFlag, unsigned int & unFileCount ) = 0;

	virtual unsigned int SetMediaFileListFilterContainerSortSpec ( FileSortCompareSpec *pFileSortCompareSpec, unsigned int unSortType ) = 0;

	virtual unsigned int DeleteMediaDir ( char aucFileNodeName [ ], int nFileNodeNameLen, char aucFileName [ ], int nFileNameLen ) = 0;

	virtual unsigned int DeleteMediaFile ( char aucFileNodeName [ ], int nFileNodeNameLen, char aucFileName [ ], int nFileNameLen ) = 0;

	virtual unsigned int GetMediaCurChildCount ( unsigned int & unChildCount ) = 0;

	virtual unsigned int GetMediaCurFileType ( int & nFileType ) = 0;

	virtual unsigned int GetMediaFileType ( int & nFileType, int nIndex ) = 0;

	virtual unsigned int GetMediaCurDeviceId(int & nDeviceId) = 0;

	virtual unsigned int GetMediaCurFileNodeName ( char aucFileNodeName [ ], unsigned int unFileNodeNameLength ) = 0;

	virtual unsigned int GetMediaFileNodeName ( char aucFileNodeName [ ], unsigned int unFileNodeNameLength, int nIndex ) = 0;

	virtual unsigned int GetMediaFileName ( char aucFileName [ ], unsigned int unFileNameLength, int nIndex ) = 0;

	virtual unsigned int GetMediaADIFSFile ( ADIFSFileStat_S * ouputADIFSFile, int nIndex ) = 0;

	virtual unsigned int FindMediaNodeIndexByNodeName ( char aucFileNodeName [ ], unsigned int unFileNodeNameLength, unsigned int & unFileIndex ) = 0;
};

#endif /* MEDIAFILELISTSCANINTERFACE_H_ */

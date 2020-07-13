#ifndef PVRFILELISTSCANINTERFACE11_H_
#define PVRFILELISTSCANINTERFACE11_H_

#include "adi_os.h"
#include "ADITime.h"
#include "PlayLockType.h"
#include "FileListFilterContainerInterface.h"
#include "StorageDeviceUpdateNotify.h"
#include "FileListScanNotify.h"
#include "StorageDeviceFormatInterface.h"
#include "StorageDeviceStatusType.h"
#include "RecordMethod.h"
#include "FileSystemCharacterType.h"

class PVRFileListScanInterface
{
public:
	PVRFileListScanInterface();
	virtual ~PVRFileListScanInterface();

public:
	virtual unsigned int CreatePVRFileListFilterContainer(FileSortCompareSpec *pFileSortCompareSpec, unsigned int unSortType) = 0;

	virtual unsigned int SendChanageGlobalPVRFileListSortMessage( void ) = 0;

	virtual unsigned int SetAllPVRFileListFilterContainerSortSpec(FileSortCompareSpec *pFileSortCompareSpec, unsigned int unSortType) = 0;

	virtual unsigned int ClearGlobalFileListFilterContainerByDeviceID(int nDeviceID) = 0;

	// 下面5个接口只给PVR模块用，因为这里涉及到Unicode 转 Ascii

	virtual unsigned int GetGlobalPVRChildCountByFileNodeNameAscii ( int nDeviceID, char acFileNodeName [ ], int nFileNodeNameLen ) = 0;

	virtual unsigned int GetGlobalPVRChildNodeNameByIndexAscii ( int nDeviceID, char acFatherFileNodeName [ ], int nFatherFileNodeNameLen, char acChildFileNodeName [ ], int nChildFileNodeNameLen, int nIndex ) = 0;

	virtual unsigned int GlobalPVRCreateMKDirAscii ( int nDeviceID, char acFileNodeName [ ], int nFileNodeNameLen, char acFileName [ ], int nFileNameLen ) = 0;

	virtual unsigned int GlobalPVRRemoveMKDirAscii ( int nDeviceID, char acFileNodeName [ ], int nFileNodeNameLen ) = 0;

	virtual unsigned int GlobalPVRCreateAndUpdateFileAscii ( int nDeviceID, char acFileNodeName [ ], int nFileNodeNameLen, char acFileName [ ], int nFileNameLen, void * pRecordInfo ) = 0;


	virtual unsigned int GetGlobalPVRChildCountByFileNodeName(int nDeviceID, char acFileNodeName[], int nFileNodeNameLen) = 0;

	virtual unsigned int GlobalPVRCreateMKDir(int nDeviceID, char aucFileNodeName[], int nFileNodeNameLen, char aucFileName[], int nFileNameLen) = 0;

	virtual unsigned int GlobalPVRRemoveMKDir(int nDeviceID, char aucFileNodeName[], int nFileNodeNameLen) = 0;

	virtual unsigned int GlobalPVRRemoveAllMKDir(int nDeviceID) = 0;

	virtual unsigned int GlobalPVRCreateAndUpdateFile(int nDeviceID, char aucFileNodeName[], int nFileNodeNameLen, char aucFileName[], int nFileNameLen, void * pRecordInfo) = 0;


	virtual unsigned int ConstructDisplayPVRFileListFilterContainer(int nDeviceID, char aucFileNodeName[], int nFileNodeNameLen, FileFilterSpecInterface *pFileFilterSpecInterface, unsigned int unErgodicFlag) = 0;

	virtual unsigned int ClearDisplayPVRFileListFilterContainer(void) = 0;

	virtual unsigned int GetDisplayPVRChildCount(unsigned int & unChildCount) = 0;

	virtual unsigned int GetDisplayPVRGetFileType(int & nFileType) = 0;

	virtual unsigned int GetDisplayPVRGetFileType(int & nFileType, int nIndex) = 0;

	virtual unsigned int GetDisplayPVRADIFSFile(ADIFSFileStat_S * ouputADIFSFile, int nIndex) = 0;

	virtual unsigned int GetDisplayPVRFileNodeNameAscii ( char aucFileNodeName [ ], unsigned int unFileNodeNameLength, int nIndex ) = 0; //Unicode 转 Ascii

	virtual unsigned int GetDisplayPVRFileNodeName(char aucFileNodeName[], unsigned int unFileNodeNameLength, int nIndex) = 0;

	virtual unsigned int GetDisplayPVRFileNameAscii ( char aucFileName [ ], unsigned int unFileNameLength, int nIndex ) = 0; //Unicode 转 Ascii

	virtual unsigned int GetDisplayPVRFileName(char aucFileName[], unsigned int unFileNameLength, int nIndex) = 0;

	virtual unsigned int GetDisplayPVRRecFileServiceName(char aucRecServceName[], unsigned int unRecServiceNameLen, int nIndex) = 0;

	virtual unsigned int ModifyPVRRecFileServiceName ( char aucRecServceName [ ], unsigned int unRecServiceNameLen, int nIndex ) = 0;

	virtual unsigned int GetDisplayPVRRecTimeInfo(ADITime & startTime, int & nduration, int nIndex) = 0;

	virtual unsigned int GetDisplayPVRPFEventInfo(char aucLanguagecode[3], char aucPEventName[], unsigned int unPEventNameLen, char aucPEventText[], unsigned int unPEventTextLen, int nIndex) = 0;

	virtual unsigned int GetDisplayPVRLockType ( PlayLockType & enLockType, int nIndex ) = 0;

	virtual unsigned int GetDisplayPVRFileServiceInfo ( unsigned short & usOriNetworkID, unsigned short & usTSID, unsigned short & usServiceID, int nIndex ) = 0;

	virtual unsigned int PVRLockFile(unsigned int unIndex, unsigned char ucLockStatus) = 0;
	
	virtual unsigned int GetDisplayPVRFileLockStatus(unsigned int unIndex, unsigned char & ucLockStatus) = 0;

	virtual unsigned int GetPVRFileLastPlayedPosition(unsigned int unIndex, unsigned int & unLastPos) = 0;

	virtual unsigned int GetPVRFileRecordMethod(unsigned int unIndex, RecordMethod & reRecordMethod) = 0;

	virtual unsigned int IsFileLocked(unsigned int unIndex) = 0;
	
	virtual unsigned int GetDisplayPVRFileSize(unsigned long long & ullFileSize, int nIndex) = 0;

};

#endif /* PVRFILELISTSCANINTERFACE_H_ */

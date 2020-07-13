/*
 * DataBaseContainerRecorderInterface.h
 *
 *  Created on: 2015-6-23
 *      Author: cl
 */

#ifndef DATABASECONTAINERRECORDERINTERFACE_H_
#define DATABASECONTAINERRECORDERINTERFACE_H_

#include "ServiceInterface.h"
#include "RecordError.h"
#include "RecorderNotify.h"
#include "PlayLockType.h"
#include "RecordMethod.h"
#include "CheckServiceLockSpec.h"
#include "RecordStatus.h"

class DataBaseContainerRecorderInterface
{
public:
    DataBaseContainerRecorderInterface ( );
    virtual ~DataBaseContainerRecorderInterface ( );

public:
    virtual RecordError Start ( ) = 0;
    virtual RecordError Start ( ServiceInterface * pService ) = 0;
    virtual RecordError Start ( ServiceInterface * pService, ADITime & inputOriginalStartTime ) = 0;
    virtual RecordError Stop ( unsigned int unSync ) = 0;
    virtual unsigned int Pause ( ) = 0;
    virtual unsigned int Resume ( ) = 0;
    //单位:秒
    virtual unsigned int GetRecordDuration ( ) = 0;
    //单位:秒
    virtual void SetDefaultRecordDuration ( int nDuration ) = 0;
    virtual void GetDefaultRecordDuration ( int & nDuration ) = 0;
    virtual void SetUnlimitedRecordDuration ( ) = 0;
    virtual unsigned int IsUnlimitedRecordDuration ( ) = 0;

    virtual unsigned int SetPVRLockInfo ( PlayLockType enLockType, unsigned char ucLockLevel, int nDuration ) = 0;
    virtual unsigned int AddRecordNotify ( RecorderNotify * pRecorderNotify ) = 0;
    virtual unsigned int RemoveRecordNotify ( RecorderNotify * pRecorderNotify ) = 0;
    virtual unsigned int IsRecordWorking ( ) = 0;
    virtual unsigned int IsFileRecording ( unsigned int unIndex ) = 0;
    virtual unsigned int CheckRecording ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int CheckServiceConflict ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual ServiceInterface * GetRecordingService ( ) = 0;
	virtual unsigned int GetRecordingServiceName ( char acServiceName [ ], unsigned int unServiceNameLen ) = 0;
    virtual unsigned int GetRecordingPath ( char acFilePath [ ], unsigned int unFilePathLen ) = 0;
    virtual unsigned int GetRecordingServiceCAPGLockStatus ( ServiceInterface* pServiceInterface, unsigned int &runPGService, unsigned int &runUnlock ) = 0;
    virtual unsigned int GetRecordingServiceStartTime ( ADITime & StartTime ) = 0;
    virtual void SetRecordMethod ( RecordMethod eMethod, unsigned short usEventID ) = 0;
    virtual void SetEventName ( char acEventName [ ], unsigned int unEventNameLen ) = 0;
    virtual void SetCheckServiceLockSpec ( CheckServiceLockSpec* pCheckServiceLockSpec ) = 0;
    virtual unsigned int GetRecordingFileSize ( unsigned long long & ullFileSize ) = 0;
	virtual RecordStatus GetRecordStatus ( ) = 0;
	virtual void NotifyUpdateRecInfo ( unsigned int unType ) = 0;
};

#endif /* DATABASECONTAINERRECORDERINTERFACE_H_ */

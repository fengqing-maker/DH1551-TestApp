/*
 * RecorderNotify.h
 *
 *  Created on: 2015-6-23
 *      Author: cl
 */

#ifndef RECORDERNOTIFY_H_
#define RECORDERNOTIFY_H_

#include "RecordError.h"
#include "adi_record.h"

class RecorderNotify
{
public:
    RecorderNotify ( );
    virtual ~RecorderNotify ( );

    virtual unsigned int NoSpaceNotify ( ADIRecType_E enADIRecType ) = 0;
    virtual unsigned int WriteFailNotify ( ADIRecType_E enADIRecType ) = 0;
    virtual unsigned int RecordFinishNotify ( ) = 0;
    virtual unsigned int ServiceRecordingNotify ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int TimeShiftRecordingNotify ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int StartRecordResultNotify ( RecordError enRecordError ) = 0;
    virtual void FileExpiredNotify ( unsigned int unNofityStopType, unsigned int unNofityUserType ) = 0;
    virtual void ProhibitRecordingNotify ( ADIRecType_E enADIRecType ) = 0;
	virtual void RecordingServiceDeletedNotify ( ) = 0;
};

#endif /* RECORDERNOTIFY_H_ */

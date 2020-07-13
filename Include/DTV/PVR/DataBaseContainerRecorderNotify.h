/*
 * DataBaseContainerRecorderNotify.h
 *
 *  Created on: 2015-6-23
 *      Author: cl
 */

#ifndef DATABASECONTAINERRECORDERNOTIFY_H_
#define DATABASECONTAINERRECORDERNOTIFY_H_

#include "ADITime.h"
#include "RecordMethod.h"

class DataBaseContainerRecorderNotify
{
public:
    DataBaseContainerRecorderNotify ( );
    virtual ~DataBaseContainerRecorderNotify ( );

    virtual void StopLiveRecorderNotify ( ADITime & RecordingStartTime, unsigned int unDuration, RecordMethod eRecordMethod ) = 0;
};

#endif /* DATABASECONTAINERRECORDERNOTIFY_H_ */

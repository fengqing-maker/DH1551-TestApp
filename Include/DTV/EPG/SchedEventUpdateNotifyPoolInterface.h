/*
 * SchedEventUpdateNotifyPoolInterface.h
 *
 *  Created on: 2015-5-5
 *      Author: linc
 */

#ifndef SCHEDEVENTUPDATENOTIFYPOOLINTERFACE_H_
#define SCHEDEVENTUPDATENOTIFYPOOLINTERFACE_H_

#include "ADITime.h"

class SchedEventUpdateNotifyPoolInterface
{
public:
	SchedEventUpdateNotifyPoolInterface();
	virtual ~SchedEventUpdateNotifyPoolInterface();

	virtual unsigned int ScheduleEventUpdateNotify(unsigned short usServiceId, ADITime startTime, unsigned int unDurationInSecond) = 0;
};

#endif /* SCHEDEVENTUPDATENOTIFYPOOLINTERFACE_H_ */

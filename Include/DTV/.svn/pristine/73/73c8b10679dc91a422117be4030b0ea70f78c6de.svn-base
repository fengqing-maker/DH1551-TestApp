/*
 * ServiceEventInterface.h
 *
 *  Created on: 2015-4-27
 *      Author: timothy.liao
 */

#ifndef SERVICEEVENTINTERFACE_H_
#define SERVICEEVENTINTERFACE_H_
#include "EventInfoInterface.h"
#include "ADITime.h"

class ServiceEventInterface
{
public:
	ServiceEventInterface();
	virtual ~ServiceEventInterface();

public:
	virtual unsigned short GetNetworkID() = 0;
	virtual unsigned short GetTSID() = 0;
	virtual unsigned short GetServiceID() = 0;
	virtual unsigned int SetPresentEvent(EventInfoInterface* pEventInfo) = 0;
	virtual EventInfoInterface* GetPresentEvent() = 0;
	virtual unsigned int SetFollowingEvent(EventInfoInterface* pEventInfo) = 0;
	virtual EventInfoInterface* GetFollowingEvent() = 0;
	virtual unsigned int AddScheduleEvent(EventInfoInterface* pEventInfo) = 0;
	virtual void* CreateEventIterator(ADITime startTime, unsigned int unDurationInSecond, TimeZone enTimeZone) = 0;
	virtual unsigned int DeleteEventIterator(void* pEventIterator) = 0;
	virtual unsigned int GetEventCount(void* pEventIterator) = 0;
	virtual EventInfoInterface* GetEvent(void* pEventIterator, unsigned int unIndex) = 0;
	virtual unsigned int GetEventCount() = 0;
	virtual EventInfoInterface* GetEvent(unsigned int unIndex) = 0;
	virtual EventInfoInterface* GetEventByEventID(unsigned short usEventID) = 0;
	virtual unsigned int ClearScheduleEvent(ADITime & inputTime) = 0;
	virtual unsigned int ClearScheduleEvent() = 0;
};

#endif /* SERVICEEVENTINTERFACE_H_ */

/*
 * CompositeNetworkEventInterface.h
 *
 *  Created on: 2015-8-7
 *      Author: linc
 */

#ifndef COMPOSITENETWORKEVENTINTERFACE_H_
#define COMPOSITENETWORKEVENTINTERFACE_H_

#include "ServiceInterface.h"
#include "ServiceEventInterface.h"

class CompositeNetworkEventInterface
{
public:
	CompositeNetworkEventInterface();
	virtual ~CompositeNetworkEventInterface();

public:
	virtual unsigned int SaveServiceEvent(ServiceEventInterface * pServiceEvent) = 0;
	//unClearActual==0:清除除usNetworkID外的其他网络的所有Schedule
	//unClearActual==1:清除usNetworkID下的所有Schedule
	virtual unsigned int ClearScheduleEvent(unsigned short usNetworkID, unsigned int unClearActual) = 0;
	//unClearActual==0:清除usNetworkID下的其他TS的Schedule
	//unClearActual==1:清除usNetworkID下的usTSID的Schedule
	virtual unsigned int ClearScheduleEvent(unsigned short usNetworkID, unsigned short usTSID, unsigned int unClearActual) = 0;
	////unClearActual==0:清除usNetworkID、usTSID下的其他节目的Schedule
	//unClearActual==1:清除usNetworkID、usTSID下的usServiceID的Schedule
	virtual unsigned int ClearScheduleEvent(unsigned short usNetworkID, unsigned short usTSID, unsigned short usServiceID, unsigned int unClearActual) = 0;
	//清除usNetworkID下inputTime之前的ScheduleEvent
	virtual unsigned int ClearScheduleEvent(unsigned short usNetworkID, ADITime & inputTime) = 0;

	virtual EventInfoInterface* GetPresentEvent(ServiceInterface * pService) = 0;
	virtual unsigned int FreePresentEvent(EventInfoInterface * pEvent) = 0;
	virtual EventInfoInterface* GetFollowingEvent(ServiceInterface * pService) = 0;
	virtual unsigned int FreeFollowingEvent(EventInfoInterface * pEvent) = 0;
	virtual void ClearExpiredPFEvent(ADITime & inputTime) = 0;

	virtual void* CreateEventIterator(ServiceInterface * pService, ADITime startTime, unsigned int unDurationInSecond, TimeZone enTimeZone) = 0;
	virtual unsigned int DeleteEventIterator(ServiceInterface * pService, void* hIterator) = 0;
	virtual unsigned int GetEventCount(ServiceInterface * pService, void* hIterator) = 0;
	virtual EventInfoInterface* GetEvent(ServiceInterface * pService, void* hIterator, unsigned int unIndex) = 0;
	virtual EventInfoInterface* GetEventByEventID(ServiceInterface * pService, unsigned short usEventID) = 0;
	virtual EventInfoInterface * GetEventByEventID(unsigned short usNetworkID, unsigned short usTSID, unsigned short usServiceID, unsigned short usEventID) = 0;
	virtual void SetCheckEventType(unsigned int unCheckAll) = 0;
	virtual unsigned int NeedCheckEventAll() = 0;
};

#endif /* COMPOSITENETWORKEVENTINTERFACE_H_ */

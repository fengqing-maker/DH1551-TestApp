/*
* UpdateLiveEventInfoInterface.h
*
*  Created on: 2015-5-4
*      Author: linc
*/

#ifndef UPDATELIVEEVENTINFOINTERFACE_H_
#define UPDATELIVEEVENTINFOINTERFACE_H_

#include "PFEventUpdateNotify.h"
#include "SchedEventUpdateNotifyPoolInterface.h"
#include "EventStrategyMode.h"
#include "EPGSearchInterface.h"

class UpdateLiveEventInfoInterface
{

public:

	UpdateLiveEventInfoInterface();
	virtual ~UpdateLiveEventInfoInterface();

	virtual unsigned int AddPFNofity(PFEventUpdateNotify * pPFEventUpdateNotify) = 0;
	virtual unsigned int RemovePFNofity(PFEventUpdateNotify * pPFEventUpdateNotify) = 0;
	virtual unsigned int AddScheduleNofity(SchedEventUpdateNotifyPoolInterface * pSchedEventUpdateNotify, unsigned short usServiceId, ADITime startTime, unsigned int unDurationInSecond, TimeZone enTimeZone) = 0;
	virtual unsigned int RemoveScheduleNofity(SchedEventUpdateNotifyPoolInterface * pSchedEventUpdateNotify, unsigned short usServiceId) = 0;

	virtual unsigned int SetPFReceiveStrategy(EventStrategyMode enReceiveStrategy, unsigned short usOriNetworkId, unsigned short usTSId, unsigned short usServiceId) = 0;
	virtual unsigned int SetPFSaveStrategy(EventStrategyMode enSaveStrategy, unsigned short usOriNetworkId, unsigned short usTSId, unsigned short usServiceId) = 0;
	virtual unsigned int SetScheduleReceiveStrategy(EventStrategyMode enReceiveStrategy, unsigned short usOriNetworkId, unsigned short usTSId, unsigned short usServiceId) = 0;
	virtual unsigned int SetScheduleSaveStrategy(EventStrategyMode enSaveStrategy, unsigned short usOriNetworkId, unsigned short usTSId, unsigned short usServiceId) = 0;

	virtual unsigned int SetEPGDefaultLanguageCode(char acLanguageCode[], int nLen) = 0;
	virtual unsigned int GetEPGDefaultLanguageCode(char acLanguageCode[], int nLen) = 0;
	//获取前端发送的语言
	virtual unsigned int GetEPGLanguageCodeCount() = 0;
	virtual unsigned int GetEPGLanguageCode(char acLanguageCode[], int nLen, unsigned int unIndex) = 0;

	virtual EPGSearchInterface * GetEPGSearchInterface() = 0;
};

#endif /* UPDATELIVEEVENTINFOINTERFACE_H_ */


/*
 * TimerContainerInterface.h
 *
 *  Created on: 2015-7-6
 *      Author: HXC
 */

#ifndef TIMERCONTAINERINTERFACE_H_
#define TIMERCONTAINERINTERFACE_H_

#include "ADITime.h"
#include "ActionType.h"
#include "EventInfoInterface.h"

class TimerContainerInterface
{

public:

    TimerContainerInterface ( );
    virtual ~TimerContainerInterface ( );

public:

    virtual unsigned int CreateOncePlayTimerByEvenID ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned short usEventID, unsigned int unPreNotifySecond, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;
    virtual unsigned int CreateWeeklyPlayTimerByEvenID ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned short usEventID, unsigned int unPreNotifySecond, unsigned char aucWeekDays [ 7 ], unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;

    virtual unsigned int CreateOnceNVODPlayTimeByService ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftEventIndex, ADITime & inputADITime, unsigned int unPreNotifySecond, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;

	virtual unsigned int CreateOnceRecordTimerBytEventID ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned short usEventID, char acEventName [ ], unsigned int unEventNameLen, unsigned int unPreNotifySecond, unsigned int unAheadOfSchedule, unsigned int unBehindOfSchedule, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;
	virtual unsigned int CreateWeeklyRecordTimerBytEventID ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned short usEventID, char acEventName [ ], unsigned int unEventNameLen, unsigned int unPreNotifySecond, unsigned char aucWeekDays [ 7 ], unsigned int unAheadOfSchedule, unsigned int unBehindOfSchedule, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;

    virtual unsigned int CreateOncePlayTimerByService ( unsigned int unGroupIndex, unsigned int unServiceIndex, ADITime & inputADITime, unsigned int unDuration, unsigned int unPreNotifySecond, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;
    virtual unsigned int CreateWeeklyPlayTimerByService ( unsigned int unGroupIndex, unsigned int unServiceIndex, ADITime & inputADITime, unsigned int & unDuration, unsigned int unPreNotifySecond, unsigned char aucWeekDays [ 7 ], unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;

    virtual unsigned int CreateOnceRecordTimerByService ( unsigned int unGroupIndex, unsigned int unServiceIndex, ADITime & inputADITime, unsigned int unDuration, unsigned int unPreNotifySecond, unsigned int unAheadOfSchedule, unsigned int unBehindOfSchedule, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;
    virtual unsigned int CreateWeeklyRecordTimerByService ( unsigned int unGroupIndex, unsigned int unServiceIndex, ADITime & inputADITime, unsigned int & unDuration, unsigned int unPreNotifySecond, unsigned char aucWeekDays [ 7 ], unsigned int unAheadOfSchedule, unsigned int unBehindOfSchedule, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;

    virtual unsigned int CreateOnceStandbyTimerByService ( unsigned int unGroupIndex, unsigned int unServiceIndex, ADITime & inputADITime, unsigned int unDuration, unsigned int unPreNotifySecond, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;
    virtual unsigned int CreateWeeklyStandbyTimerByService ( unsigned int unGroupIndex, unsigned int unServiceIndex, ADITime & inputADITime, unsigned int unDuration, unsigned int unPreNotifySecond, unsigned char aucWeekDays [ 7 ], unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;
    
    virtual unsigned int CreateOnceWakeupTimerByService ( unsigned int unGroupIndex, unsigned int unServiceIndex, ADITime & inputADITime, unsigned int unDuration, unsigned int unPreNotifySecond, unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;
    virtual unsigned int CreateWeeklyWakeupTimerByService ( unsigned int unGroupIndex, unsigned int unServiceIndex, ADITime & inputADITime, unsigned int unDuration, unsigned int unPreNotifySecond, unsigned char aucWeekDays [ 7 ], unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;

    virtual unsigned int CreateStandByTimer ( ADITime & inputADITime, unsigned int unPreNotifySecond ) = 0;
    virtual unsigned int DeleteStandByTimer ( ) = 0;
    virtual unsigned int ResetStandByTimer ( ADITime & newActionTime ) = 0;

    virtual unsigned int SetTimerHelperNotify ( TimerHelperNotify pTimerHelperNotify ) = 0;

    virtual unsigned int GetTimerCount ( ) = 0;
    virtual unsigned int GetTimerCount ( ActionType eActionType ) = 0;
    virtual unsigned int FindTimer ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned short usEventID, unsigned int & unTimerIndex ) = 0;
    virtual unsigned int FindTimer ( unsigned short usOriginalNetworkID, unsigned short usTSID, unsigned short usServiceID, unsigned short usEventID, unsigned int & unTimerIndex ) = 0;

    virtual unsigned int GetTimer ( unsigned int unTimerIndex, unsigned int & unGroupIndex, unsigned int & unServiceIndex, ADITime & startADITime, unsigned int & unDuration, unsigned int &unPreNotifySecond, unsigned int &unAheadOfSchedule, unsigned int &unBehindOfSchedule, unsigned char aucWeekDays [ 7 ], unsigned int & unAction, unsigned short & usEventID ) = 0;
    virtual unsigned int SetTimer ( unsigned int unTimerIndex, unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned short usEventID, ADITime & startADITime, unsigned int unDuration, unsigned int unPreNotifySecond, unsigned int unAheadOfSchedule, unsigned int unBehindOfSchedule, unsigned char aucWeekDays [ 7 ], unsigned int aunConflictTimer [ ], unsigned int unSize, unsigned int & unConflictCount ) = 0;
    virtual unsigned int SetTimer ( unsigned int unTimerIndex, unsigned int unRemindTimeBeforeAction ) = 0;

    virtual unsigned int GetTimerServiceName ( unsigned int unTimerIndex, char acServiceName [ ], unsigned int unServiceNameLen ) = 0;
    virtual unsigned int GetTimerServiceEventName ( unsigned int unTimerIndex, char acEventName [ ], unsigned int unEventNameLen ) = 0;

    virtual unsigned int CancelTimerActionByIndex ( unsigned int unTimerIndex ) = 0;
    virtual unsigned int AllowAction ( unsigned int unTimerIndex ) = 0;
    virtual unsigned int GetIntervalToNextRecordSchedule ( ) = 0;
    virtual unsigned int GetIntervalToNextSchedule ( ) = 0;

    virtual unsigned int DeleteTimerByIndex ( unsigned int unTimerIndex ) = 0;
    virtual unsigned int DeleteTimersByIndex ( unsigned int aunTimerIndex [ ], unsigned int unSize ) = 0;
    virtual unsigned int DeleteTimerByEventID ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned short usEventID ) = 0;
    virtual unsigned int DeleteAllTimer ( ) = 0;
    virtual unsigned int DeleteAllTimer ( ActionType eActionType ) = 0;
};

#endif /* TIMERCONTAINERINTERFACE_H_ */

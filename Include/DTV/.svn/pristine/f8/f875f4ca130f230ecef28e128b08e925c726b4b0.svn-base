/*
 * ActionType.h
 *
 *  Created on: 2015-7-8
 *      Author: HXC
 */

#ifndef ACTIONTYPE_H_
#define ACTIONTYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

enum ActionType
{
    ePlay = 0x01,
	eNVODPlay = 0x02,
	eRecord = 0x04,
	eStandby = 0x08,
	eWakeup = 0x10,
};

typedef void (*TimerHelperNotify)( unsigned int unNotifyType, unsigned int unActionType, unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned int unTimerIndex );

enum TimerErrType
{
	eTimerSucess,
	eErrTimerExsit,
	eErrTimeConflict,
	eErrTimePassed,
    eErrTimerUnAvailable
};

#ifdef __cplusplus
}
#endif

#endif /* ACTIONTYPE_H_ */

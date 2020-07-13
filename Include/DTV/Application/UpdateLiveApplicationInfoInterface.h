/*
 * UpdateLiveApplicationInfoInterface.h
 *
 *  Created on: 2015-11-10
 *      Author: timothy.liao
 */

#ifndef UPDATELIVEAPPLICATIONINFOINTERFACE_H_
#define UPDATELIVEAPPLICATIONINFOINTERFACE_H_
#include "ApplicationListInterface.h"

class UpdateLiveApplicationInfoInterface
{
public:
	UpdateLiveApplicationInfoInterface();
	virtual ~UpdateLiveApplicationInfoInterface();

public:
	
	virtual unsigned int LockApplicationList() = 0;
	virtual void UnLockApplicationList() = 0;
	virtual ApplicationListInterface* GetApplicationList() = 0;
};

#endif /* UPDATELIVEAPPLICATIONINFOINTERFACE_H_ */

/*
 * ServiceProgramInfoNotify.h
 *
 *  Created on: 2017-6-24
 *      Author: HXC_PC
 */

#ifndef SERVICEPROGRAMINFONOTIFY_H_
#define SERVICEPROGRAMINFONOTIFY_H_

#include "ServiceInterface.h"

class ServiceProgramInfoNotify
{

public:
	
    ServiceProgramInfoNotify( );
	virtual ~ServiceProgramInfoNotify( );

public:

    virtual void NotifyServiceProgramInfo ( ServiceInterface & inputService, unsigned int unCASSystemID ) = 0;

};

#endif /* SERVICEPROGRAMINFONOTIFY_H_ */

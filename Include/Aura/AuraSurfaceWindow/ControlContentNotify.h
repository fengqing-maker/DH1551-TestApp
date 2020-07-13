/*
 * ControlContentNotify.h
 *
 *  Created on: 2016-9-12
 *      Author: HXC
 */

#ifndef CONTROLCONTENTNOTIFY_H_
#define CONTROLCONTENTNOTIFY_H_

#include "ControlInterface.h"
#include "AuraSurfaceInterface.h"

class ControlContentNotify
{

public:

	ControlContentNotify( );
	virtual ~ControlContentNotify( );

public:

    virtual void ContentUpdateNotify ( ControlInterface & inputControl, AuraSurfaceInterface & inputAuraSurface, unsigned int unX, unsigned int unY ) = 0;
    virtual void ContentClearNotify ( ControlInterface & inputControl, AuraSurfaceInterface & inputAuraSurface, unsigned int unX, unsigned int unY ) = 0;

};

#endif /* CONTROLCONTENTNOTIFY_H_ */

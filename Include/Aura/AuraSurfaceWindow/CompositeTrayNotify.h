/*
 * CompositeTrayNotify.h
 *
 *  Created on: 2016-9-12
 *      Author: HXC
 */

#ifndef COMPOSITETRAYNOTIFY_H_
#define COMPOSITETRAYNOTIFY_H_

#include "TrayInterface.h"

class CompositeTrayNotify
{

public:

	CompositeTrayNotify( );
	virtual ~CompositeTrayNotify( );

public:

    virtual void IsPermiteShowDisableTray ( TrayInterface & inputTray, unsigned int & unPermittion ) = 0;
    virtual void UpdateTrayDisplayInfo ( TrayInterface & inputTray, unsigned int & unOriX, unsigned int & unOriY, unsigned int & unNewX, unsigned int & unNewY, unsigned int & unOriWidth, unsigned int & unOriHeight, unsigned int & unNewWidth, unsigned int & unNewHeight, unsigned int & unOriAlpha, unsigned int & unNewAlpha, unsigned int & unIndexCount ) = 0;

};

#endif /* COMPOSITETRAYNOTIFY_H_ */

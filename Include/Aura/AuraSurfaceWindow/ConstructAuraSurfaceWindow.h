/*
 * ConstructAuraSurfaceWindow.h
 *
 *  Created on: 2016-9-19
 *      Author: HXC
 */

#ifndef CONSTRUCTAURASURFACEWINDOW_H_
#define CONSTRUCTAURASURFACEWINDOW_H_

#include "AuraSurfaceWindowInterface.h"
#include "ControlInterface.h"
#include "AuraSurfaceWindowServiceInterface.h"
#include "ControlCommandNotify.h"
#include "DoProcessNotify.h"
#include "ControlInputKeyNotify.h"
#include "TrayInterface.h"

class ConstructAuraSurfaceWindow
{

public:

	ConstructAuraSurfaceWindow( );
	virtual ~ConstructAuraSurfaceWindow( );

public:

    AuraSurfaceWindowInterface * CreateAuraSurfaceWindow ( unsigned int unX, unsigned int unY, unsigned int unWidth, unsigned int unHeight );
    ControlInterface * CreateButtonControl ( unsigned int unControlID, unsigned int unX, unsigned int unY, unsigned int unWidth, unsigned int unHeight, TrayInterface * pTray );
    ControlInterface * CreateTabControl ( unsigned int unControlID, unsigned int unX, unsigned int unY, unsigned int unWidth, unsigned int unHeight, TrayInterface * pTray );
    ControlInterface * CreateStaticControl ( unsigned int unControlID, unsigned int unX, unsigned int unY, unsigned int unWidth, unsigned int unHeight, TrayInterface * pTray );
    TrayInterface * CreateTray ( unsigned int unX, unsigned int unY, unsigned int unWidth, unsigned int unHeight, unsigned int unAlphaValue, unsigned int unBltMode );

    AuraSurfaceWindowServiceInterface * CreateAuraSurfaceWindowService ( ControlCommandNotify & inputControlCommandNotify, DoProcessNotify & inputDoProcessNotify, ControlInputKeyNotify & inputControlInputKeyNotify, unsigned int unKeyValueNextView, unsigned int unKeyValuePreView, unsigned int unKeyValueNextFocus, unsigned int unKeyValuePreFocus );

};

#endif /* CONSTRUCTAURASURFACEWINDOW_H_ */

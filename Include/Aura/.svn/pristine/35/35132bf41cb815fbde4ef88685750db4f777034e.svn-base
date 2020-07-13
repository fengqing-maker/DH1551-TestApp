/*
 * AuraSurfaceWindowServiceInterface.h
 *
 *  Created on: 2016-9-13
 *      Author: HXC
 */

#ifndef AURASURFACEWINDOWSERVICEINTERFACE_H_
#define AURASURFACEWINDOWSERVICEINTERFACE_H_

#include "DoProcessNotify.h"
#include "ControlCommandNotify.h"
#include "ControlInputKeyNotify.h"
#include "ControlContentNotify.h"
#include "CompositeTrayNotify.h"
#include "ControlInterface.h"
#include "TrayInterface.h"
#include "AuraSurfaceWindowInterface.h"

#include <list>
using std::list;

class AuraSurfaceWindowServiceInterface
{

public:

	AuraSurfaceWindowServiceInterface( );
	virtual ~AuraSurfaceWindowServiceInterface( );

public:
 
    virtual void Inital ( AuraSurfaceWindowInterface & inputAuraSurfaceWindow ) = 0;

    virtual void SetContentNotify ( ControlContentNotify & inputControlContentNotify ) = 0;
    virtual void SetCommandNotify ( ControlCommandNotify & inputControlCommandNotify ) = 0;
    virtual void SetInputKeyNotify ( ControlInputKeyNotify & inputControlInputKeyNotify ) = 0;
    virtual void SetCompositeTrayNotify ( CompositeTrayNotify & inputCompositeTrayNotify ) = 0;

    virtual void SetControlContentNotify ( ControlInterface & inputControl, ControlContentNotify & inputControlContentNotify ) = 0;
    virtual void SetControlCommandNotify ( ControlInterface & inputControl, ControlCommandNotify & inputControlCommandNotify ) = 0;
    virtual void SetControlInputKeyNotify ( ControlInterface & inputControl, ControlInputKeyNotify & inputControlInputKeyNotify ) = 0;
    virtual void SetTrayCompositeTrayNotify ( TrayInterface & inputTray, CompositeTrayNotify & inputCompositeTrayNotify ) = 0;

    virtual unsigned int SetView ( ControlInterface & inputControl ) = 0;
    virtual ControlInterface & GetView ( ) = 0;
    virtual ControlInterface & SetNextView ( ) = 0;
    virtual ControlInterface & SetPreView ( ) = 0;

    virtual unsigned int SetFocus ( ControlInterface & inputControl ) = 0;
    virtual ControlInterface * GetFocus ( ) = 0;
    virtual void SetNextFocus ( ) = 0;
    virtual void SetPreFocus ( ) = 0;

    virtual unsigned int ShowControl ( ControlInterface & inputControl ) = 0;
    virtual unsigned int HideControl ( ControlInterface & inputControl ) = 0;
    virtual unsigned int IsShowControl ( ControlInterface & inputControl ) = 0;

    virtual unsigned int UpdateContentControl ( ControlInterface & inputControl ) = 0;
    virtual unsigned int UpdateAllContentControl ( ) = 0;

    virtual unsigned int EnableTray ( TrayInterface & inputTray ) = 0;
    virtual unsigned int DisableTray ( TrayInterface & imputTray ) = 0;
    virtual unsigned int IsEnableTray ( TrayInterface & inputTray ) = 0;

    virtual void ClearBKAuraSurface ( unsigned int colorRGBA, unsigned int unX, unsigned int unY, unsigned int unWidth, unsigned int unHeight ) = 0;
    virtual void UpdateTraySurfaceToWindowSurface ( ) = 0;
    virtual void UpdateTraySurfaceToWindowSurface ( list< TrayInterface * > & inputTrayList ) = 0;
    virtual void ClearUpdateTraySurfaceToWindowSurface ( ) = 0;

    virtual unsigned int InputKey ( unsigned int unKeyValue ) = 0;

};

#endif /* AURASURFACEWINDOWSERVICEINTERFACE_H_ */

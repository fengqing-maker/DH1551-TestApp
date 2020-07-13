/*
 * AuraSurfaceWindowInterface.h
 *
 *  Created on: 2016-9-13
 *      Author: HXC
 */

#ifndef AURASURFACEWINDOWINTERFACE_H_
#define AURASURFACEWINDOWINTERFACE_H_

#include "ControlInterface.h"
#include "TrayInterface.h"

class AuraSurfaceWindowInterface
{

public:

	AuraSurfaceWindowInterface( );
	virtual ~AuraSurfaceWindowInterface( );

public:

    virtual void GetPosition ( unsigned int & unX, unsigned int & unY ) = 0;
    virtual void GetSize ( unsigned int & unWidth, unsigned int & unHeight ) = 0;

    virtual unsigned int AddControl ( ControlInterface * pControl ) = 0;
    virtual unsigned int GetControlCount ( ) = 0;
    virtual ControlInterface * GetControl ( unsigned int unIndex ) = 0;
    virtual unsigned int RemoveControl ( ControlInterface * pControl ) = 0;

    virtual unsigned int AddTray ( TrayInterface * pTray ) = 0;
    virtual unsigned int GetTrayCount ( ) = 0;
    virtual TrayInterface * GetTrays ( unsigned int unIndex ) = 0;
    virtual unsigned int RemoveTray ( TrayInterface * pTray ) = 0;

};

#endif /* AURASURFACEWINDOWINTERFACE_H_ */

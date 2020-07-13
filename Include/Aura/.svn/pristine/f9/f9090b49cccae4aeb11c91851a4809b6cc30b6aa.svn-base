/*
 * TrayInterface.h
 *
 *  Created on: 2016-9-10
 *      Author: HXC_PC
 */

#ifndef TRAYINTERFACE_H_
#define TRAYINTERFACE_H_

#include "../AuraSurfaceInterface.h"

class TrayInterface
{

public:

	TrayInterface( );
	virtual ~TrayInterface( );

public:

    virtual AuraSurfaceInterface & GetAuraSurfaceInterface ( ) = 0;

    virtual void GetPosition ( unsigned int & unX, unsigned int & unY ) = 0;
    virtual void GetSize ( unsigned int & unWidth, unsigned int & unHeight ) = 0;
    virtual unsigned int GetAlpha ( ) = 0;
    virtual unsigned int GetBltMode ( ) = 0;

    virtual void SetPosition ( unsigned int unX, unsigned int unY ) = 0;
    virtual void SetAlpha ( unsigned int unAlphaValue ) = 0;

};

#endif /* TRAYINTERFACE_H_ */

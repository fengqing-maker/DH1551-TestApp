/*
 * AuraSurfaceInterface.h
 *
 *  Created on: 2015-7-19
 *      Author: Demo
 */

#ifndef AURASURFACEINTERFACE_H_
#define AURASURFACEINTERFACE_H_

#include "adi_osg.h"
#include "MSWindows.h"

class AuraSurfaceInterface
{

public:
	
	AuraSurfaceInterface( );
	virtual ~AuraSurfaceInterface( );

public:

	virtual ADI_HANDLE LockSurface ( ) = 0;
    virtual void FreeSurface ( ) = 0;

    virtual void GetPosition ( MSPOINT & outputPOINT ) = 0;
    virtual void GetSIZE ( MSSIZE & outputSIZE ) = 0;
    virtual unsigned int GetFormat ( ) = 0;

    virtual void SetPosition ( MSPOINT inputPOINT ) = 0;

};

#endif /* AURASURFACEINTERFACE_H_ */

/*
 * ControlInterface.h
 *
 *  Created on: 2016-9-10
 *      Author: HXC_PC
 */

#ifndef CONTROLINTERFACE_H_
#define CONTROLINTERFACE_H_

#include "TrayInterface.h"

class ControlInterface
{

public:
	
    ControlInterface( );
	virtual ~ControlInterface( );

public:

    virtual unsigned int GetControlID ( ) = 0;
    virtual TrayInterface * GetTray ( ) = 0;

    virtual void GetPosition ( unsigned int & unX, unsigned int & unY ) = 0;
    virtual void GetSize( unsigned int & unWidth, unsigned int & unHeight ) = 0;

    virtual void SetPosition ( unsigned int unX, unsigned int unY ) = 0;

    virtual unsigned int IsFocus ( ) = 0;
    virtual unsigned int IsView ( ) = 0;
    virtual unsigned int IsInputKey ( unsigned int unKeyValue ) = 0;
    virtual unsigned int IsCommandOK ( unsigned int unKeyValue ) = 0;
    
};

#endif /* CONTROLINTERFACE_H_ */

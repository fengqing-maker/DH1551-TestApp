/*
 * DoProcessNotify.h
 *
 *  Created on: 2016-9-12
 *      Author: HXC
 */

#ifndef DOPROCESSNOTIFY_H_
#define DOPROCESSNOTIFY_H_

#include "ControlInterface.h"

class DoProcessNotify
{

public:

	DoProcessNotify( );
	virtual ~DoProcessNotify( );

public:

    virtual void InitialNotify ( ) = 0;

    virtual void FocusChangedNotify ( ControlInterface & focusedControl ) = 0;
    virtual void FocusNextChangedNotify ( ControlInterface & killControl ) = 0;
    virtual void FocusPreChangedNotify ( ControlInterface & killControl ) = 0;

    virtual void ViewChangedNotify ( ControlInterface & viewedControl ) = 0;
    virtual void ViewNextChangedNotify ( ControlInterface & viewedControl ) = 0;
    virtual void ViewPreChangedNotify ( ControlInterface & viewedControl ) = 0;

    virtual void CommandPreOKNotify ( ControlInterface & commandControl ) = 0;
    virtual void CommandEndOKNotify ( ControlInterface & commandControl ) = 0;

};

#endif /* DOPROCESSNOTIFY_H_ */

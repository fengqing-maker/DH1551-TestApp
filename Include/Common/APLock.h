/*
 * APLock.h
 *
 *  Created on: 2010-10-7
 *      Author: NTT
 */

#ifndef APLOCK_H_
#define APLOCK_H_

#include <stdio.h>
#include "string.h"

class APLock
{

public:

	APLock( );
	virtual ~APLock( );

public:
	unsigned int Lock( int nTimeOut );
	unsigned int Lock( );
	void UnLock( );

private:

	void * m_hMutex;

};

#endif /* APLOCK_H_ */

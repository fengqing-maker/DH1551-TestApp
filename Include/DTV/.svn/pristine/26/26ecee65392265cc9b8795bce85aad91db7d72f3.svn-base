/*
 * ServicesGroupFindInterface.h
 *
 *  Created on: 2015-9-9
 *      Author: HXC
 */

#ifndef SERVICESFINDINTERFACE_H_
#define SERVICESFINDINTERFACE_H_

#include "ServiceInterface.h"
#include "KeyBoardInputSpec.h"
#include "StrFind.h"

class ServicesFindInterface
{

public:

	ServicesFindInterface( );
    virtual ~ServicesFindInterface ( );

public:

    virtual unsigned int SetFilter ( char acStr [ ], unsigned int unStrLen ) = 0;
	//unCaseSensitive=1:区分大小写
	virtual unsigned int SetFilter ( char acStr [ ], unsigned int unStrLen, KeyBoardInputSpec * pKeyBoardInputSpec, StrFind * pStrFind, unsigned int unCaseSensitive ) = 0;
    virtual unsigned int GetServicesCount ( ) = 0;
    virtual ServiceInterface * GetService ( unsigned int unIndex ) = 0;

};

#endif /* SERVICESFINDINTERFACE_H_ */

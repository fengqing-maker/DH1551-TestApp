/*
* CheckServiceLockSpec.h
*
*  Created on: 2016-3-11
*      Author: Timothy.Liao
*/

#ifndef CHECKSERVICELOCKSPEC_H_
#define CHECKSERVICELOCKSPEC_H_
#include "ServiceInterface.h"

class CheckServiceLockSpec
{

public:

    CheckServiceLockSpec ( );
    virtual ~CheckServiceLockSpec ( );

public:

    virtual unsigned int IsLockedService ( ServiceInterface * pServiceInterface ) = 0;

};

#endif /* CHECKSERVICELOCKSPEC_H_ */

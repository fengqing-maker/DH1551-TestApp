/*
 * CheckServiceSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKSERVICESPEC_H_
#define CHECKSERVICESPEC_H_

#include "ServiceInterface.h"

class CheckServiceSpec
{

public:

	CheckServiceSpec( );
	virtual ~CheckServiceSpec( );

public:

    virtual unsigned int IsChecked ( ServiceInterface * pServiceInterface ) = 0;

};

#endif /* CHECKSERVICESPEC_H_ */

/*
 * ServicesGroupFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICESGROUPFILTERSPEC_H_
#define SERVICESGROUPFILTERSPEC_H_

#include "ServicesGroupFilterSpecType.h"
#include "ArchiveInterface.h"
#include "ServiceInterface.h"

class ServicesGroupFilterSpec
{

public:

	ServicesGroupFilterSpec();
	virtual ~ServicesGroupFilterSpec();

public:

    virtual unsigned int IsBelongToThis ( ServiceInterface * pServiceInterface ) = 0;
	virtual ServicesGroupFilterSpecType GetType( ) = 0;
	virtual unsigned int Save( ArchiveInterface & inputArchiveInterface ) = 0;

    virtual ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( ) = 0;

};

#endif /* SERVICESGROUPFILTERSPEC_H_ */

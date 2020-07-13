/*
 * AndServicesGroupFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef ANDSERVICESGROUPFILTERSPEC_H_
#define ANDSERVICESGROUPFILTERSPEC_H_

#include "CompositeServicesGroupFilterSpec.h"

class AndServicesGroupFilterSpec : public CompositeServicesGroupFilterSpec
{

public:

	AndServicesGroupFilterSpec( );
	virtual ~AndServicesGroupFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

};

#endif /* ANDSERVICESGROUPFILTERSPEC_H_ */

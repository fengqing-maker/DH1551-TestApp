/*
 * OrServicesGroupFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef ORSERVICESGROUPFILTERSPEC_H_
#define ORSERVICESGROUPFILTERSPEC_H_

#include "CompositeServicesGroupFilterSpec.h"

class OrServicesGroupFilterSpec : public CompositeServicesGroupFilterSpec
{

public:

	OrServicesGroupFilterSpec( );
	virtual ~OrServicesGroupFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

};

#endif /* ORSERVICESGROUPFILTERSPEC_H_ */

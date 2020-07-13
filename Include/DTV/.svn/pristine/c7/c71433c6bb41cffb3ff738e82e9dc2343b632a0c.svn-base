/*
 * NotServicesGroupFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef NOTSERVICESGROUPFILTERSPEC_H_
#define NOTSERVICESGROUPFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class NotServicesGroupFilterSpec : public ServicesGroupFilterSpec
{

public:

	NotServicesGroupFilterSpec( ServicesGroupFilterSpec * pServicesGroupFilterSpec );
	virtual ~NotServicesGroupFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

	ServicesGroupFilterSpec * m_pServicesGroupFilterSpec;

};

#endif /* NOTSERVICESGROUPFILTERSPEC_H_ */

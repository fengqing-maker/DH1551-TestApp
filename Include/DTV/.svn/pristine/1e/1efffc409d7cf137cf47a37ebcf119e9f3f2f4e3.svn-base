/*
 * ServiceTypeFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICETYPEFILTERSPEC_H_
#define SERVICETYPEFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class ServiceTypeFilterSpec : public ServicesGroupFilterSpec
{

public:
	
	ServiceTypeFilterSpec( unsigned short usServiceType );
	virtual ~ServiceTypeFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

	unsigned short m_usServiceType;

};

#endif /* SERVICETYPEFILTERSPEC_H_ */

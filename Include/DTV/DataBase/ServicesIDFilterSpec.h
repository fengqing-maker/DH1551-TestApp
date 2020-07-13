/*
 * ServicesIDFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICESIDFILTERSPEC_H_
#define SERVICESIDFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class ServicesIDFilterSpec : public ServicesGroupFilterSpec
{

public:
	
	ServicesIDFilterSpec( unsigned short usServiceID );
	virtual ~ServicesIDFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

	unsigned short m_usServiceID;

};

#endif /* SERVICESIDFILTERSPEC_H_ */

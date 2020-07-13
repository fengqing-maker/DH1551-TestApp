/*
 * OriIDFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef ORIIDFILTERSPEC_H_
#define ORIIDFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class OriIDFilterSpec: public ServicesGroupFilterSpec
{

public:

	OriIDFilterSpec( unsigned short usOriNetworkID );
	virtual ~OriIDFilterSpec();

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

	unsigned short m_usOriNetworkID;

};

#endif /* ORIIDFILTERSPEC_H_ */

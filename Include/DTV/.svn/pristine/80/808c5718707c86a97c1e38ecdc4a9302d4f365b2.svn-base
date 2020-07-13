/*
 * NetworkIDFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef NETWORKIDFILTERSPEC_H_
#define NETWORKIDFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class NetworkIDFilterSpec: public ServicesGroupFilterSpec
{

public:

	NetworkIDFilterSpec( unsigned short usNetworkID );
	virtual ~NetworkIDFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

	unsigned short m_usNetworkID;

};

#endif /* NETWORKIDFILTERSPEC_H_ */

/*
 * TSIDFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef TSIDFILTERSPEC_H_
#define TSIDFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class TSIDFilterSpec : public ServicesGroupFilterSpec
{

public:
	
	TSIDFilterSpec( unsigned short usTSID );
	virtual ~TSIDFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

	unsigned short m_usTSID;

};

#endif /* TSIDFILTERSPEC_H_ */

/*
 * SatelliteNameFilterSpec.h
 *
 *  Created on: 2015-9-7
 *      Author: HXC
 */

#ifndef SATELLITENAMEFILTERSPEC_H_
#define SATELLITENAMEFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class SatelliteNameFilterSpec : public ServicesGroupFilterSpec
{

public:

	SatelliteNameFilterSpec( unsigned int unSatelliteID );
	virtual ~SatelliteNameFilterSpec( );

public:

    unsigned int IsBelongToThis ( ServiceInterface * pServiceInterface );
    ServicesGroupFilterSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

    unsigned int m_unSatelliteID;

};

#endif /* SATELLITENAMEFILTERSPEC_H_ */

/*
 * CountryAvailabilityServiceAddSpec.h
 *
 *  Created on: 2016-11-1
 *      Author: Timothy.Liao
 */

#ifndef COUNTRYAVAILABILITYSERVICEADDSPEC_H_
#define COUNTRYAVAILABILITYSERVICEADDSPEC_H_

#include "ServiceMergeSpec.h"

class CountryAvailabilityServiceAddSpec : public ServiceMergeSpec
{

public:

    CountryAvailabilityServiceAddSpec ( char acCountryCode [ 3 ] );
    virtual ~CountryAvailabilityServiceAddSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    char m_acCountryCode [ 3 ];

};

#endif /* COUNTRYAVAILABILITYSERVICEADDSPEC_H_ */

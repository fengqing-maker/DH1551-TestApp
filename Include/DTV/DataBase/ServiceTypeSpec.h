/*
 * ServiceTypeSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICETYPESPEC_H_
#define SERVICETYPESPEC_H_

#include "ServiceMergeSpec.h"

class ServiceTypeSpec : public ServiceMergeSpec
{

public:

    ServiceTypeSpec ( unsigned short usServiceType );
    virtual ~ServiceTypeSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usServiceType;

};

#endif /* SERVICETYPESPEC_H_ */

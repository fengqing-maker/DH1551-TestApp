/*
 * CompositeNotServiceAddSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITENOTSERVICEADDSPEC_H_
#define COMPOSITENOTSERVICEADDSPEC_H_

#include "ServiceMergeSpec.h"

class CompositeNotServiceAddSpec : public ServiceMergeSpec
{

public:

    CompositeNotServiceAddSpec ( ServiceMergeSpec * pServiceMergeSpec );
    virtual ~CompositeNotServiceAddSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    ServiceMergeSpec * m_pServiceMergeSpec;

};

#endif /* COMPOSITENOTSERVICEADDSPEC_H_ */

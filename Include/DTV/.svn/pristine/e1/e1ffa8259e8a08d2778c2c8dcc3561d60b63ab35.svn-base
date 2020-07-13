/*
 * CompositeAndServiceAddSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITEANDSERVICEADDSPEC_H_
#define COMPOSITEANDSERVICEADDSPEC_H_

#include "CompositeServiceAddSpec.h"

class CompositeAndServiceAddSpec : public CompositeServiceAddSpec
{

public:

    CompositeAndServiceAddSpec ( );
    virtual ~CompositeAndServiceAddSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );
};

#endif /* COMPOSITEANDSERVICEADDSPEC_H_ */

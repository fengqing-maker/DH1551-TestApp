/*
 * CompositeOrServiceAddSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITEORSERVICEADDSPEC_H_
#define COMPOSITEORSERVICEADDSPEC_H_

#include "CompositeServiceAddSpec.h"

class CompositeOrServiceAddSpec : public CompositeServiceAddSpec
{

public:

    CompositeOrServiceAddSpec ( );
    virtual ~CompositeOrServiceAddSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

};

#endif /* COMPOSITEORSERVICEADDSPEC_H_ */

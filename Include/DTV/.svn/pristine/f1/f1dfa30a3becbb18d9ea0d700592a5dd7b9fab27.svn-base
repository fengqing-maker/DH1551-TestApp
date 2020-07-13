/*
 * NetworkIDSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef NETWORKIDSPEC_H_
#define NETWORKIDSPEC_H_

#include "ServiceMergeSpec.h"

class NetworkIDSpec : public ServiceMergeSpec
{

public:

    NetworkIDSpec ( unsigned short usNetworkID );
    virtual ~NetworkIDSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usNetworkID;

};

#endif /* NETWORKIDSPEC_H_ */

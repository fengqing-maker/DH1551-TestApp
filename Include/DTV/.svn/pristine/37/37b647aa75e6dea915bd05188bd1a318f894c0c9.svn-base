/*
 * OriNetwordIDSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef ORINETWORDIDSPEC_H_
#define ORINETWORDIDSPEC_H_

#include "ServiceMergeSpec.h"

class OriNetwordIDSpec : public ServiceMergeSpec
{

public:

    OriNetwordIDSpec ( unsigned short usOriNetwork );
    virtual ~OriNetwordIDSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usOriNetwork;

};

#endif /* ORINETWORDIDSPEC_H_ */

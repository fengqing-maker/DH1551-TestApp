/*
 * LCNSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef VIDEOPIDSPEC_H_
#define VIDEOPIDSPEC_H_

#include "ServiceMergeSpec.h"

class LCNSpec : public ServiceMergeSpec
{

public:

    LCNSpec ( unsigned short unLCN );
    virtual ~LCNSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usLCN;

};

#endif /* VIDEOPIDSPEC_H_ */

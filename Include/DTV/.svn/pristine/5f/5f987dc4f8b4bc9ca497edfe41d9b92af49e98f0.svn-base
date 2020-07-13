/*
 * VideoPIDSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef VIDEOPIDSPEC_H_
#define VIDEOPIDSPEC_H_

#include "ServiceMergeSpec.h"

class VideoPIDSpec : public ServiceMergeSpec
{

public:

    VideoPIDSpec ( unsigned short unVideoPID );
    virtual ~VideoPIDSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usVideoPID;

};

#endif /* VIDEOPIDSPEC_H_ */

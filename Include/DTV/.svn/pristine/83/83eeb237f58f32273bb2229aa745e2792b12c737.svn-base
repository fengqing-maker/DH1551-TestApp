/*
 * AudioPIDSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef AUDIOPIDSPEC_H_
#define AUDIOPIDSPEC_H_

#include "ServiceMergeSpec.h"

class AudioPIDSpec : public ServiceMergeSpec
{

public:

    AudioPIDSpec ( unsigned short usPID );
    virtual ~AudioPIDSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned int m_usPID;

};

#endif /* AUDIOPIDSPEC_H_ */

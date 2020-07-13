/*
 * TransponderIDSepc.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef TRANSPONDERIDSEPC_H_
#define TRANSPONDERIDSEPC_H_

#include "ServiceMergeSpec.h"

class TransponderIDSepc : public ServiceMergeSpec
{

public:

    TransponderIDSepc ( unsigned short usTSID );
    virtual ~TransponderIDSepc ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usTSID;

};

#endif /* TRANSPONDERIDSEPC_H_ */

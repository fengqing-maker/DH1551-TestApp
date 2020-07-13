/*
 * ServiceIDSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICEIDSPEC_H_
#define SERVICEIDSPEC_H_

#include "ServiceMergeSpec.h"

class ServiceIDSpec : public ServiceMergeSpec
{

public:

    ServiceIDSpec ( unsigned short usServiceID );
    virtual ~ServiceIDSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usServiceID;

};

#endif /* SERVICEIDSPEC_H_ */

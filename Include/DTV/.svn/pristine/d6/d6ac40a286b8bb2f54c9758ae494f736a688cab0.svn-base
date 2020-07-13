/*
 * ServiceNameSpec.h
 *
 *  Created on: 2015-7-9
 *      Author: HXC
 */

#ifndef SERVICENAMESPEC_H_
#define SERVICENAMESPEC_H_

#include "ServiceMergeSpec.h"

class ServiceNameSpec : public ServiceMergeSpec
{

public:

    ServiceNameSpec ( char acServiceName [ ], unsigned int unNameLen );
    virtual ~ServiceNameSpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned int MatchWithAsterisk ( char acString [ ], unsigned int unStrlen, char acPattern [ ], unsigned int unPatternLen );

private:

    char m_acStr [ 64 ];

};

#endif /* SERVICENAMESPEC_H_ */

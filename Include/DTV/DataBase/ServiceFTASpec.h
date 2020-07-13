/*
 * ServiceFTASpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICEFTASPEC_H_
#define SERVICEFTASPEC_H_

#include "ServiceMergeSpec.h"
#include "FreeCAMode.h"

class ServiceFTASpec : public ServiceMergeSpec
{

public:

    ServiceFTASpec ( FreeCAMode eFreeCAMode );
    virtual ~ServiceFTASpec ( );

public:

    unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface );
    ServiceMergeSpecType GetType ( );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );
    ServiceMergeSpec* ConstructSimilarServiceMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    FreeCAMode m_eFreeCAMode;
};

#endif /* SERVICEFTASPEC_H_ */

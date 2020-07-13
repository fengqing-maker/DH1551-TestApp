/*
 * ServiceLogicNumSortSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICELOGICNUMCOMPARESPEC_H_
#define SERVICELOGICNUMCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class ServiceLogicNumCompareSpec : public ServicesCompareSpec
{

public:

    ServiceLogicNumCompareSpec ( );
    virtual ~ServiceLogicNumCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* SERVICELOGICNUMCOMPARESPEC_H_ */

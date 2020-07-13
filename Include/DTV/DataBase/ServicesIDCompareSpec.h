/*
 * ServicesIDCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICESIDCOMPARESPEC_H_
#define SERVICESIDCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class ServicesIDCompareSpec : public ServicesCompareSpec
{

public:

    ServicesIDCompareSpec ( );
    virtual ~ServicesIDCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* SERVICESIDCOMPARESPEC_H_ */

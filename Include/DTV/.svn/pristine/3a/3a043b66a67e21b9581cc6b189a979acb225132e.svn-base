/*
 * TVToRadioCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef TVTORADIOCOMPARESPEC_H_
#define TVTORADIOCOMPARESPEC_H_

#include "ServicesCompareSpec.h"
#include "ServiceType.h"

class TVToRadioCompareSpec : public ServicesCompareSpec
{

public:

    TVToRadioCompareSpec ( );
    virtual ~TVToRadioCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* TVTORADIOCOMPARESPEC_H_ */

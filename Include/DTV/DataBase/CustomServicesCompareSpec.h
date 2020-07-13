/*
 * CustomServicesCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef CUSTOMSERVICESCOMPARESPEC_H_
#define CUSTOMSERVICESCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class CustomServicesCompareSpec : public ServicesCompareSpec
{

public:

    CustomServicesCompareSpec ( );
    virtual ~CustomServicesCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* CUSTOMSERVICESCOMPARESPEC_H_ */

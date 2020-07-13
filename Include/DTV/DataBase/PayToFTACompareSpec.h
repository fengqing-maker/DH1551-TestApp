/*
 * PayToFTACompareSpec.h
 *
 *  Created on: 2017-5-13
 *      Author: Nick
 */

#ifndef PAYTOFTACOMPARESPEC_H_
#define PAYTOFTACOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class PayToFTACompareSpec : public ServicesCompareSpec
{

public:

    PayToFTACompareSpec ( );
    virtual ~PayToFTACompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* PAYTOFTACOMPARESPEC_H_ */

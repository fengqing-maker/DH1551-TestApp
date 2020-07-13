/*
 * FrequencyCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef FREQUENCYCOMPARESPEC_H_
#define FREQUENCYCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class FrequencyCompareSpec : public ServicesCompareSpec
{

public:

    FrequencyCompareSpec ( );
    virtual ~FrequencyCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* FREQUENCYCOMPARESPEC_H_ */

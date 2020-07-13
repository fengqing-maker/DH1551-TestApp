/*
 * TSIDFilterCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef TSIDFILTERCOMPARESPEC_H_
#define TSIDFILTERCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class TSIDFilterCompareSpec : public ServicesCompareSpec
{

public:

    TSIDFilterCompareSpec ( );
    virtual ~TSIDFilterCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* TSIDFILTERCOMPARESPEC_H_ */

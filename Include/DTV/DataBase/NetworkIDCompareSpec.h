/*
 * NetworkIDCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef NETWORKIDCOMPARESPEC_H_
#define NETWORKIDCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class NetworkIDCompareSpec : public ServicesCompareSpec
{

public:

    NetworkIDCompareSpec ( );
    virtual ~NetworkIDCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* NETWORKIDCOMPARESPEC_H_ */

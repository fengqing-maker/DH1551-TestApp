/*
 * OriNetworkIDCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef ORINETWORKIDCOMPARESPEC_H_
#define ORINETWORKIDCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class OriNetworkIDCompareSpec : public ServicesCompareSpec
{

public:

    OriNetworkIDCompareSpec ( );
    virtual ~OriNetworkIDCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* ORINETWORKIDCOMPARESPEC_H_ */

/*
 * ServicesPHYNetworkIDCompareSpec.h
 *
 *  Created on: 2015-9-7
 *      Author: Demo
 */

#ifndef SERVICESPHYNETWORKIDCOMPARESPEC_H_
#define SERVICESPHYNETWORKIDCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class ServicesPHYNetworkIDCompareSpec : public ServicesCompareSpec
{

public:

	ServicesPHYNetworkIDCompareSpec( );
	virtual ~ServicesPHYNetworkIDCompareSpec( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
	ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
	unsigned int Save ( ArchiveInterface & inputArchiveInterface );
	ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* SERVICESPHYNETWORKIDCOMPARESPEC_H_ */

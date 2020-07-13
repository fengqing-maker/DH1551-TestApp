/*
 * LocalNetworkCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef LOCALNETWORKCOMPARESPEC_H_
#define LOCALNETWORKCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class LocalNetworkCompareSpec : public ServicesCompareSpec
{

public:

    LocalNetworkCompareSpec ( unsigned short usOriNetworkID );
    virtual ~LocalNetworkCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );

private:

    unsigned short m_usOriNetworkID;

};

#endif /* LOCALNETWORKCOMPARESPEC_H_ */

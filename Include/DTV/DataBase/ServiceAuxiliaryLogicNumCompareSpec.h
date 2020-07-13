/*
 * ServiceAuxiliaryLogicNumCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICAUXILIARYELOGICNUMCOMPARESPEC_H_
#define SERVICAUXILIARYELOGICNUMCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class ServiceAuxiliaryLogicNumCompareSpec : public ServicesCompareSpec
{

public:

    ServiceAuxiliaryLogicNumCompareSpec ( );
    virtual ~ServiceAuxiliaryLogicNumCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* SERVICAUXILIARYELOGICNUMCOMPARESPEC_H_ */

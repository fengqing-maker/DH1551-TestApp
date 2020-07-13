/*
 * ServicesCompareSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICESCOMPARESPEC_H_
#define SERVICESCOMPARESPEC_H_

#include "ServicesCompareSpecType.h"
#include "ArchiveInterface.h"
#include "ServiceInterface.h"
#include "ServicesGroupInterface.h"

class ServicesCompareSpec
{

public:

    ServicesCompareSpec ( );
    virtual ~ServicesCompareSpec ( );

public:

    virtual int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface ) = 0;
    virtual ServicesCompareSpecType GetType ( ) = 0;
	virtual unsigned int GetSortName ( char acNameBuf[ ], unsigned int unBufLen ) = 0;
	virtual unsigned int Save ( ArchiveInterface & inputArchiveInterface ) = 0;

    virtual ServicesCompareSpec * CopyConstructServicesCompareSpec ( ) = 0;
    virtual unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec ) = 0;

};

#endif /* SERVICESCOMPARESPEC_H_ */

/*
 * ServiceNameSortSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICENAMECOMPARESPEC_H_
#define SERVICENAMECOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class ServiceNameCompareSpec : public ServicesCompareSpec
{

public:

    ServiceNameCompareSpec ( );
    virtual ~ServiceNameCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );

private:
	void DeletePageCode(char acStr[], unsigned int unStrLen);
};

#endif /* SERVICENAMECOMPARESPEC_H_ */

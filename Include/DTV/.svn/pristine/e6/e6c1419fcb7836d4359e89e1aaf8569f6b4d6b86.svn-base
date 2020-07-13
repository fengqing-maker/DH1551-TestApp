/*
 * LockToUnlockCompareSpec.h
 *
 *  Created on: 2017-5-13
 *      Author: Nick
 */

#ifndef LOCKTOUNLOCKCOMPARESPEC_H_
#define LOCKTOUNLOCKCOMPARESPEC_H_

#include "ServicesCompareSpec.h"

class LockToUnlockCompareSpec : public ServicesCompareSpec
{

public:

    LockToUnlockCompareSpec ( );
    virtual ~LockToUnlockCompareSpec ( );

public:

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
    ServicesCompareSpecType GetType ( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );
};

#endif /* LOCKTOUNLOCKCOMPARESPEC_H_ */

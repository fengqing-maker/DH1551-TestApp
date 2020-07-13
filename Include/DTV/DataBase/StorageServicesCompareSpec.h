/*
 * StorageServicesCompareSpec.h
 *
 *  Created on: 2015-5-13
 *      Author: HXC
 */

#ifndef STORAGESERVICESCOMPARESPEC_H_
#define STORAGESERVICESCOMPARESPEC_H_

#include "ServicesCompareSpec.h"
#include "CompositeServicesCompareSpec.h"
#include "ArchiveInterface.h"

class StorageServicesCompareSpec
{

public:

	StorageServicesCompareSpec();
	virtual ~StorageServicesCompareSpec();

public:

    unsigned int Load ( ServicesCompareSpec *& pServicesCompareSpec, ArchiveInterface & inputArchiveInterface );
    unsigned int Save ( ServicesCompareSpec * pServicesCompareSpec, ArchiveInterface & inputArchiveInterface );

    unsigned int LoadOneSpec ( ServicesCompareSpec *& pServicesCompareSpec, ArchiveInterface & inputArchiveInterface );

private:

    unsigned int LoadChildSpec ( CompositeServicesCompareSpec * pParentCompositeServicesCompareSpec, ArchiveInterface & inputArchiveInterface );
};

#endif /* STORAGESERVICESCOMPARESPEC_H_ */

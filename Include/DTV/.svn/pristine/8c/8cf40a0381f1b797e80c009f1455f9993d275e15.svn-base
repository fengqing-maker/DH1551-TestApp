/*
 * ServiceMergeSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICEMERGESPEC_H_
#define SERVICEMERGESPEC_H_

#include "ServiceMergeSpecType.h"
#include "ArchiveInterface.h"
#include "ServiceInterface.h"

class ServiceMergeSpec
{

public:

	ServiceMergeSpec( );
	virtual ~ServiceMergeSpec( );

public:

    virtual unsigned int IsAcceptableServiceInterface ( ServiceInterface * pServiceInterface ) = 0;
    virtual ServiceMergeSpecType GetType ( ) = 0;
    virtual unsigned int Save ( ArchiveInterface & inputArchiveInterface ) = 0;
	virtual ServiceMergeSpec* ConstructSimilarServiceMergeSpec() = 0;
};

#endif /* SERVICEMERGESPEC_H_ */

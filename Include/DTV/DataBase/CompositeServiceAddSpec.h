/*
 * CompositeServiceAddSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITESERVICEADDSPEC_H_
#define COMPOSITESERVICEADDSPEC_H_

#include "ServiceMergeSpec.h"
#include <vector>
using std::vector;

class CompositeServiceAddSpec : public ServiceMergeSpec
{

public:

	CompositeServiceAddSpec( );
	virtual ~CompositeServiceAddSpec( );

public:

    unsigned int AddServiceMergeSpec ( ServiceMergeSpec * pServiceMergeSpec );
    unsigned int RemoveServiceMergeSpec ( ServiceMergeSpec * pServiceMergeSpec );

    unsigned int Save ( ArchiveInterface & inputArchiveInterface );

protected:

    unsigned int GetServiceMergeSpecCount ( );
    ServiceMergeSpec * GetServiceMergeSpec ( unsigned int unIndex );

private:

    void DeleteServiceMergeSpecList ( vector < ServiceMergeSpec * > & inputServiceMergeSpecList );
private:

    vector < ServiceMergeSpec * > m_ServiceMergeSpecList;

};

#endif /* COMPOSITESERVICEADDSPEC_H_ */

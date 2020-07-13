/*
 * CompositeServicesGroupFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITESERVICESGROUPFILTERSPEC_H_
#define COMPOSITESERVICESGROUPFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"
#include <vector>
using std::vector;

class CompositeServicesGroupFilterSpec : public ServicesGroupFilterSpec
{

public:

	CompositeServicesGroupFilterSpec( );
	virtual ~CompositeServicesGroupFilterSpec( );

public:

	unsigned int AddServicesGroupFilterSpec( ServicesGroupFilterSpec * pServicesGroupFilterSpec );
	unsigned int RemoveServicesGroupFilterSpec( ServicesGroupFilterSpec * pServicesGroupFilterSpec );

	unsigned int Save( ArchiveInterface & inputArchiveInterface );

protected:

	unsigned int GetServicesGroupFilterSpecCount( );
	ServicesGroupFilterSpec * GetServicesGroupFilterSpec( unsigned int unIndex );

    unsigned int CopyServicesGroupFilterSpec ( CompositeServicesGroupFilterSpec * pDstCompositeServicesGroupFilterSpec );

private:

	void DeleteServicesGroupFilterSpecList( vector< ServicesGroupFilterSpec * > & inputServicesGroupFilterSpecList );

private:

	vector< ServicesGroupFilterSpec * > m_ServicesGroupFilterSpecList;

};

#endif /* COMPOSITESERVICESGROUPFILTERSPEC_H_ */

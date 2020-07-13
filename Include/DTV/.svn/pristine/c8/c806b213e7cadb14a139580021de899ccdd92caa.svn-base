/*
 * CompositeServicesCompareSpec.h
 *
 *  Created on: 2015-5-13
 *      Author: Demo
 */

#ifndef COMPOSITESERVICESCOMPARESPEC_H_
#define COMPOSITESERVICESCOMPARESPEC_H_

#include "ServicesCompareSpec.h"
#include <vector>
using std::vector;

class CompositeServicesCompareSpec : public ServicesCompareSpec
{

public:

	CompositeServicesCompareSpec( );
	virtual ~CompositeServicesCompareSpec( );

public:

	unsigned int AddServicesCompareSpec( ServicesCompareSpec * pServicesCompareSpec );
	unsigned int RemoveServicesCompareSpec( ServicesCompareSpec * pServicesCompareSpec );
    unsigned int GetCompareSpecCount ( );
    ServicesCompareSpec* GetServicesCompareSpec ( unsigned int unIndex );

    int CompareServices ( ServicesGroupInterface * pServicesGroup, ServiceInterface * pFirstServiceInterface, ServiceInterface * pSecondServiceInterface );
	ServicesCompareSpecType GetType( );
	unsigned int GetSortName ( char acNameBuf [ ], unsigned int unBufLen );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesCompareSpec * CopyConstructServicesCompareSpec ( );
    unsigned int IsSimilarServicesCompareSpec ( ServicesCompareSpec * pServicesCompareSpec );

private:

	void DeleteServicesCompareSpecList( vector< ServicesCompareSpec * > & inputServicesCompareSpecList );

private:

	vector< ServicesCompareSpec * > m_ServicesCompareSpecList;

};

#endif /* COMPOSITESERVICESCOMPARESPEC_H_ */

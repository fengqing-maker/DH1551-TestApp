/*
 * ServiceNameFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICENAMEWILDCARDFILTERSPEC_H_
#define SERVICENAMEWILDCARDFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class ServiceNameWithSubStrFilterSpec : public ServicesGroupFilterSpec
{

public:
	
	ServiceNameWithSubStrFilterSpec( char acServiceName[ ], unsigned int unNameLen );
	virtual ~ServiceNameWithSubStrFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

	char m_acStr[ 64 ];

};

#endif /* SERVICENAMEFILTERSPEC_H_ */

/*
 * ServiceNameFilterSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef SERVICENAMEFILTERSPEC_H_
#define SERVICENAMEFILTERSPEC_H_

#include "ServicesGroupFilterSpec.h"

class ServiceNameFilterSpec : public ServicesGroupFilterSpec
{

public:
	
	ServiceNameFilterSpec( char acServiceName[ ], unsigned int unNameLen );
	virtual ~ServiceNameFilterSpec( );

public:

	unsigned int IsBelongToThis( ServiceInterface * pServiceInterface );
	ServicesGroupFilterSpecType GetType( );
	unsigned int Save( ArchiveInterface & inputArchiveInterface );

    ServicesGroupFilterSpec * CopyConstructServicesGroupFilterSpec ( );

private:

	char m_acStr[ 64 ];

};

#endif /* SERVICENAMEFILTERSPEC_H_ */

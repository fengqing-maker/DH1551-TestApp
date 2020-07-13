/*
 * CheckServiceNameSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKSERVICENAMESPEC_H_
#define CHECKSERVICENAMESPEC_H_

#include "CheckServiceSpec.h"

class CheckServiceNameSpec : public CheckServiceSpec
{

public:

	CheckServiceNameSpec( char acServiceName[ ], unsigned int unServiceNameLen );
	virtual ~CheckServiceNameSpec( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:

	unsigned int MatchWithAsterisk(char* str1, char* pattern);

private:

    char m_acServiceName [ 64 ];

};

#endif /* CHECKSERVICENAMESPEC_H_ */

/*
 * CheckServiceIDSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKSERVICEIDSPEC_H_
#define CHECKSERVICEIDSPEC_H_

#include "CheckServiceSpec.h"

class CheckServiceIDSpec : public CheckServiceSpec
{

public:

	CheckServiceIDSpec( unsigned short usServiceID );
	virtual ~CheckServiceIDSpec( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:

    unsigned short m_usServiceID;

};

#endif /* CHECKSERVICEIDSPEC_H_ */

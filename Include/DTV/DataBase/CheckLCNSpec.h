/*
 * CheckLCNSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKLCNSPEC_H_
#define CHECKLCNSPEC_H_

#include "CheckServiceSpec.h"

class CheckLCNSpec : public CheckServiceSpec
{

public:

	CheckLCNSpec( unsigned short unLCN );
	virtual ~CheckLCNSpec( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:

    unsigned short m_usLCN;

};

#endif /* CHECKLCNSPEC_H_ */

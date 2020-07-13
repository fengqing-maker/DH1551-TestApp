/*
 * CheckServiceTypeSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKSERVICETYPESPEC_H_
#define CHECKSERVICETYPESPEC_H_

#include "CheckServiceSpec.h"

class CheckServiceTypeSpec : public CheckServiceSpec
{

public:

    CheckServiceTypeSpec ( ServiceType enServiceType );
	virtual ~CheckServiceTypeSpec( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:

    ServiceType m_enServiceType;

};

#endif /* CHECKSERVICETYPESPEC_H_ */

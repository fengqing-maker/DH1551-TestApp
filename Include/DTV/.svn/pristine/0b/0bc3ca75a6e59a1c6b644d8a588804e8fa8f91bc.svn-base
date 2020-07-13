/*
 * NotCheckServiceSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef NOTCHECKSERVICESPEC_H_
#define NOTCHECKSERVICESPEC_H_

#include "CheckServiceSpec.h"

class NotCheckServiceSpec : public CheckServiceSpec
{

public:

    NotCheckServiceSpec ( CheckServiceSpec * pCheckServiceSpec );
	virtual ~NotCheckServiceSpec( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:
    
    CheckServiceSpec * m_pCheckServiceSpec;

};

#endif /* NOTCHECKSERVICESPEC_H_ */

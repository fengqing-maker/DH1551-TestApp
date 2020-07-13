/*
 * OrCompositeCheckServiceSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef ORCOMPOSITECHECKSERVICESPEC_H_
#define ORCOMPOSITECHECKSERVICESPEC_H_

#include "CompositeCheckServiceSpec.h"

class OrCompositeCheckServiceSpec : public CompositeCheckServiceSpec
{

public:

	OrCompositeCheckServiceSpec( );
	virtual ~OrCompositeCheckServiceSpec( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

};

#endif /* ORCOMPOSITECHECKSERVICESPEC_H_ */

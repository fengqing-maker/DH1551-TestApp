/*
 * CompositeCheckServiceSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef COMPOSITECHECKSERVICESPEC_H_
#define COMPOSITECHECKSERVICESPEC_H_

#include "CheckServiceSpec.h"
#include <list>
using std::list;

class CompositeCheckServiceSpec : public CheckServiceSpec
{

public:
	
    CompositeCheckServiceSpec( );
	virtual ~CompositeCheckServiceSpec( );

public:

    unsigned int AddCheckServiceSpec ( CheckServiceSpec * pCheckServiceSpec );
    unsigned int RemoveCheckServiceSpec ( CheckServiceSpec * pCheckServiceSpec );

protected:

    list< CheckServiceSpec * > & GetCheckServiceSpecList ( );

private:

    void DeleteServicesGroupFilterSpecList ( list< CheckServiceSpec * > & inputCheckServiceSpecList );

private:

    list< CheckServiceSpec * > m_CheckServiceSpecList;

};

#endif /* COMPOSITECHECKSERVICESPEC_H_ */

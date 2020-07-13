/*
 * CompositeCheckNetworkSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef COMPOSITECHECKNETWORKSPEC_H_
#define COMPOSITECHECKNETWORKSPEC_H_

#include "CheckNetworkSpec.h"
#include <list>
using std::list;

class CompositeCheckNetworkSpec : public CheckNetworkSpec
{

public:
	
    CompositeCheckNetworkSpec ( );
    virtual ~CompositeCheckNetworkSpec ( );

public:

    unsigned int AddCheckNetworkSpec ( CheckNetworkSpec * pCheckNetworkSpec );
    unsigned int RemoveCheckNetworkSpec ( CheckNetworkSpec * pCheckNetworkSpec );

protected:

    list< CheckNetworkSpec * > & GetCheckNetworkSpecList ( );

private:

    void DeleteCheckNetworkSpecList ( list< CheckNetworkSpec * > & inputCheckNetworkSpecList );

private:

    list< CheckNetworkSpec * > m_CheckNetworkSpecList;

};

#endif /* COMPOSITECHECKNETWORKSPEC_H_ */

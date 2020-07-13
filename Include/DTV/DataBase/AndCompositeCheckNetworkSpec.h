/*
 * AndCompositeCheckNetworkSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef ANDCOMPOSITECHECKNETWORKSPEC_H_
#define ANDCOMPOSITECHECKNETWORKSPEC_H_

#include "CompositeCheckNetworkSpec.h"
#include <list>
using std::list;

class AndCompositeCheckNetworkSpec : public CompositeCheckNetworkSpec
{

public:

    AndCompositeCheckNetworkSpec ( );
    virtual ~AndCompositeCheckNetworkSpec ( );

public:

    unsigned int IsChecked ( NetworkInterface * pNetworkInterface );
    CheckNetworkSpec * ConstructSimilarCheckNetworkSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

};

#endif /* ANDCOMPOSITECHECKNETWORKSPEC_H_ */

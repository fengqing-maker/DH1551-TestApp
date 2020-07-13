/*
 * OrCompositeCheckNetworkSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef ORCOMPOSITECHECKNETWORKSPEC_H_
#define ORCOMPOSITECHECKNETWORKSPEC_H_

#include "CompositeCheckNetworkSpec.h"

class OrCompositeCheckNetworkSpec : public CompositeCheckNetworkSpec
{

public:

    OrCompositeCheckNetworkSpec ( );
    virtual ~OrCompositeCheckNetworkSpec ( );

public:

    unsigned int IsChecked ( NetworkInterface * pNetworkInterface );
    CheckNetworkSpec * ConstructSimilarCheckNetworkSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );
};

#endif /* ORCOMPOSITECHECKNETWORKSPEC_H_ */

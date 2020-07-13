/*
 * CheckNetworkSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKNETWORKSPEC_H_
#define CHECKNETWORKSPEC_H_

#include "NetworkInterface.h"

class CheckNetworkSpec
{

public:

    CheckNetworkSpec ( );
    virtual ~CheckNetworkSpec ( );

public:

    virtual unsigned int IsChecked ( NetworkInterface * pNetworkInterface ) = 0;
    virtual CheckNetworkSpec * ConstructSimilarCheckNetworkSpec ( ) = 0;
};

#endif /* CHECKNETWORKSPEC_H_ */

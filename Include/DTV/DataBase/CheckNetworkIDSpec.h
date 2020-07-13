/*
 * CheckNetworkIDSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKNETWORKIDSPEC_H_
#define CHECKNETWORKIDSPEC_H_

#include "CheckNetworkSpec.h"

class CheckNetworkIDSpec : public CheckNetworkSpec
{

public:

    CheckNetworkIDSpec ( unsigned short usNetworkID );
    virtual ~CheckNetworkIDSpec ( );

public:

    unsigned int IsChecked ( NetworkInterface * pNetworkInterface );
    CheckNetworkSpec * ConstructSimilarCheckNetworkSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usNetworkID;

};

#endif /* CHECKNETWORKIDSPEC_H_ */

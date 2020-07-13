/*
 * NotCheckNetworkSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef NOTCHECKNETWORKSPEC_H_
#define NOTCHECKNETWORKSPEC_H_

#include "CheckNetworkSpec.h"

class NotCheckNetworkSpec : public CheckNetworkSpec
{

public:

    NotCheckNetworkSpec ( CheckNetworkSpec * pCheckNetworkSpec );
    virtual ~NotCheckNetworkSpec ( );

public:

    unsigned int IsChecked ( NetworkInterface * pNetworkInterface );
    CheckNetworkSpec * ConstructSimilarCheckNetworkSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    CheckNetworkSpec * m_pCheckNetworkSpec;

};

#endif /* NOTCHECKNETWORKSPEC_H_ */

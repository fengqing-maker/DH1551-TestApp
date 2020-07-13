/*
 * CheckNetworkNameSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKNETWORKNAMESPEC_H_
#define CHECKNETWORKNAMESPEC_H_

#include "CheckNetworkSpec.h"

class CheckNetworkNameSpec : public CheckNetworkSpec
{

public:

    CheckNetworkNameSpec ( char acNetworkName [ ], unsigned int unNetworkNameLen );
    virtual ~CheckNetworkNameSpec ( );

public:

    unsigned int IsChecked ( NetworkInterface * pNetworkInterface );
    CheckNetworkSpec * ConstructSimilarCheckNetworkSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned int MatchWithAsterisk ( char* str1, char* pattern );

private:

    char m_acNetworkName [ 256 ];

};

#endif /* CHECKNETWORKNAMESPEC_H_ */

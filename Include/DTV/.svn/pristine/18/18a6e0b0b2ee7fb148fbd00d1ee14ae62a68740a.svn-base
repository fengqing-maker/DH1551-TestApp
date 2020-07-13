/*
 * CustomDescriptorParserInterface.h
 *
 *  Created on: 2016-11-15
 *      Author: Timothy.Liao
 */

#ifndef CUSTOMDESCRIPTORPARSERINTERFACE_H_
#define CUSTOMDESCRIPTORPARSERINTERFACE_H_
#include "NetworkInterface.h"
#include "TransponderInterface.h"
#include "ServiceInterface.h"

class CustomDescriptorParserInterface
{

public:

    CustomDescriptorParserInterface ( );
    virtual ~CustomDescriptorParserInterface ( );

public:

    virtual void ParseCustomDescriptor ( unsigned char aucDescriptor [ ], unsigned int unLength, NetworkInterface * pNetworkInterface ) = 0;
    virtual void ParseCustomDescriptor ( unsigned char aucDescriptor [ ], unsigned int unLength, TransponderInterface * pTransponderInterface ) = 0;
    virtual void ParseCustomDescriptor ( unsigned char aucDescriptor [ ], unsigned int unLength, ServiceInterface * pServiceInterface ) = 0;

};

#endif /* SIGNALINDICATORINTERFACE_H_ */

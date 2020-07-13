/*
 * ServiceExpDataSerializationNotify.h
 *
 *  Created on: 2017-5-5
 *      Author: HXC
 */

#ifndef SERVICEEXPDATASERIALIZATIONNOTIFY_H_
#define SERVICEEXPDATASERIALIZATIONNOTIFY_H_

#include "ServiceInterface.h"

class ServiceExpDataSerializationNotify
{

public:

    ServiceExpDataSerializationNotify ( );
    virtual ~ServiceExpDataSerializationNotify ( );

public:

    virtual unsigned int GetExpServiceDataLen ( ) = 0;
    virtual void DataToService ( ServiceInterface & outputService, unsigned char aucOutputServiceData [ ], unsigned int unOutputServiceDataLen ) = 0;
    virtual void ServiceToData ( ServiceInterface & inputService, unsigned char aucOutputServiceData [ ], unsigned int unOutputServiceDataLen ) = 0;

};

#endif /* SERVICEEXPDATASERIALIZATIONNOTIFY_H_ */

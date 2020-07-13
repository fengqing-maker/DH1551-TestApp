/*
 * UserDefineServiceIDAsLCNSpec.h
 *
 *  Created on: 2017-4-6
 *      Author: Timothy.Liao
 */

#ifndef USERDEFINESERVICEIDASLCNSPEC_H_
#define USERDEFINESERVICEIDASLCNSPEC_H_
#include "UserDefineLCNSpec.h"

class UserDefineServiceIDAsLCNSpec : public UserDefineLCNSpec
{

public:

    UserDefineServiceIDAsLCNSpec (  );
    virtual ~UserDefineServiceIDAsLCNSpec ( );

public:

    unsigned int SetUserLCN ( ServicesDataBaseInterface * pServicesDataBaseInterface );
};

#endif /* USERDEFINESERVICEIDASLCNSPEC_H_ */

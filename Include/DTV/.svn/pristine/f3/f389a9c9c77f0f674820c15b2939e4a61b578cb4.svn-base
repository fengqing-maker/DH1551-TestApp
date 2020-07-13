/*
 * UserDefineTVRadioServicesLCNSpec.h
 *
 *  Created on: 2017-4-6
 *      Author: Timothy.Liao
 */

#ifndef USERDEFINETVRADIOSERVICESLCNSPEC_H_
#define USERDEFINETVRADIOSERVICESLCNSPEC_H_
#include "UserDefineLCNSpec.h"
#include "ServicesCompareSpec.h"

class UserDefineTVRadioServicesLCNSpec : public UserDefineLCNSpec
{

public:

    UserDefineTVRadioServicesLCNSpec ( unsigned short usTVLCNInitialValue, unsigned short usRadioLCNInitialValue, ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending );
    virtual ~UserDefineTVRadioServicesLCNSpec ( );

public:

    unsigned int SetUserLCN ( ServicesDataBaseInterface * pServicesDataBaseInterface );

private:

    unsigned short m_usTVLCNInitialValue;
    unsigned short m_usRadioLCNInitialValue;
	
    ServicesCompareSpec * m_pServicesCompareSpec;
    unsigned int m_unAscending;
};

#endif /* USERDEFINERADIOSERVICESLCNSPEC_H_ */

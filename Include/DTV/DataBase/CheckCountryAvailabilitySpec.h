/*
 * CheckCountryAvailabilitySpec.h
 *
 *  Created on: 2016-11-1
 *      Author: Timothy.Liao
 */

#ifndef CHECKCOUNTRYAVAILABILITYSPEC_H_
#define CHECKCOUNTRYAVAILABILITYSPEC_H_

#include "CheckServiceSpec.h"

class CheckCountryAvailabilitySpec : public CheckServiceSpec
{

public:

    CheckCountryAvailabilitySpec ( char acCountryCode [ 3 ] );
    virtual ~CheckCountryAvailabilitySpec ( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:

    char m_acCountryCode [ 3 ];

};

#endif /* CHECKCOUNTRYAVAILABILITYSPEC_H_ */

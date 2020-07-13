/*
* CheckSimilarTransponderDeliverySpec.h
*
*  Created on: 2016-10-27
*      Author: Timothy
*/

#ifndef CHECKSIMILARTRANSPONDERDELIVERYSPEC_H_
#define CHECKSIMILARTRANSPONDERDELIVERYSPEC_H_

#include "CheckSimilarTransponderSpec.h"

class CheckSimilarTransponderDeliverySpec : public CheckSimilarTransponderSpec
{

public:

    CheckSimilarTransponderDeliverySpec ( );
    virtual ~CheckSimilarTransponderDeliverySpec ( );

public:

    unsigned int IsSimilarTransponder ( TransponderInterface * pTransponderInterface1, TransponderInterface * pTransponderInterface2 );
    CheckSimilarTransponderSpec * ConstructSimilarSpec ( );
};

#endif /* CHECKSIMILARTRANSPONDERDELIVERYSPEC_H_ */

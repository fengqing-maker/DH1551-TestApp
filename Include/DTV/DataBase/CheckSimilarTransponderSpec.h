/*
 * CheckSimilarTransponderSpec.h
 *
 *  Created on: 2016-10-20
 *      Author: Timothy
 */

#ifndef CHECKSIMILARTRANSPONDERSPEC_H_
#define CHECKSIMILARTRANSPONDERSPEC_H_

#include "TransponderInterface.h"

class CheckSimilarTransponderSpec
{

public:

    CheckSimilarTransponderSpec ( );
    virtual ~CheckSimilarTransponderSpec ( );

public:

    virtual unsigned int IsSimilarTransponder ( TransponderInterface * pTransponderInterface1, TransponderInterface * pTransponderInterface2 ) = 0;
    virtual CheckSimilarTransponderSpec * ConstructSimilarSpec ( ) = 0;
};

#endif /* CHECKSIMILARTRANSPONDERSPEC_H_ */

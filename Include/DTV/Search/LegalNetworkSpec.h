/*
 * LegalNetworkSpec.h
 *
 *  Created on: 2015-12-28
 *      Author: Timothy.Liao
 */

#ifndef LEGALNETWORKSPEC_H_
#define LEGALNETWORKSPEC_H_

#include "NetworkInterface.h"
#include "TransponderInterface.h"
#include "ServiceInterface.h"

class LegalNetworkSpec
{

public:

	LegalNetworkSpec ( );
	virtual ~LegalNetworkSpec ( );

public:

    virtual unsigned int IsLegal ( ServiceInterface * pServiceInterface ) = 0;
	virtual unsigned int IsLegal ( NetworkInterface * pNetworkInterface ) = 0;
	virtual unsigned int IsLegal ( TransponderInterface * pTransponderInterfae ) = 0;
	virtual LegalNetworkSpec* ConstructSimilarLegalNetworkSpec ( ) = 0;
};

#endif /* LEGALNETWORKSPEC_H_ */

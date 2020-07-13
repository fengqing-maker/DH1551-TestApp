/*
 * CompositeAndLegalNetworkSpec.h
 *
 *  Created on: 2015-12-28
 *      Author: Timothy.Liao
 */

#ifndef COMPOSITEANDLEGALNETWORKSPEC_H_
#define COMPOSITEANDLEGALNETWORKSPEC_H_

#include "CompositeLegalNetworkSpec.h"

class CompositeAndLegalNetworkSpec : public CompositeLegalNetworkSpec
{

public:

	CompositeAndLegalNetworkSpec ( );
	virtual ~CompositeAndLegalNetworkSpec ( );

public:

    unsigned int IsLegal ( ServiceInterface * pServiceInterface );
	unsigned int IsLegal ( NetworkInterface * pNetworkInterface );
	unsigned int IsLegal ( TransponderInterface * pTransponderInterfae );
	LegalNetworkSpec* ConstructSimilarLegalNetworkSpec ( );
};

#endif /* COMPOSITEANDLEGALNETWORKSPEC_H_ */

/*
 * LegalNetworkNetworkNameSpec.h
 *
 *  Created on: 2015-12-28
 *      Author: Timtohy.Liao
 */

#ifndef LEGALNETWORKNETWORKNAMESPEC_H
#define LEGALNETWORKNETWORKNAMESPEC_H

#include "LegalNetworkSpec.h"

class LegalNetworkNetworkNameSpec : public LegalNetworkSpec
{

public:

	LegalNetworkNetworkNameSpec ( char acNetworkName[], unsigned int unNetworkNameLength );
	virtual ~LegalNetworkNetworkNameSpec ( );

public:

    unsigned int IsLegal ( ServiceInterface * pServiceInterface );
	unsigned int IsLegal ( NetworkInterface * pNetworkInterface );
	unsigned int IsLegal ( TransponderInterface * pTransponderInterfae );
	LegalNetworkSpec* ConstructSimilarLegalNetworkSpec ( );

private:

	char m_acNetworkName[64];
};

#endif /* LEGALNETWORKNETWORKNAMESPEC_H */

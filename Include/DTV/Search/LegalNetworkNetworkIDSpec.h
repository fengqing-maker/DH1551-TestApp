/*
 * LegalNetworkNetworkIDSpec.h
 *
 *  Created on: 2015-12-28
 *      Author: Timtohy.Liao
 */

#ifndef LEGALNETWORKNETWORKIDSPEC_H
#define LEGALNETWORKNETWORKIDSPEC_H

#include "LegalNetworkSpec.h"

class LegalNetworkNetworkIDSpec : public LegalNetworkSpec
{

public:

	LegalNetworkNetworkIDSpec ( unsigned short usNetworkID ) ;
	virtual ~LegalNetworkNetworkIDSpec ( );

public:

    unsigned int IsLegal ( ServiceInterface * pServiceInterface );
	unsigned int IsLegal ( NetworkInterface * pNetworkInterface );
	unsigned int IsLegal ( TransponderInterface * pTransponderInterfae );
	LegalNetworkSpec* ConstructSimilarLegalNetworkSpec ( );

private:

	unsigned short m_usNetworkID;
};

#endif /* CHANNELNUMBERSERVICEIDSPEC_H */

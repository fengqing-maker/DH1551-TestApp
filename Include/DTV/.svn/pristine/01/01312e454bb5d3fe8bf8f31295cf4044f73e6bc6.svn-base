/*
 * LegalNetworkCASIDSpec.h
 *
 *  Created on: 2015-12-28
 *      Author: Timtohy.Liao
 */

#ifndef LEGALNETWORKCASID_H
#define LEGALNETWORKCASID_H

#include "LegalNetworkSpec.h"

class LegalNetworkCASIDSpec : public LegalNetworkSpec
{

public:

	LegalNetworkCASIDSpec ( unsigned short usCASID );
	virtual ~LegalNetworkCASIDSpec ( );

public:

    unsigned int IsLegal ( ServiceInterface * pServiceInterface );
	unsigned int IsLegal ( NetworkInterface * pNetworkInterface );
	unsigned int IsLegal ( TransponderInterface * pTransponderInterfae );
	LegalNetworkSpec* ConstructSimilarLegalNetworkSpec ( );

private:

	unsigned short m_usCASID;

};

#endif /* LEGALNETWORKCASID_H */

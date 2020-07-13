/*
 * CompositeLegalNetworkSpec.h
 *
 *  Created on: 2015-12-28
 *      Author: Timothy.Liao
 */

#ifndef COMPOSITELEGALNETWORKSPEC_H_
#define COMPOSITELEGALNETWORKSPEC_H_

#include "LegalNetworkSpec.h"
#include <list>
using std::list;

class CompositeLegalNetworkSpec : public LegalNetworkSpec
{

public:

	CompositeLegalNetworkSpec ( );
	virtual ~CompositeLegalNetworkSpec ( );

public:

    unsigned int AddLegalNetworkSpec ( LegalNetworkSpec * pLegalNetworkSpec );
    unsigned int RemoveLegalNetworkSpec ( LegalNetworkSpec * pLegalNetworkSpec );

protected:

	list< LegalNetworkSpec * > & GetLegalNetworkSpecList( );
	unsigned int CopyLegalNetworkSpecList(CompositeLegalNetworkSpec & inputCompositeLegalNetworkList);

private:

	list< LegalNetworkSpec * > m_LegalNetworkSpecList;
};

#endif /* COMPOSITELEGALNETWORKSPEC_H_ */

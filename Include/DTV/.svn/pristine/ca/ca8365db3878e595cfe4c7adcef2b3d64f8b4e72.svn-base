/*
 * CompositeAndBouquetAddSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITEANDBOUQUETADDSPEC_H_
#define COMPOSITEANDBOUQUETADDSPEC_H_

#include "CompositeBouquetAddSpec.h"

class CompositeAndBouquetAddSpec : public CompositeBouquetAddSpec
{

public:
	
    CompositeAndBouquetAddSpec ( );
    virtual ~CompositeAndBouquetAddSpec ( );

public:

    unsigned int IsAcceptableBouquetInterface ( BouquetInterface * pBouquetInterface );
    BouquetMergeSpec* ConstructSimilarBouquetMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

};

#endif /* COMPOSITEANDBOUQUETADDSPEC_H_ */

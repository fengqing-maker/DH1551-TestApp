/*
 * CompositeNotBouquetAddSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITENOTBOUQUETADDSPEC_H_
#define COMPOSITENOTBOUQUETADDSPEC_H_

#include "BouquetMergeSpec.h"

class CompositeNotBouquetAddSpec : public BouquetMergeSpec
{

public:

    CompositeNotBouquetAddSpec ( BouquetMergeSpec * pBouquetMergeSpec );
    virtual ~CompositeNotBouquetAddSpec ( );

public:

    unsigned int IsAcceptableBouquetInterface ( BouquetInterface * pBouquetInterface );
    BouquetMergeSpec* ConstructSimilarBouquetMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    BouquetMergeSpec * m_pBouquetMergeSpec;

};

#endif /* COMPOSITENOTBOUQUETADDSPEC_H_ */

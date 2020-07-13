/*
 * CompositeBouquetAddSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITEBOUQUETADDSPEC_H_
#define COMPOSITEBOUQUETADDSPEC_H_

#include "BouquetMergeSpec.h"
#include <vector>
using std::vector;

class CompositeBouquetAddSpec : public BouquetMergeSpec
{

public:

    CompositeBouquetAddSpec ( );
    virtual ~CompositeBouquetAddSpec ( );

public:

    unsigned int AddBouquetMergeSpec ( BouquetMergeSpec * pBouquetMergeSpec );
    unsigned int RemoveBouquetMergeSpec ( BouquetMergeSpec * pBouquetMergeSpec );

protected:

    unsigned int GetBouquetMergeSpecCount ( );
    BouquetMergeSpec * GetBouquetMergeSpec ( unsigned int unIndex );

private:

    void DeleteBouquetMergeSpecList ( vector < BouquetMergeSpec * > & inputBouquetMergeSpecList );

private:

    vector < BouquetMergeSpec * > m_BouquetMergeSpecList;

};

#endif /* COMPOSITEBOUQUETADDSPEC_H_ */

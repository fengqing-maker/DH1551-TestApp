#ifndef BOUQUETCOMPARESPEC_H_
#define BOUQUETCOMPARESPEC_H_

#include "BouquetInterface.h"
#include "ArchiveInterface.h"
#include "BouquetCompareSpecType.h"

class BouquetCompareSpec
{

public:

	BouquetCompareSpec( );
	virtual ~BouquetCompareSpec();

public:

	virtual int CompareServices( BouquetInterface * pFirstBouquetInterface, BouquetInterface * pSecondBouquetInterface ) = 0;

	virtual BouquetCompareSpecType GetType( void ) = 0;

	virtual unsigned int GetSortName( char acNameBuf[ ], unsigned int unBufLen ) = 0;

	virtual unsigned int Save( ArchiveInterface & inputArchiveInterface ) = 0;

	virtual BouquetCompareSpec * CopyConstructBouquetCompareSpec( void ) = 0;

};

#endif /* BOUQUETCOMPARESPEC_H_ */

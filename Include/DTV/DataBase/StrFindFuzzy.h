/*
 * StrFindFuzzy.h
 *
 *  Created on: 2016-8-15
 *      Author: linc
 */

#ifndef STRFINDFUZZY_H_
#define STRFINDFUZZY_H_


#include "StrFind.h"


class StrFindFuzzy : public StrFind
{

public:

	StrFindFuzzy();
	virtual ~StrFindFuzzy();

public:

    int IsIncludeTheFindStr ( char acSrcStr [ ], unsigned int unSrcStrBufLen, char acFindStr [ ], unsigned int unFindStrBufLen );

};

#endif /* STRFINDFUZZY_H_ */

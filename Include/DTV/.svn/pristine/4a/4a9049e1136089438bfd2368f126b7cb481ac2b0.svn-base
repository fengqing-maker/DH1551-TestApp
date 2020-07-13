/*
 * FilterParameter.h
 *
 *  Created on: 2015-3-8
 *      Author: Demo
 */

#ifndef FILTERPARAMETER_H_
#define FILTERPARAMETER_H_

#include "string.h"


class FilterParameter
{

public:

	friend class Filter;

public:
	
	FilterParameter( unsigned int unFilterLen );
	virtual ~FilterParameter( );

public:

    unsigned int GetMatch ( unsigned char aucMatch [ ], unsigned int unMatchCount );
    unsigned int GetMask ( unsigned char aucMask [ ], unsigned int unMaskCount );
    unsigned int GetNegate ( unsigned char aucNegate [ ], unsigned int unNegateCount );

	unsigned int SetMatch( unsigned char aucMatch[ ], unsigned int unMatchCount );
	unsigned int SetMask( unsigned char aucMask[ ], unsigned int unMaskCount );
	unsigned int SetNegate( unsigned char aucNegate[ ], unsigned int unNegateCount );

	unsigned int SetMatch( unsigned int unPos, unsigned int unBits, unsigned char aucMatch[ ] );
	unsigned int SetMask( unsigned int unPos, unsigned int unBits, unsigned char aucMask[ ] );
	unsigned int SetNegate( unsigned int unPos, unsigned int unBits, unsigned char aucNegate[ ] );

	FilterParameter & operator = ( FilterParameter & inputFilterParameter );

private:

	unsigned int m_unFilterLen;

	unsigned char * m_pucMatch;
	unsigned char * m_pucMask;
	unsigned char * m_pucNegate;

};

#endif /* FILTERPARAMETER_H_ */

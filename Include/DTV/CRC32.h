/*
 * CRC32.h
 *
 *  Created on: 2015-5-23
 *      Author: HXC
 */

#ifndef CRC32_H_
#define CRC32_H_

class CRC32
{

public:

	CRC32( );
	virtual ~CRC32( );

public:

    unsigned int CalcCRC32 ( unsigned char * pucBuf, unsigned int unLen );

    unsigned int GetFirstCRC32 ( );
    unsigned int CalcSEGSCRC32 ( unsigned int unCRC32, unsigned char * pucBuf, unsigned int unLen );

};

#endif /* CRC32_H_ */

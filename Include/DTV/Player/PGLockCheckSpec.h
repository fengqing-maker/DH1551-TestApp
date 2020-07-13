/*
 * PGLockCheckSpec.h
 *
 *  Created on: 2017-01-17
 *      Author: linc
 */

#ifndef PGLOCKCHECKSPEC_H_
#define PGLOCKCHECKSPEC_H_


class PGLockCheckSpec
{

public:

    PGLockCheckSpec ( );
    virtual ~PGLockCheckSpec ( );

public:

    virtual unsigned int IsPGLocked ( unsigned char ucSTBRating, unsigned char ucCurEventRating ) = 0;
};

#endif /* PGLOCKCHECKSPEC_H_ */

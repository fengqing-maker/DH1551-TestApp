/**
 * $Id: s3_ansi_functions.h,v 1.9 2011/04/21 06:08:05 jcao Exp $
 *
 * Copyright 2003-2005 Irdeto Access B.V.
 *
 * This file and the information contained herein are the subject of copyright
 * and intellectual property rights under international convention. All rights
 * reserved. No part of this file may be reproduced, stored in a retrieval
 * system or transmitted in any form by any means, electronic, mechanical or
 * optical, in whole or in part, without the prior written permission of Irdeto
 * Access B.V.
 *
 * This file is part of the SoftCell 3 Integration library.
 * 
 * This file provides an abstraction layer between SoftCell and the ANSI-C standard library.
 * 
 * Functions may need to meet additional requirements above those described in the ANSI C standard.
 * 
 * Most functions can be mapped directly to the ANSI defined library function.
 **/

#ifndef ANSI_FUNCTIONS_H
#define ANSI_FUNCTIONS_H

/* Requirement: same as ANSI-C library memcpy. */
void* ansi_memcpy( void *pvDest, const void *pvSrc, unsigned int uiCount );

/* Requirement: same as ANSI-C library memmove. */
void* ansi_memmove( void *pvDest, const void *pvSrc, unsigned int uiCount );

/* Requirement: same as ANSI-C library memcmp. */
int ansi_memcmp( const void *pvData1, const void *pvData2, unsigned int uiLength );

/* Requirement: same as ANSI-C library memset. */
void* ansi_memset( void *pvData, int iData, unsigned int uiLength );

/* Requirement: same as ANSI-C library strlen. */
unsigned int ansi_strlen( const char *pcString );

/* Requirement: same as ANSI-C library sprintf, but using a subset for conversion specifications. 
 * Support is required for conversion specifications %s, %d, and %X.
 * Support is required for flag character 0, and field width for %X.
 */
unsigned int ansi_sprintf( char *pcbuffer, const char *pcFormat, ... );

/* Requirement: same as ANSI-C library time, with the exception that it MUST be implemented, 
 * and thus is not allowed to return -1. 
 * SoftCell will always call ansi_time with 0 for pliTimer. 
 */
long int ansi_time( long int *pliTimer );

#endif /* ANSI_FUNCTIONS_H */



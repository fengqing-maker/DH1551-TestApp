/**
 * $Id: s3_ansi_functions.c,v 1.8 2011/04/21 06:08:01 jcao Exp $
 *
 * Copyright 2003-2005 Irdeto Access B.V., All rights reserved.
 *
 * This file is proivided as part of the SoftCell 3 Integration library.
 * 
 * This file, together with s3_ansi_functions.h, provides an abstraction layer between SoftCell 
 * and the ANSI-C standard library.
 * 
 * This file is provided as an example and may need to be altered to match the target platform.
 * Functions may need to meet additional requirements above those described in the ANSI C standard.
 * 
 * Most functions map directly to the ANSI defined library function.
 **/

//#include <stdio.h>
//#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <api/libc/printf.h>
#include <time.h>
#include "s3_ansi_functions.h"

void* ansi_memcpy( void *pvDest, const void *pvSrc, unsigned int uiCount )
{
	return memcpy( pvDest, pvSrc, uiCount );
}

void* ansi_memmove( void *pvDest, const void *pvSrc, unsigned int uiCount )
{
	return memmove( pvDest, pvSrc, uiCount );
}

int ansi_memcmp( const void *pvData1, const void *pvData2, unsigned int uiLength )
{
	return memcmp( pvData1, pvData2, uiLength );
}

void* ansi_memset( void *pvData, int iData, unsigned int uiLength )
{
	return memset( pvData, iData, uiLength );
}

unsigned int ansi_strlen( const char *pcString )
{
	return strlen( pcString );
}

unsigned int ansi_sprintf( char *pcbuffer, const char *pcFormat, ... )
{
	unsigned int retVal;
	va_list args;
	
	va_start( args, pcFormat );
	retVal = vsprintf( pcbuffer, pcFormat, args );
	va_end( args );
	return retVal;
}

long int ansi_time( long int *pliTimer )
{
	return time( pliTimer );
}


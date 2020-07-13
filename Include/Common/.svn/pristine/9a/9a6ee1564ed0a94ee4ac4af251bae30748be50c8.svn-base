/*
 * APMemory.h
 *
 *  Created on: 2010-10-7
 *      Author: NTT
 */
#ifndef APMEYORY_H_
#define APMEYORY_H_

#include "string.h"

//shall config if enable mempory pool in prior to DTV initialization
unsigned int ConfigAPMemoryPool ( unsigned int unMemoryPool );

void * APMalloc ( unsigned int unSize );
void APFree ( void * pvPtr );
void APMallocPrintMemoryStatus ( );

void * APEPGMalloc ( unsigned int unSize );
void APEPGFree ( void * pvPtr );
void APEPGMallocPrintMemoryStatus ( );

void * APNew ( unsigned int unSize );
void APDelete ( void * pvPtr );
void APNewPrintMemoryStatus ( );

#endif /* APMEYORY_H_ */

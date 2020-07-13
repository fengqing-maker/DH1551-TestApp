
#ifndef __APASSERT_H
#define __APASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define APAssert( expression )  \
	do { \
		if ( !( expression ) ) \
		printf( " APAssert: \"%s\", in file %s, at line %d \n", #expression, __FILE__, __LINE__ ); \
	}while( 0 );

#define APTrace  printf

#ifdef __cplusplus
}
#endif

#endif

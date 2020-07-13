
#include <stdarg.h>
#include "adi_typedef.h"
#include "adi_error.h"

#ifndef _ADI_DEBUG_H_
#define _ADI_DEBUG_H_

#ifdef  __cplusplus
extern "C" {
#endif

enum
{
	ADIDEBUG_ERROR_BAD_PARAMETER = ADI_DEBUG_ERROR_BASE,
	ADIDEBUG_ERROR_FEATURE_NOT_SUPPORTED,
	ADIDEBUG_ERROR_UNKNOWN_ERROR,
	ADIDEBUG_ERROR_NO_MEMORY,
	
	ADIDEBUG_ERROR_MAX
};

/*调试级*/
#define DEBUG_LEVEL		    (0)

/*流程等提示级*/
#define INFO_LEVEL 		    (1)

/*不确定是否可恢复故障级*/
#define ERROR_LEVEL		    (0x3FFFFFFF)

/*禁止级信息输出*/
#define DISABLE_LEVEL		(0x7FFFFFFF)

/*ADIDebugSet时，使用该宏表示设置所有模块的日志级别*/
#define MODULE_NAME_ALL     ("*all")

#define FATAL_LEVEL  DISABLE_LEVEL

#ifdef _ADI_DEBUG_
	#define ADIASSERT(expression)  \
	do{ \
		if(!(expression)) \
		ADIDebug("ADIDebug",FATAL_LEVEL,"Assertion: \"%s\" failed, in file %s, line %d\n", \
				#expression, __FILE__, __LINE__); \
	}while(0)
	
	#define ADIASSERT_FAILED(exp) (!(exp)? (ADIDebug("ADIDebug", FATAL_LEVEL, "Assertion \"%s\" failed, in file %s line %d\n", #exp, __FILE__,__LINE__), 1) : 0) 

	#define ADIDEBUG    	ADIDebug
	#define ADIVDEBUG	ADIVDebug
#else
	#define ADIASSERT(x)
	#define ADIASSERT_FAILED(exp) (!(exp))
	
	#define ADIDEBUG		1?(void)0:ADIDebug
	#define ADIVDEBUG	1?(void)0:ADIVDebug

#endif


typedef  void ( *ADIDebugOutPutString )( const char* pStr );

ADI_Error_Code ADIDebugSetDefaultLevel(int nDefaultLevel);

ADI_Error_Code ADIDebugSetLevel(const char* pcModuleName,int nOutputLevel);

int ADIDebugGetModuleInfo(const char** ppModules,int nMaxCount);

ADI_Error_Code ADIDebugRegisterOutputCallback(ADIDebugOutPutString OutputCallback);

void ADIDebug(const char * pcModuleName, int nOutputLevel, const char *pcFormat, ...);

int ADIDbgPrintf(const char *pcFormat,...); // printf

/**V版本的ADIDebug，与ADIDebug的关系相当于vprintf与printf的关系*/
void ADIVDebug(const char * pcModuleName, int nOutputLevel, const char *pcFormat,va_list arg);

void ADIDebugHex (const char * pcModuleName, int nOutputLevel, char *pcTxt, unsigned char *pucData, int unLen );

#ifdef	__cplusplus
}
#endif

#endif


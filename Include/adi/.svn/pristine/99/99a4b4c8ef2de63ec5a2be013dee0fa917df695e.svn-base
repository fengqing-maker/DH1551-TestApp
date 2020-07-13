
#ifndef _ADI_TYPEDEF_H_
#define _ADI_TYPEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

//#include "string.h"

typedef int                 ADI_BOOL;

typedef void *			    ADI_HANDLE;         // 句柄类型,其长度等于指针长度。@note Eastwin会将ADI_NULL当做一个非法的句柄，请在实现时特别注意所有Handle的取值范围

#define ADI_FALSE         (0 == 1)
#define ADI_TRUE          (!(ADI_FALSE))

#ifdef PLATFORM_SUPPORT_LL

typedef long long           ADI_INT64;            ///< 64位有符号数,当定义PLATFORM_SUPPORT_LL时有效
typedef unsigned long long  ADI_UINT64;          ///< 64位无符号数,当定义PLATFORM_SUPPORT_LL时有效

#else
/*64位有符号数结构体*/
typedef	struct
{
	unsigned int	 low; // 低32位
	int	             high;// 高32位
}ADI_INT64;

/*64位无符号数结构体*/
typedef	struct
{
	unsigned int	low;// 低32位
	unsigned int	high;// 高32位
}ADI_UINT64;



#endif

#define ADIUNUSED(x) ((void)(x))

#ifdef __cplusplus
}
#endif


#endif  


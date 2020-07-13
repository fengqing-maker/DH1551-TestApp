
#ifndef _MSWINDOWS_H
#define _MSWINDOWS_H

#ifdef  __cplusplus
extern "C" {
#endif

#define UNALIGNED

#ifndef _MSC_VER
#define _MSC_VER 0x0     //versions of vc the compiler don't use
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用 Windows 95 和 Windows NT 4 或更高版本的特定功能。
#define WINVER 0x600		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_WINNT		// 允许使用 Windows NT 4 或更高版本的特定功能。
#define _WIN32_WINNT 0x0501	//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用 Windows 98 或更高版本的特定功能。
#define _WIN32_WINDOWS 0x0400 //为 Windows Me 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_IE			// 允许使用 IE 4.0 或更高版本的特定功能。
#define _WIN32_IE 0x0500	//为 IE 5.0 及更新版本改变为适当的值。
#endif


#ifndef _WIN32_WCE
#define _WIN32_WCE   0x0400
#endif

#ifndef ISOLATION_AWARE_ENABLED
#define ISOLATION_AWARE_ENABLED 0
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../adi/adi_typedef.h"
#include "../adi/adi_debug.h"
#include "../adi/adi_error.h"
#include "AuraTypedef.h"

#include "MSWinDef.h"
#include "MSGDIDDK.h"
#include "MSWINGDI.h"
#include "MSWINUser.h"
#include "MSCommCtrl.h"
#include "MSWINError.h"
#include "MSFont.h"
#include "AuraColorConversion.h"

#ifdef  __cplusplus
}
#endif

#endif

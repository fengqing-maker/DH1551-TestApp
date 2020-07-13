#include "version.h"
#include "SvnVersion.h"

const char * GetAppVersion ( void )
{
	const char* pVer = "svn "SRC_VERSION" "__DATE__" "__TIME__;
	return pVer;
}

const char * GetAppSVNVersion ( void )
{
	const char* pVer = SRC_SVN_VERSION;
	
	return pVer;
}


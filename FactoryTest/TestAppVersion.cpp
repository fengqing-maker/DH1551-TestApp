#include "TestAppVersion.h"
#include "string.h"

#define TESTVERSION "TestApp V2.6.0.4"

int GetTestAppVersion(char *pBuffer, int nLen)
{
	int nRet = 0;

	if(pBuffer != NULL && nLen > strlen(TESTVERSION))
	{
		memcpy(pBuffer, TESTVERSION, strlen(TESTVERSION));

		nRet = 1;
	}

	return nRet;
}


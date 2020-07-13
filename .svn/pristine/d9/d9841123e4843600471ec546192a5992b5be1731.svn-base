#include "ReadSTBAndCardID.h"
#include "STBDataInterface.h"
#include "string.h"

int ReadCardID(char *pBuffer, int nLen)
{
	return 1;
}

int ReadSTBID(char *pBuffer, int nLen)
{	
	int nRet = -1;
	
	if(pBuffer != NULL && nLen > 0)
	{
		nRet = ReadSN( pBuffer, nLen);
	}
	
	return nRet;
}

int IsCaDataBurned(void)
{
	return 0;
}

int GetCardStatus(void)
{
	return 1;
}


/*
*  MS_DrawControl.c
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#include "MSWindows.h"
#include "AuraDesktop.h"
#include "AuraWindows.h"
#include "MS_DrawType.h"
#include "MS_DrawControl.h"
#include "../Resources.h"

#define RCID_MAX (100000)

BOOL MSSetDlgItemTextByIDS(HMSWND hWnd, DWORD dwCtrlID ,DWORD dwStrID)
{
	BOOL bRet = FALSE;
    TCHAR strBuf[256] = {0};

	if (hWnd == NULL || dwCtrlID == NULL || dwStrID <= 0)
	{
		ADIASSERT(hWnd != NULL && dwCtrlID != 0 && dwStrID != 0);
		return FALSE;
	}
 
    MSLoadString(GetInstance(),dwStrID, strBuf, (sizeof(strBuf)>>1)-1);
    
    bRet = MSSetDlgItemText(hWnd, dwCtrlID, strBuf);
    if(!bRet)
    {
        return FALSE;
    }

    return TRUE;
}


BOOL MSSetWindowTextByIDS(HMSWND hWnd ,DWORD dwStrID)
{
    BOOL bRet = FALSE;
    TCHAR strBuf[128] = {0};

	if (hWnd == NULL || dwStrID <= 0)
	{
		ADIASSERT(hWnd != NULL && dwStrID != 0);
		return FALSE;
	}
    
	MSLoadString(GetInstance(), dwStrID, strBuf, (sizeof(strBuf) >> 1) - 1);
   
    bRet = MSSetWindowText(hWnd, strBuf);
    if(!bRet)
    {
        return FALSE;
    }

    return TRUE;
}


BOOL MSSetDlgItemTextByChar(HMSWND hWnd, DWORD dwCtrlID, const char* pStr, int nCount)
{
	BOOL bRet = FALSE;
    TCHAR strBuf[1024] = {0};

	if (hWnd == NULL || dwCtrlID == 0 || pStr == NULL || nCount <= 0)
	{
		ADIASSERT(hWnd != NULL && dwCtrlID != 0 && pStr == NULL && nCount > 0);
		return FALSE;
	}

	MSMultiByteToWideChar(0, 0, (LPCSTR)pStr, nCount, (LPWSTR)strBuf, sizeof(strBuf) >> 1);

    bRet = MSSetDlgItemText(hWnd, dwCtrlID, strBuf);
    if(!bRet)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL MSSetWindowTextByChar(HMSWND hWnd, const char* pStr, int nCount)
{
	BOOL bRet = FALSE;
    TCHAR strBuf[256] = {0};

	if (hWnd == NULL || pStr == NULL || nCount <= 0)
	{
		ADIASSERT(hWnd != NULL && pStr == NULL && nCount > 0);
		return FALSE;
	}
    
	MSMultiByteToWideChar(0, 0, (LPCSTR)pStr, nCount, (LPWSTR)strBuf, sizeof(strBuf)>>1);
    
    bRet = MSSetWindowText(hWnd, strBuf);
    if(!bRet)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL MSDrawDlgItemTextEx(HMSWND hWnd,int nIDDlgItem,DWORD dwStrID)
{
	char acTxt[256] = {0};
	char acTmp[128] = {0};

	if (hWnd == NULL || nIDDlgItem == 0 || dwStrID == 0)
    {
        return FALSE;
    }
    
    if ( dwStrID > 0 && dwStrID < RCID_MAX )
    {
		MSLoadString(GetInstance(), dwStrID, (LPTSTR)acTxt, (sizeof(acTxt) >> 1) - 1 );
    }
	else
	{		
		strcpy(acTmp,(char*)dwStrID);
		MSMultiByteToWideChar( 0, 0,(LPCSTR)acTmp, sizeof(acTmp), (LPWSTR)acTxt, sizeof(acTxt)>>1);
	}
	
	MSSetDlgItemText(hWnd, nIDDlgItem, (LPCTSTR)acTxt);

	return TRUE;
}

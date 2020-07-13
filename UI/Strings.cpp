#include "MSWindows.h"
#include "Strings.h"

int MSWideChar2MultiByte(const char* wcStr, char *MultiStr, int nMultiStrLen)
{
    int i = 0;
    int nLen = 0;

    nLen = MSwcslen(wcStr);
    
    if(wcStr == NULL || MultiStr == NULL || nMultiStrLen == 0)
    {
        return 0;
    }

    for(i = 0; i < nLen; i++)
    {
        if(i < nMultiStrLen)
        {
            MultiStr[i] = wcStr[i * 2 + 1];
        }
    }

    if(i < nMultiStrLen)
    {
        MultiStr[i] = '\0';
    }
    else
    {
        MultiStr[i - 1] = '\0';
    }
    
    return i;
    
}

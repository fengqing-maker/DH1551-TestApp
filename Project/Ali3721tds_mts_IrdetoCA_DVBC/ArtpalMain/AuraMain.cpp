
#include "MSWindows.h"
#include "Aura.h"
#include "adi_os.h"
#include "adi_osg.h"
#include "AuraMain.h"
#include "adi_debug.h"
#include "DecompressResources.h"
#include "adi_toolset.h"
#include "ArtpalMain.h"

#define SCREEN_HEIGHT           ( 720 )
#define SCREEN_WIDTH            ( 1280 )
#define RCCOUNT 3

//int g_nClientType = 0 ;

void AuraMain( void )
{
	BOOL bRet = FALSE;
	int  nBit = 32;
	unsigned int unRet = 0;
	ADI_HANDLE hHandle = NULL;
	unsigned char * pucResourcesData = NULL;
	unsigned char * pucAuraData = NULL;

	unsigned char * apucRCData[2]	= { NULL };
	unsigned int aunDataType[2]		= { 0 };
	unsigned int aunRcDataLen[2]	= { 0 };


	unsigned char *apucRCDataTemp[RCCOUNT] = { NULL };
	unsigned int  aunRcDataLenTemp[RCCOUNT] = { 0 };

	unsigned char * pucRadioIFrameBuf = NULL;
	unsigned int unRadioIFrameLen = 0;
	unsigned int unRadioType = 3;
	
	aunDataType[ 0 ] = 1;
	aunDataType[ 1 ] = 2;

	pucResourcesData = g_aucRC;
	
	bRet = ParseResourcesData(pucResourcesData, apucRCDataTemp, aunRcDataLenTemp, sizeof(aunRcDataLenTemp) / sizeof(unsigned int));
	if (bRet == FALSE)
	{
		ADIASSERT(bRet == TRUE);
		return;
	}

	if (apucRCDataTemp[0] != NULL || aunRcDataLenTemp[0] > 0)
	{
		apucRCData[0] = apucRCDataTemp[0];
		aunRcDataLen[0] = aunRcDataLenTemp[0];
	}

	if (apucRCDataTemp[1] != NULL || aunRcDataLenTemp[1] > 0)
	{
		apucRCData[1] = apucRCDataTemp[1];
		aunRcDataLen[1] = aunRcDataLenTemp[1];
	}

	if (apucRCDataTemp[2] != NULL || aunRcDataLenTemp[2] > 0)
	{
		pucRadioIFrameBuf = apucRCDataTemp[2];
		unRadioIFrameLen = aunRcDataLenTemp[2];
	}
	else
	{
		//×öÄ¬ÈÏ²Ù×÷
	}
    ADI_HANDLE   hSurface = NULL ;
    ADIOSGSurfaceInfo_S  sSurfaceInfo ;
    
    ADIOSGCreateSurface(EM_ADIOSG_PIXEL_FORMAT_ARGB_8888 ,1280,720, &hSurface) ;
    ADIOSGGetSurfaceInfo(hSurface, &sSurfaceInfo) ;
    pucAuraData =(unsigned char *)sSurfaceInfo.m_pvSurfaceMem;

	if(pucAuraData == NULL)
	{
		ADIOSFree(apucRCDataTemp[0]);
		apucRCDataTemp[0] = NULL;
		aunRcDataLenTemp[0] = 0;

		ADIOSFree(apucRCDataTemp[1]);
		apucRCDataTemp[1] = NULL;
		aunRcDataLenTemp[1] = 0;
		return;
	}
	    
	memset( pucAuraData,0, 1280 * 720 * 4 );
	
    unRet = AuraInit ( pucAuraData, 1280 * 720 * 4, apucRCData, aunRcDataLen, aunDataType, 2 );
    
	if ( unRet > 0 )
    {         
	    AuraBoot ( ( AURAMAIN ) AuraApp, 5 * 17, 512 * 1024 );
		printf("@@@@after AuraBoot\n");
    }

	return;
}

unsigned int GetWidth( void )
{
	return SCREEN_WIDTH;
}

unsigned int GetHeight( void )
{
	return SCREEN_HEIGHT;
}


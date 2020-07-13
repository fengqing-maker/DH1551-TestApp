#include "MSWindows.h"
#include "CRC.h"
#include "Decompresslzma.h"
#include "DecompressResources.h"
#include "adi_flash.h"
#include "adi_os.h"



#define HDRCMEMSIZE		((1024+512)*1024)
#define SDRCMEMSIZE		(512*1024)
#define RCHEADMAGICID	(0xABCDDCBA)


static BOOL VerifyDataCRC(unsigned int unInputDataCRC, unsigned char ucInputData[], unsigned int unInputLen);


BOOL ReadResourcesDataWindowsAndLiunx(unsigned char **pucResourcesData,char cFileName[])
{
	int nRet = 0;
	FILE *fResourcesHandle = NULL;

	if (pucResourcesData == NULL || cFileName == NULL || (strlen(cFileName) == 0))
	{
		return FALSE;
	}

	fResourcesHandle = fopen(cFileName, "rb");
	if (fResourcesHandle == NULL)
	{
		return FALSE;
	}

	*pucResourcesData = (unsigned char *)ADIOSMalloc( HDRCMEMSIZE *sizeof(unsigned char));

	if (*pucResourcesData == NULL)
	{
		return FALSE;
	}

	nRet = fread(*pucResourcesData, sizeof(unsigned char), HDRCMEMSIZE*sizeof(unsigned char), fResourcesHandle);
	if (nRet == 0)
	{
	
	    ADIOSFree(*pucResourcesData);
		*pucResourcesData = NULL;
		fclose(fResourcesHandle);
		return FALSE;
	}

	fclose(fResourcesHandle);
	fResourcesHandle = NULL;

	return TRUE;
}

BOOL ReadResourcesData(unsigned char **pucResourcesData, unsigned int unRCStartAddress)
{
	int nRet = 0;
	BOOL bRet = FALSE;

	ADI_Error_Code	E_ADIErroeCode = 0;

	if (pucResourcesData == NULL || unRCStartAddress == 0)
	{
		return bRet;
	}


	*pucResourcesData = (unsigned char *)ADIOSMalloc( HDRCMEMSIZE * sizeof(unsigned char));

	if (*pucResourcesData == NULL)
	{
		return bRet;
	}

	E_ADIErroeCode = ADIFlashRead(unRCStartAddress, *pucResourcesData, HDRCMEMSIZE * sizeof(unsigned char));
	if (E_ADIErroeCode != ADI_SUCCESS)
	{	
		ADIOSFree(*pucResourcesData);
		*pucResourcesData = NULL;
		bRet = FALSE;
	}
	else
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL ParseResourcesData(unsigned char ucResourcesData[], unsigned char *apucRCData[], unsigned int  aucRcDataLen[],int nRCCount)
{
	BOOL bRet = FALSE;
	RCDataHead_S ouputRCDataHead;
	unsigned char *pucinputData = NULL;

	unsigned char *pucOuputData = NULL;
	unsigned int  unOuputSize = 0;

	if (ucResourcesData == NULL || apucRCData == NULL || aucRcDataLen == NULL || nRCCount < 2)
	{
		return FALSE;
	}

	pucinputData = ucResourcesData;

	do
	{
		memset(&ouputRCDataHead, 0, sizeof(RCDataHead_S));

		memcpy(&ouputRCDataHead, pucinputData, sizeof(RCDataHead_S));

		if (ouputRCDataHead.unMagicID != RCHEADMAGICID)
		{
			break;
		}

		bRet = VerifyDataCRC(ouputRCDataHead.unCRC, (unsigned char *)&ouputRCDataHead, sizeof(RCDataHead_S)-sizeof(unsigned int));
		if (bRet == FALSE)
		{
			break;
		}

		pucinputData += sizeof(RCDataHead_S);

		bRet = ConstructCompressRCData((unsigned char *)pucinputData, ouputRCDataHead.unSize, &pucOuputData, &unOuputSize, ouputRCDataHead.ucCompress);
		
		if (bRet == FALSE || pucOuputData == NULL || unOuputSize == 0)
		{
			break;
		}

		if (ouputRCDataHead.ucType == E_RC)
		{
			apucRCData[0]   = pucOuputData;
			aucRcDataLen[0] = unOuputSize;
		}
		else if (ouputRCDataHead.ucType == E_FONT)
		{
			apucRCData[1]   = pucOuputData;
			aucRcDataLen[1] = unOuputSize;
		}

		pucinputData += ouputRCDataHead.unSize;

	} while (1);

	return bRet;
}

BOOL ConstructCompressRCData(unsigned char ucInputData[], unsigned int inputDataSize,unsigned char **pucOuputData,unsigned int  *punOuputSize,unsigned char ucCompress)
{
	BOOL bRet = FALSE;
	int  nRet = -1;

	unsigned char *pucRCData = NULL;
	unsigned int  unRCDataSize = 0;
	DecompressHead_S ouputDecompressHead;

	if (ucInputData == NULL || inputDataSize == 0 || pucOuputData == NULL || punOuputSize == NULL)
	{
		return bRet;
	}

	memset(&ouputDecompressHead, 0, sizeof(DecompressHead_S));

	memcpy(&ouputDecompressHead, ucInputData, sizeof(DecompressHead_S));

	//Verify Head
	bRet = VerifyDataCRC(ouputDecompressHead.unHeadCRC32, (unsigned char *)&ouputDecompressHead, sizeof(DecompressHead_S)-sizeof(ouputDecompressHead.unHeadCRC32));

	if (bRet == FALSE)
	{
		return bRet;
	}

	//verify Compress Data
	bRet = VerifyDataCRC(ouputDecompressHead.unCompressDataCRC32, (unsigned char *)(ucInputData + sizeof(DecompressHead_S)), ouputDecompressHead.unCompressDataSize);

	if (bRet == FALSE)
	{
		return bRet;
	}

	ucInputData += sizeof(DecompressHead_S);

	inputDataSize -= sizeof(DecompressHead_S);

	pucRCData = (unsigned char *)ADIOSMalloc( ouputDecompressHead.unOrgDataSize * sizeof(unsigned char));//new unsigned char[ouputDecompressHead.unOrgDataSize];
	if( pucRCData == NULL)
	{
		return FALSE;
	}
	
	memset(pucRCData,0,ouputDecompressHead.unOrgDataSize * sizeof(unsigned char));
	
	unRCDataSize = ouputDecompressHead.unOrgDataSize;

	if (ucCompress == 1)
	{
		nRet = LzmaDecompress(pucRCData, &unRCDataSize, ucInputData, &inputDataSize, ouputDecompressHead.aucLzmaProperties, LZMA_PROPS_SIZE);
		if (nRet != 0)
		{
			ADIOSFree((void *)pucRCData);
			pucRCData = NULL;
			return bRet;
		}

		bRet = VerifyDataCRC(ouputDecompressHead.unOrgDataCRC32, (unsigned char *)pucRCData, unRCDataSize);
		if (bRet == FALSE)
		{
			ADIOSFree((void *)pucRCData);
			pucRCData = NULL;
			return bRet;
		}
	}
	else
	{
		memcpy(pucRCData, ucInputData, inputDataSize*sizeof(unsigned char));
		bRet = TRUE;
	}

	*pucOuputData = pucRCData;
	*punOuputSize = unRCDataSize;

	return bRet;
}

static BOOL VerifyDataCRC(unsigned int unInputDataCRC, unsigned char ucInputData[], unsigned int unInputLen)
{
	BOOL bRet = FALSE;

	unsigned int unDataCRC = 0xFFFFFFFF;

	if (ucInputData == NULL || unInputLen == 0)
	{
		return bRet;
	}

	unDataCRC = CalculateCRC32((unsigned char *)ucInputData, unInputLen);

	if (unInputDataCRC == unDataCRC)
	{
		bRet = TRUE;
	}

	return bRet;
}


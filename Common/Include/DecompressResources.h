#ifndef _DECOMPRESSRESOURSES_H_
#define _DECOMPRESSRESOURSES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"


#define LZMA_PROPS_SIZE (5)
#define IMAGE_EXTEND (64)
#define DECOMPRESS_TYPE_LZMA (0x11111111) 

typedef struct
{
	unsigned int unCompressType;
	unsigned int unOrgDataSize;
	unsigned int unOrgDataCRC32;

	unsigned int unCompressDataSize;
	unsigned int unCompressDataCRC32;

	unsigned char aucLzmaProperties[LZMA_PROPS_SIZE];
	unsigned char aucReserved[3]; /*与aucLzmaProperties对应--4字节对齐, 没有使用*/

	unsigned int unExeMemAddr;

	unsigned char aucExtend[IMAGE_EXTEND];

	unsigned int unHeadCRC32;/*以上所有数据的CRC32*/

}DecompressHead_S;


typedef struct
{
	unsigned int  unMagicID;
	unsigned char ucType;
	unsigned char ucCompress;
	unsigned char ucReserved[2];
	unsigned int  unSize;
	unsigned int  unCRC;
}RCDataHead_S;

typedef enum E_RC_DATA
{
	E_FONT,
	E_RC,
	E_SATELLITE_TP_LIST,
	E_FIRST_IFREME,
	E_END
};

BOOL ReadResourcesData(unsigned char **pucResourcesData, unsigned int unRCStartAddress);

BOOL ReadResourcesDataWindowsAndLiunx(unsigned char **pucResourcesData, char cFileName[]);

BOOL ParseResourcesData(unsigned char ucResourcesData[], unsigned char *apucRCData[], unsigned int  aucRcDataLen[], int nRCCount);

BOOL ConstructCompressRCData(unsigned char ucInputData[], unsigned int inputDataSize, unsigned char **pucOuputData, unsigned int  *punOuputSize, unsigned char ucCompress);

#ifdef __cplusplus
}
#endif

#endif
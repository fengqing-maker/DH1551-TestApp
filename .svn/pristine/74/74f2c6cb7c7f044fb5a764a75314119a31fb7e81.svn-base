/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : Carousel.c                                                 *
*                                                                            *
*   Description : DVB-SSU sections handling.                                 *
*                                                                            *
*****************************************************************************/

#include <sys_config.h>

/* ---------------- */
#include <LoaderCorePrivate.h>
#include <DemuxManager.h>
#include <Utilization.h>
#include "Carousel.h"
#include "LoaderCoreSPI.h"


/* Maximum Time for SSU download. */
#define SSU_DOWNLOAD_TIMEOUT      3 * 60 * 1000    /* 3 minutes */

/* Maximum Retry Times for SSU download. */
#define SSU_DOWNLOAD_ATTEMPT_MAX      3

/* Estimated download time descriptor tag */
#define TAG_ESTIMATED_DOWNOLOAD_TIME       0x07
#define LENGTH_ESTIMATED_DOWNOLOAD_TIME       0x04
#define MAX_DOWNLOAD_TIMEOUT       24 * 60 * 60 * 1000

/* Table ID for DVB-SSU sections. */
#define DSI_TID  0x3B
#define DII_TID  0x3B
#define DDB_TID  0x3C

/* Message ID for DVB-SSU sections. */
#define DSI_MESSAGE_ID  0x1006
#define DII_MESSAGE_ID  0x1002
#define DDB_MESSAGE_ID  0x1003

/*  */
#define FAKE_COMPATIBILITY_DESCRIPTOR_LEN      2
#define MINIMUM_COMPATIBILITY_DESCRIPTOR_LEN      11


/* Group structure from DSI. */
typedef struct _group_info_st 
{
    lc_uint32  groupId;
    lc_uint32  groupSize;
    
} group_info_st;

/* DII message parsing */
typedef struct _ddb_info_st 
{
    lc_uint32  blockNumber;
    lc_uint16  blockSize;
    lc_uchar*  pBlockData;
    lc_uint32  NumberReceived;	
    
} ddb_info_st;

/* Module structure from DII. */
typedef struct _module_info_st
{
    lc_uint16  moduleId;
    lc_uint32  moduleSize;
    lc_uchar   moduleVersion;
    lc_uint16  generalBlockSize;
    lc_uint32  maxBlockNumber;
    lc_uint16  receivedBlockNumber;
    ddb_info_st* pDDBInfoStruct;
    
} module_info_st;

/* Download Group information in DSI. */
static group_info_st gDownloadGroup;

/* Information of one DVB-SSU module. */
static module_info_st* gpModuleInfoStruct;

/* Total number of DVB-SSU modules */
static lc_uint16 gNumberOfModules;

/* Global memory for gathering download data from SSU stream. */
static lc_buffer_st gSSUDataBuffer;

static lc_bool isTimeoutDownload = LC_FALSE;
static lc_uint32 timeoutDownload = 3 * 60 * 1000;


static void LC_TimerNotifyProc(lc_uint32 timerId,   void * timerHandle)
{
	isTimeoutDownload = LC_TRUE;
}

static lc_result ParseDsmccAdaptionFields(lc_buffer_st *pData, lc_uint32 *pBitPos)
{
    LC_UNUSED(pData);
    LC_UNUSED(pBitPos);
    return  LC_SUCCESS;
}

/* The CompatibilityDescriptor structure, defined in ISO/IEC 13818-6 ch06 */
static lc_bool ParseCompatibilityDescriptor(lc_buffer_st *pData, lc_uint32 *pBitPos)
{
    lc_result  result = LC_SUCCESS;
    lc_uint16  descriptorLength = 0;
    lc_uint16  descCount = 0;
    lc_uint16  i = 0;
    lc_uchar   descType = 0;
    lc_uchar   descLen = 0;
    lc_uchar   OUI[3] = {0};
    lc_uint16  model = 0;
    lc_uint16  version = 0;
    lc_uchar   subDescCount = 0;
    lc_uchar   specifierType = 0;
    lc_bool    bHardwareFound = LC_FALSE;
    lc_bool    bSoftwareFound = LC_FALSE;
    lc_bool    bSubVariantFound = LC_TRUE;
    lc_uchar   tmpStr[256];   /* to skip string in compatibilityDescriptor sent from OpenCaster */
    lc_uint16 deviceDownloadSequence = 0;
    lc_bool isMigration = LC_FALSE;
    lc_uchar psModifyFlag = 0;	

    result = MessageParser_ReadBits(pData, pBitPos, 16, &descriptorLength);
    N2H16(&descriptorLength);

    if ((LC_SUCCESS == result) && (descriptorLength > 0))
    {
        if (LC_SUCCESS == result)
        {
            result = MessageParser_ReadBits(pData, pBitPos, 16, &descCount);
            N2H16(&descCount);

            TRACE_LOG2(TRACE_DEBUG, "parseCompatibilityDescriptor: len %d, descCount %d\n", descriptorLength, descCount);
        }

        if (LC_SUCCESS == result)
        {
            
            /* For len equals 2, descCount should be 0, empty compatibilityDescriptor. Return descriptor length directly. */
            if((descriptorLength < (descCount * MINIMUM_COMPATIBILITY_DESCRIPTOR_LEN)) && 
                (descriptorLength > FAKE_COMPATIBILITY_DESCRIPTOR_LEN))
            {
                /* There is "hello" in DSI.sec from OpenCaster. Skips them. */
                /* data in hex */
                TRACE_LOG0(TRACE_DEBUG, "  [CompDesc] ");
                for(i=0; i<descriptorLength; i++)
                {
                    TRACE_LOG1(TRACE_DEBUG, "%02x ", pData->bytes[i + 2]);
                }
               
                /* string information for the same hex data above. Just for observation. */
                LC_memcpy(tmpStr, pData->bytes + 2, descriptorLength);
                tmpStr[descriptorLength] = '\0';
                TRACE_LOG1(TRACE_DEBUG, "  [%s]\n", tmpStr);

                *pBitPos -= 2;
                result = MessageParser_ReadBits(pData, pBitPos, 8 * descriptorLength, tmpStr);

                /* No error code should be set by empty or character compatibilityDescriptor. */
            }
            else if ((descriptorLength >= (descCount * MINIMUM_COMPATIBILITY_DESCRIPTOR_LEN)) && (descCount > 0))
            {
                
                /* Migration? */
                isMigration = LC_UtilCheckMigrationMode();
                
                /* compatibility contains valid data: desc len + desc count + desc data */
                for(i=0; i<descCount; i++)
                {
                    result = MessageParser_ReadBits(pData, pBitPos, 8, &descType);
                    result = MessageParser_ReadBits(pData, pBitPos, 8, &descLen);
                    result = MessageParser_ReadBits(pData, pBitPos, 8, &specifierType);
                   
                    TRACE_LOG2(TRACE_DEBUG, "  [CompDesc] descType 0x%02x, descLen %d\n", descType, descLen);
                   
                    if(0x01 == specifierType)
                    {
                        result = MessageParser_ReadBits(pData, pBitPos, 24, OUI);
                        result = MessageParser_ReadBits(pData, pBitPos, 16, &model);
                        N2H16(&model);
                        result = MessageParser_ReadBits(pData, pBitPos, 16, &version);
                        N2H16(&version);
                        result = MessageParser_ReadBits(pData, pBitPos, 8, &subDescCount);
                       
                        TRACE_LOG3(TRACE_DEBUG, "  [CompDesc] OUI 0x%02x%02x%02x\n", OUI[0], OUI[1], OUI[2]);
                        TRACE_LOG3(TRACE_DEBUG, "  [CompDesc] model 0x%04x, version 0x%04x, subDescCount %d\n", model, version, subDescCount);
                        
                        switch(descType)
                        {
                            case 0x00:
                                /* pad descriptor. */
                                break;
                                
                            case 0x01:
                            
                                /* system hardware descriptor */
                               
                                /* STB hardware code mapped to model in HWDescriptor */
                                /* check if hardware code matched */

                                /* Check OUI. */
                                result = LC_UtilCheckOUI(OUI);

                                /* Check Manufacturer ID. */
                                if (LC_SUCCESS == result)
                                {
                                    result = LC_UtilCheckManufacturerId(model);
                                }

                                /* Check Hardware Version. */
                                if (LC_SUCCESS == result)
                                {
                                    result = LC_UtilCheckHardwareVersion(version);
                                }
                                
                                if (LC_SUCCESS == result)
                                {
                                    bHardwareFound = LC_TRUE;
                                    TRACE_LOG0(TRACE_INFO, "  [CompDesc] System hardware descriptor found.\n");
                                }
                                
                                break;
                                
                            case 0x02:
                            
                                /* system software descriptor */
                               
                                /* STB variant mapped to model in SWDescriptor. 
                                 * DownloadSequenceNumber mapped to version in SWDescriptor 
                                 */
                                 
                                /* Check download sequence number. */
                                if (LC_FALSE == isMigration)
                                {
                                    result = LC_UtilGetDownloadSequence(&deviceDownloadSequence);
                                    
                                    LoaderCoreSPI_UPDATE_UI(UI_INFO_TYPE_DSN,sizeof(lc_uint16),(void*)(&version));
                                    if (LC_SUCCESS == result)
                                    {
                                        result = LC_CheckDownloadSequence(version, deviceDownloadSequence);
                                    }

									if(LC_ERROR_SAME_DOWNLOAD_SEQUENCE_NUMBER == result)
									{
										LoaderCoreSPI_GetPSModifyFlag(&psModifyFlag);  /* PS modify to recovery ignore the same error */
										if (PS_MODIFIED == psModifyFlag)
										{
											result = LC_SUCCESS;
      									}
									}

                                }

                                /* Check OUI. */
                                if (LC_SUCCESS == result)
                                {
                                    result = LC_UtilCheckOUI(OUI);
                                }

                                /* Check variant. */
                                if (LC_SUCCESS == result)
                                {
                                    result = LC_UtilCheckVariant(isMigration, &model, LC_NULL);
                                }
                                
                                if(LC_SUCCESS == result)
                                {
                                    bSoftwareFound = LC_TRUE;
                                    TRACE_LOG0(TRACE_INFO, "  [CompDesc] System software descriptor found.\n");
                                }
                                
                                break;
                                
                            case 0x40:

                                bSubVariantFound = LC_FALSE;
                                 
                                /* Check OUI. */
                                result = LC_UtilCheckOUI(OUI);

                                /* Check Sub-variant. */
                                if (LC_SUCCESS == result)
                                {
                                    result = LC_UtilCheckVariant(isMigration, LC_NULL, &model);
                                }

                                /* The "version" field should equal to ZERO. */
                                if (LC_SUCCESS == result)
                                {
                                    if (0 != version)
                                    {
                                        result = LC_ERROR_INVALID_DATA;
                                    }
                                }
                                
                                if (LC_SUCCESS == result)
                                {
                                    bSubVariantFound = LC_TRUE;
                                    TRACE_LOG0(TRACE_INFO, "  [CompDesc] system private descriptor found.\n");
                                }
                                
                                break;
                                
                            default:
                                /* reserved */
                                break;
                        }
                       
                        if(subDescCount > 0)
                        {
                            /* parse subDescriptor in HW_descriptor, SW_descriptor and etc */
                            /* todo. no subDescriptor currently */
                            /* skips subDescriptor */
                        }
                    }
                }
            }
        }
    }

    /* check if hardware code matched and has valid software version. Pay attention to subvariant check!!! */
    return (lc_bool)(bHardwareFound && bSoftwareFound && bSubVariantFound);
}

static lc_result ParseGroupInfoByte(lc_buffer_st *pData, lc_uint32 *pBitPos)
{
    lc_result result = LC_SUCCESS;
    lc_uchar tagEDTD = 0;
    lc_uint16 EDTDDataLen = 0;
    lc_uint32 EDTDTime = 0;
	
    result = MessageParser_ReadBits(pData, pBitPos, 8, &tagEDTD);

	if(TAG_ESTIMATED_DOWNOLOAD_TIME == tagEDTD)
	{
        result = MessageParser_ReadBits(pData, pBitPos, 8, &EDTDDataLen);
        if(LENGTH_ESTIMATED_DOWNOLOAD_TIME == EDTDDataLen)
        {
	        result = MessageParser_ReadBits(pData, pBitPos, 32, &EDTDTime);
			N2H32(&EDTDTime);

			if(EDTDTime > MAX_DOWNLOAD_TIMEOUT / SSU_DOWNLOAD_ATTEMPT_MAX)
	        {	
	 	       	EDTDTime = MAX_DOWNLOAD_TIMEOUT / SSU_DOWNLOAD_ATTEMPT_MAX;
			}

			if(0 != EDTDTime)
			{
				timeoutDownload = SSU_DOWNLOAD_ATTEMPT_MAX * EDTDTime * 1000 * 2;
			}
        }
	}
	
    return  result;
}

static lc_result ParseGroupInfoIndication(lc_buffer_st *pData, lc_uint32 *pBitPos)
{
    lc_result  result = LC_SUCCESS;
    lc_uint16 groupNumber = 0;
    lc_uint16 i = 0;
    lc_uint16 groupInfoLen = 0;
    lc_uint16 privateDataLen = 0;
    lc_bool bFound = LC_FALSE;
    group_info_st groupInfoStruct;
    
      
    result = MessageParser_ReadBits(pData, pBitPos, 16, &groupNumber);
    N2H16(&groupNumber);

    TRACE_LOG1(TRACE_DEBUG, "parseGroupInfoIndication: groupNumber %d\n", groupNumber);
   
    for(i=0; i<groupNumber; i++)
    {
        result = MessageParser_ReadBits(pData, pBitPos, 32, &groupInfoStruct.groupId);
        N2H32(&groupInfoStruct.groupId);
        result = MessageParser_ReadBits(pData, pBitPos, 32, &groupInfoStruct.groupSize);
        N2H32(&groupInfoStruct.groupSize);

        TRACE_LOG2(TRACE_DEBUG, "  [GroupInfo] groupId 0x%08x, groupSize 0x%08x\n",
                        groupInfoStruct.groupId, groupInfoStruct.groupSize);
       
        bFound = ParseCompatibilityDescriptor(pData, pBitPos);
       
        result = MessageParser_ReadBits(pData, pBitPos, 16, &groupInfoLen);
        N2H16(&groupInfoLen);

        TRACE_LOG1(TRACE_DEBUG, "  [GroupInfo] groupInfoLen %d\n", groupInfoLen);
       
        if(groupInfoLen > 0)
        {
            result = ParseGroupInfoByte(pData, pBitPos);   /* US 288339 add one estimated download time descriptor as ESD */
        }
       
        /* The detail mismatch error code was set in compatibilityDescriptor. */
        /* No need set error code here if(LC_FALSE == bFound) */
        if(LC_TRUE == bFound)
        {
            gDownloadGroup.groupId = groupInfoStruct.groupId;
            gDownloadGroup.groupSize = groupInfoStruct.groupSize;
        }
    }
   
    result = MessageParser_ReadBits(pData, pBitPos, 16, &privateDataLen);
    N2H16(&groupInfoLen);

    if(privateDataLen > 0)
    {
        /* This field is user defined. */
        /* todo based on SD for Loader v5. No privateDataByte currently */

        /* skips privateDataByte */
    }
   
    TRACE_LOG1(TRACE_DEBUG, "  [GroupInfo] privateDataLen %d\n", privateDataLen);
    TRACE_LOG2(TRACE_INFO, "  [GroupInfo] --> found groupId 0x%08x, groupSized 0x%08x\n",
                    gDownloadGroup.groupId, gDownloadGroup.groupSize);
   
    return  result;
}

static lc_result LC_ProcessDSI(void)
{
    lc_result result = LC_SUCCESS;
    lc_sint32 compare = 0;
    lc_uchar* pBuffer = LC_NULL;
    lc_uchar dsiTID = 0;
    lc_uint16 dsiSectionLength = 0;
    lc_uint16 tidExtension;
    lc_uchar dsiVersion = 0;
    lc_uchar sectionNumber = 0;
    lc_uchar lastSectionNumber = 0;
    lc_uchar protocolDiscrimitor = 0;
    lc_uchar dsmccType = 0;
    lc_uint16 messageId = 0;
    lc_uint32 transactionId = 0;    /* 4 bytes */
    lc_uchar reservedByte;
    lc_uchar adaptionLen = 0;
    lc_uint16 messageLen = 0;
    lc_uchar tmpBuff[20];
    lc_uchar serviceId[20];
    lc_uint16 privateDataLength = 0;
    lc_uint32 sectionLength = 0;
    lc_uint32 crc32Org = 0;
    lc_uint32 crc32Cal = 0;
    lc_buffer_st dsiSection = {LC_NULL, 0};
    lc_uint32 bitPos = 0;
    lc_uint16 count = 0;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;

    lc_filter_info filterInfo;

    LC_memset(&filterInfo, 0x0, sizeof(lc_filter_info));

    /*Set up filter condition.*/
    filterInfo.match[0] = DSI_TID;
    filterInfo.match[1] = 0x00;
    filterInfo.match[2] = 0x00;
    filterInfo.mask[0] = 0xFF;
    filterInfo.mask[1] = 0xFF;
    filterInfo.mask[2] = 0xFE;
    filterInfo.filterDepth = 3;

    TRACE_LOG3(TRACE_INFO, "BLOADER_ProcessDSI: match 0x%02x %02x %02x\n",
                    filterInfo.match[0], filterInfo.match[1], filterInfo.match[2]);
    TRACE_LOG3(TRACE_INFO, "BLOADER_ProcessDSI: mask 0x%02x %02x %02x\n",
                    filterInfo.mask[0], filterInfo.mask[1], filterInfo.mask[2]);
       
    bitPos = 0;

    if(LC_SUCCESS == result)
    {
        /*Set filter conditions.*/
        result = LC_SetFilter(&filterInfo);
    }

    if(LC_SUCCESS == result)
    {
        /*Start demux.*/
        result = LC_StartDemux();
    }

    while(count < SSU_DOWNLOAD_ATTEMPT_MAX)
    {
        if((LC_SUCCESS == result) || (LC_ERROR_INCORRECT_SECTION_CRC32 == result))
        {
            /*Once the demux has started, we can call this function to get a section.*/
            result = LC_ReadSection(&pBuffer,
                             &sectionLength,
                             SSU_DOWNLOAD_TIMEOUT);    /* if 0 is used as the timeout. This function will not return untile a section is got.*/
            if(LC_SUCCESS != result)
            {
                errCode = ERROR_CODE_TABLE_TIMEOUT;
                break;
            }
        }

        /* If incorrect CRC32, retry section receiving SSU_DOWNLOAD_ATTEMPT_MAX times */
        if(LC_SUCCESS == result)
        {
            dsiSection.bytes = pBuffer;
            dsiSection.length = sectionLength;
            crc32Cal = CRC_MPEG32(dsiSection.bytes, sectionLength - 4);
            crc32Org = LC_GetUint32(dsiSection.bytes, sectionLength - 4);
            if(crc32Cal != crc32Org)
            {
                count ++;
                TRACE_LOG2(TRACE_ERROR, "BLOADER_ProcessDSI: org crc32 0x%08x, cal crc32 0x%08x\n", crc32Org, crc32Cal);
            }
            else
            {
                count = 0;
                /* If section with correct crc32, start to parse fields followed */
                break;
            }
        }
    }
    
    if(count == SSU_DOWNLOAD_ATTEMPT_MAX)
    {
        result = LC_ERROR_INCORRECT_SECTION_CRC32;
        errCode = ERROR_CODE_INVALID_DSI_CRC;
    }
    
    if((LC_SUCCESS == result) || (LC_ERROR_TIMEOUT == result) || (LC_ERROR_INCORRECT_SECTION_CRC32 == result))
    {
        LC_StopDemux();
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 8, &dsiTID);
        /* Analyse DSI table ID */
        if(DSI_TID != dsiTID)
        {
            TRACE_LOG1(TRACE_ERROR, "  [DSI] Wrong DSI. Table ID 0x%02X\n", dsiTID);

            result = LC_ERROR_WRONG_SECTION;
            errCode = ERROR_CODE_DSI_WRONG_SECTION;
        }      
    }

    if(LC_SUCCESS == result)
    {
        /*Check length.*/
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 16, &dsiSectionLength);
        N2H16(&dsiSectionLength);
        dsiSectionLength &= 0x0FFF;
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 16, &tidExtension);
        N2H16(&tidExtension);
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 8, &dsiVersion);
        dsiVersion = (dsiVersion & 0x3E) >> 1;

        if((lc_uint32)(dsiSectionLength + 3) != sectionLength)
        {
            TRACE_LOG2(TRACE_ERROR, "  [DSI] Invalid section length. dsiSectionLen %d, sectionLength %d\n", 
                            dsiSectionLength, sectionLength);

            result = LC_ERROR_WRONG_SECTION;
            errCode = ERROR_CODE_WRONG_DSI_SECTION_SIZE;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 8, &sectionNumber);
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 8, &lastSectionNumber);
        /* section number & last section number should be 0 for DSI */
        if((0 != sectionNumber) || (0 != lastSectionNumber))
        {
            result = LC_ERROR_WRONG_SECTION;
            errCode = ERROR_CODE_DSI_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        /* Check protocolDiscrimitor and dsmccType in DownloadServerInitiate message */
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 8, &protocolDiscrimitor);
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 8, &dsmccType);
        if((0x11 != protocolDiscrimitor) || (0x03 != dsmccType))
        {
            TRACE_LOG2(TRACE_ERROR, "  [DSI] Invalid protocolDiscrimitor or dsmccType. protocolDiscrimitor %02X, dsmccType %02X\n",
                            protocolDiscrimitor, dsmccType);

            result = LC_ERROR_WRONG_MESSAGE_ID;
            errCode = ERROR_CODE_DSI_WRONG_MESSAGE_ID;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 16, &messageId);
        N2H16(&messageId);
        if(DSI_MESSAGE_ID != messageId) /*0x1006*/
        {
            result = LC_ERROR_WRONG_MESSAGE_ID;
            errCode = ERROR_CODE_DSI_WRONG_MESSAGE_ID;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 32, &transactionId);
        N2H32(&transactionId);

        /*Check the least two bytes, it must be 0x0000 or 0x0001 according to SSU spec.*/
        if(0x2 <= (transactionId & 0xFFFF))
        {
            TRACE_LOG1(TRACE_ERROR, "  [DSI] Invalid transactionId 0x%08x.\n", transactionId);

            result = LC_ERROR_WRONG_TRANSACTION_ID;
            errCode = ERROR_CODE_DSI_WRONG_TRANSACTION_ID;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 8, &reservedByte);
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 8, &adaptionLen);
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 16, &messageLen);
        N2H16(&messageLen);
      
        TRACE_LOG2(TRACE_DEBUG, "  [DSI] adaptionLen 0x%x, messagelLen 0x%02x\n", adaptionLen, messageLen);
       
        if(adaptionLen > 0)
        {
            ParseDsmccAdaptionFields(&dsiSection, &bitPos); /* todo. no adaption field currently */
            bitPos += adaptionLen * 8;
        }
       
        /* check serviceId fields. Fixed value. 20 bytes 0xFF */
        LC_memset(tmpBuff, 0xFF, 20);
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 20 * 8, &serviceId);
        compare = LC_memcmp(serviceId, tmpBuff, 20);

        if(0 != compare)
        {
            TRACE_LOG0(TRACE_ERROR, "  [DSI] unwanted service id. It should be filled with 0xFF.\n");
            result = LC_ERROR_WRONG_SERVICE_ID;
            errCode = ERROR_CODE_DSI_WRONG_SERVICE_ID;
        }
    }
       
    if(LC_SUCCESS == result)
    {
        /* compatibility descriptor */
        /* For DSI, only length fields should be included by compatibilityDescriptor, and length should be 0 */
        ParseCompatibilityDescriptor(&dsiSection, &bitPos);
       
        result = MessageParser_ReadBits(&dsiSection, &bitPos, 16, &privateDataLength);
        N2H16(&privateDataLength);
        TRACE_LOG1(TRACE_DEBUG, "privateDataLength %d\n", privateDataLength);
        if(privateDataLength > 0)
        {
            /* GroupInfoIndication(). Defined in ETSI EN 301 192, table 44 */
            /* valid download information should be included in compatibilityDescriptor in groupInfoIndication. */
            result = ParseGroupInfoIndication(&dsiSection, &bitPos);
        }
    }

    ERR_REPORT_SetErrorCode(errCode);

    return  result;
}


static lc_result ParseDIIModuleInfoByte(lc_buffer_st *pData, lc_uint32 *pBitPos)
{
    lc_result result = LC_SUCCESS;
    lc_uchar type = 0;
    lc_uchar length = 0;

    /* Need further check. Get the structure based on hex file from OpenCaster. */
    TRACE_LOG0(TRACE_DEBUG, "parseDIIModuleInfoByte: ");

    /* Type */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pData, pBitPos, 8, &type);
    }

    /* Length */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pData, pBitPos, 8, &length);
    }

    /* Byte */
    if (LC_SUCCESS == result)
    {
        /* Just skip this field. */
        *pBitPos += 8 * length;
    }
      
    return  result;
}

static lc_result ParseDIIPrivateDataByte(lc_buffer_st *pData, lc_uint32 *pBitPos)
{
    LC_UNUSED(pData);
    LC_UNUSED(pBitPos);
    return  LC_SUCCESS;
}

static lc_result ParseDIIModuleLoop(lc_buffer_st *pData, lc_uint32 *pBitPos, lc_uint16 blockSize)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uint16 i = 0;
    lc_uchar moduleInfoLength = 0;
    module_info_st* pModuleInfoStruct = LC_NULL;
    

    result = MessageParser_ReadBits(pData, pBitPos, 16, &gNumberOfModules);
    if (LC_SUCCESS == result)
    {
        N2H16(&gNumberOfModules);
        TRACE_LOG1(TRACE_INFO, "parseDIIModuleLoop: gNumberOfModules %d\n", gNumberOfModules);
        if(0 == gNumberOfModules)
        {
            result = LC_ERROR_INVALID_DATA;
            errCode = ERROR_CODE_DII_NO_VALID_MODULE_INFO;
        }
    }

    if (LC_SUCCESS == result)
    {
        pModuleInfoStruct = (module_info_st*)LC_MALLOC(sizeof(module_info_st) * gNumberOfModules);
        if(LC_NULL == pModuleInfoStruct)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    if(LC_SUCCESS == result)
    {
        gpModuleInfoStruct = pModuleInfoStruct;
       
        for(i=0; i<gNumberOfModules; i++)
        {
            result = MessageParser_ReadBits(pData, pBitPos, 16, &pModuleInfoStruct->moduleId);
            N2H16(&pModuleInfoStruct->moduleId);
            result = MessageParser_ReadBits(pData, pBitPos, 32, &pModuleInfoStruct->moduleSize);
            N2H32(&pModuleInfoStruct->moduleSize);
            result = MessageParser_ReadBits(pData, pBitPos, 8, &pModuleInfoStruct->moduleVersion);

            pModuleInfoStruct->pDDBInfoStruct = LC_NULL;
            pModuleInfoStruct->generalBlockSize = blockSize;
            if(0 == (pModuleInfoStruct->moduleSize % blockSize))
            {
                pModuleInfoStruct->maxBlockNumber = pModuleInfoStruct->moduleSize / blockSize;
            }
            else
            {
                pModuleInfoStruct->maxBlockNumber = pModuleInfoStruct->moduleSize / blockSize + 1;
            }
            pModuleInfoStruct->receivedBlockNumber = 0;
            TRACE_LOG4(TRACE_INFO, "&[DIIModule] moduleId 0x%04x, moduleSize 0x%08x, moduleVersion %d, maxBlockNumber %d\n",
                            pModuleInfoStruct->moduleId, 
                            pModuleInfoStruct->moduleSize, 
                            pModuleInfoStruct->moduleVersion, 
                            pModuleInfoStruct->maxBlockNumber);
           
            result = MessageParser_ReadBits(pData, pBitPos, 8, &moduleInfoLength);
            TRACE_LOG1(TRACE_INFO, "&[DIIModule] moduleInfoLength %d\n", moduleInfoLength);
            if(moduleInfoLength > 0)
            {
                result = ParseDIIModuleInfoByte(pData, pBitPos);
            }
           
            pModuleInfoStruct ++;
        }
    }

    ERR_REPORT_SetErrorCode(errCode);
   
    return  result;
}

static lc_result LC_ProcessDII(void)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uchar* pBuffer = LC_NULL;
    lc_uint16 diiSectionLength = 0;
    lc_uchar  diiVersion = 0;
    lc_uchar  diiTID = 0;
    lc_uint16 tidExtension = 0;
    lc_uchar sectionNumber = 0;
    lc_uchar lastSectionNumber = 0;
    lc_uchar protocolDiscrimitor = 0;
    lc_uchar dsmccType = 0;
    lc_uint16 messageId = 0;
    lc_uint32 transactionId = 0;
    lc_uchar reservedByte = 0;
    lc_uchar  adaptionLen = 0;
    lc_uint16 messageLen = 0;
    lc_uint32 downloadId = 0;
    lc_uint16 blockSize = 0;
    lc_uchar windowSize = 0;
    lc_uchar ackPeriod = 0;
    lc_uint32 tcDownloadWindow = 0;
    lc_uint32 tcDownloadScenario = 0;
    lc_uint16 privateDataLength = 0;
    lc_uint32 crc32Org = 0;
    lc_uint32 crc32Cal = 0;
    lc_buffer_st diiSection;
    lc_uint32 bitPos = 0;
    lc_uint16 count = 0;
    lc_uint32 sectionLength = 0;
    lc_filter_info filterInfo;

    LC_memset(&filterInfo, 0x0, sizeof(lc_filter_info));

    /*Set up filter condition.*/
    filterInfo.match[0] = DII_TID;
    filterInfo.match[1] = (gDownloadGroup.groupId >> 8) & 0xFF;
    filterInfo.match[2] = gDownloadGroup.groupId & 0xFF;
    filterInfo.mask[0] = 0xFF;
    filterInfo.mask[1] = 0xFF;
    filterInfo.mask[2] = 0xFF;
    filterInfo.filterDepth = 3;
   
    TRACE_LOG3(TRACE_INFO, "BLOADER_ProcessDII: filter 0x%02x %02x %02x\n",
                    filterInfo.match[0], filterInfo.match[1], filterInfo.match[2]);
    TRACE_LOG3(TRACE_INFO, "BLOADER_ProcessDII: filter 0x%02x %02x %02x\n",
                    filterInfo.mask[0], filterInfo.mask[1], filterInfo.mask[2]);

    if(LC_SUCCESS == result)
    {
        /*Set filter conditions.*/
        result = LC_SetFilter(&filterInfo);
    }

    if(LC_SUCCESS == result)
    {
        /*Start demux.*/
        result = LC_StartDemux();
    }
    while(count < SSU_DOWNLOAD_ATTEMPT_MAX)
    {
        if((LC_SUCCESS == result) || (LC_ERROR_INCORRECT_SECTION_CRC32 == result))
        {

            /*Once the demux has started, we can call this function to get a section.*/
            result = LC_ReadSection(&pBuffer,
                             &sectionLength,
                             SSU_DOWNLOAD_TIMEOUT);    /* if 0 is used as the timeout. This function will not return untile a section is got.*/
            if(LC_SUCCESS != result)
            {
                errCode = ERROR_CODE_TABLE_TIMEOUT;
                break;
            }
        }

        if(LC_SUCCESS == result)
        {
            diiSection.bytes = pBuffer;
            diiSection.length = sectionLength;
            crc32Cal = CRC_MPEG32(diiSection.bytes, sectionLength - 4);
            crc32Org = LC_GetUint32(diiSection.bytes, sectionLength - 4);
            if(crc32Cal != crc32Org)
            {
                count ++;
                TRACE_LOG2(TRACE_ERROR, "BLOADER_ProcessDII: org crc32 0x%08x, cal crc32 0x%08x\n", crc32Org, crc32Cal);
            }
            else
            {
                count = 0;
                /* If section with correct crc32, start to parse fields followed */
                break;
            }
        }
    }
    
    if(count == SSU_DOWNLOAD_ATTEMPT_MAX)
    {
        result = LC_ERROR_INCORRECT_SECTION_CRC32;
        errCode = ERROR_CODE_INVALID_DII_CRC;
    }
    
    if((LC_SUCCESS == result) || (LC_ERROR_TIMEOUT == result) || (LC_ERROR_INCORRECT_SECTION_CRC32 == result))
    {
        LC_StopDemux();
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &diiTID);

        /* Analyse DII table */
        if(DII_TID != diiTID)
        {
            TRACE_LOG1(TRACE_ERROR, "  [DII] Wrong DII. Table ID 0x%02X\n", diiTID);

            result = LC_ERROR_WRONG_SECTION;
            errCode = ERROR_CODE_DII_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&diiSection, &bitPos, 16, &diiSectionLength);
        N2H16(&diiSectionLength);
        diiSectionLength &= 0x0FFF;
        result = MessageParser_ReadBits(&diiSection, &bitPos, 16, &tidExtension);
        N2H16(&tidExtension);
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &diiVersion);
        diiVersion = (diiVersion & 0x3E) >> 1;
       
        TRACE_LOG2(TRACE_DEBUG, "  [DII] diiSectionLen %d, diiVersion %d\n", diiSectionLength, diiVersion);

        if((lc_uint32)(diiSectionLength + 3) != sectionLength)
        {
            TRACE_LOG2(TRACE_ERROR, "  [DII] Invalid section length. diiSectionLength %d, sectionLength %d\n", 
                            diiSectionLength, sectionLength);

            result = LC_ERROR_WRONG_SECTION;
            errCode = ERROR_CODE_WRONG_DII_SECTION_SIZE;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &sectionNumber);
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &lastSectionNumber);
        /* section number & last section number should be 0 for DII */
        if((0 != sectionNumber) || (0 != lastSectionNumber))
        {
            result = LC_ERROR_WRONG_SECTION;
            errCode = ERROR_CODE_DII_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &protocolDiscrimitor);
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &dsmccType);
        /* Check protocolDiscrimitor and dsmccType in DownloadInfoIndication message */
        if((0x11 != protocolDiscrimitor) || (0x03 != dsmccType))
        {
            TRACE_LOG2(TRACE_ERROR, "  [DSI] Invalid protocolDiscrimitor or dsmccType. protocolDiscrimitor %02X, dsmccType %02X\n",
                            protocolDiscrimitor, dsmccType);

            result = LC_ERROR_WRONG_MESSAGE_ID;
            errCode = ERROR_CODE_DII_WRONG_MESSAGE_ID;
        }

    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&diiSection, &bitPos, 16, &messageId);
        N2H16(&messageId);

        TRACE_LOG1(TRACE_DEBUG, "  [DII] messageId 0x%04x\n", messageId);

        if(DII_MESSAGE_ID != messageId) /* 0x1002 */
        {
            result = LC_ERROR_WRONG_MESSAGE_ID;
            errCode = ERROR_CODE_DII_WRONG_MESSAGE_ID;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&diiSection, &bitPos, 32, &transactionId);
        N2H32(&transactionId);
        
        TRACE_LOG1(TRACE_DEBUG, "  [DII] transactionId 0x%08x\n", transactionId);

        if(transactionId != gDownloadGroup.groupId)
        {
            result = LC_ERROR_WRONG_TRANSACTION_ID;
            errCode = ERROR_CODE_DII_WRONG_TRANSACTION_ID;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &reservedByte);
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &adaptionLen);
        result = MessageParser_ReadBits(&diiSection, &bitPos, 16, &messageLen);
        N2H16(&messageLen);
               
        result = MessageParser_ReadBits(&diiSection, &bitPos, 32, &downloadId);
        N2H32(&downloadId);
        result = MessageParser_ReadBits(&diiSection, &bitPos, 16, &blockSize);
        N2H16(&blockSize);

        TRACE_LOG4(TRACE_DEBUG, "  [DII] adaptionLen %d, messageLen %d, downloadId 0x%08x, blockSize %d\n", 
                        adaptionLen, messageLen, downloadId, blockSize);

        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &windowSize);
        result = MessageParser_ReadBits(&diiSection, &bitPos, 8, &ackPeriod);
               
        result = MessageParser_ReadBits(&diiSection, &bitPos, 32, &tcDownloadWindow);
        N2H32(&tcDownloadWindow);
        result = MessageParser_ReadBits(&diiSection, &bitPos, 32, &tcDownloadScenario);
        N2H32(&tcDownloadScenario);

        TRACE_LOG4(TRACE_DEBUG, "  [DII] windowSize %d, ackPeriod %d, tcDownloadWindow %d, tcDownloadScenario %d\n",
                        windowSize, ackPeriod, tcDownloadWindow, tcDownloadScenario);
               
        /* compatibility descriptor */
        /* For DII, only length fields should be included by compatibilityDescriptor, and length should be 0 */
        ParseCompatibilityDescriptor(&diiSection, &bitPos);
               
        ParseDIIModuleLoop(&diiSection, &bitPos, blockSize);

        result = MessageParser_ReadBits(&diiSection, &bitPos, 16, &privateDataLength);
        N2H16(&privateDataLength);

        if(privateDataLength > 0)
        {
            ParseDIIPrivateDataByte(&diiSection, &bitPos);  /* todo */
        }
               
        TRACE_LOG1(TRACE_DEBUG, "  [DII] PrivateDataLength %d\n", privateDataLength);
    }

    ERR_REPORT_SetErrorCode(errCode);

    return result;
}

static lc_result LC_ProcessDDB(void)
{
    lc_uint16 i = 0;
    lc_uint32 j = 0;
    lc_uchar* pBuffer = LC_NULL;
    lc_uint16 ddbSectionLength = 0;
    lc_uchar ddbVersion = 0;
    lc_uchar ddbTID = 0;
    lc_uint16 tidExtension = 0;
    lc_uchar sectionNumber = 0;
    lc_uchar lastSectionNumber = 0;
    lc_uchar protocolDiscrimitor = 0;
    lc_uchar dsmccType = 0;
    lc_uint16 messageId = 0;
    lc_uint32 downloadId = 0;
    lc_uchar reservedByte = 0;
    lc_uchar adaptionLen = 0;
    lc_uint16 messageLen = 0;
    lc_uint16 blockNumber = 0;
    lc_uint16 blockSize = 0;
    lc_uint16 moduleId = 0;
    lc_uchar moduleVersion = 0;
    lc_uchar* pMem =LC_NULL;
    module_info_st* pModuleInfoStruct;
    ddb_info_st* pDDBInfoStruct;
    lc_uint16 filterExtension = 0;
    lc_uint16 maskExtension = 0xFFFF;
    lc_uint32 groupSize;
    lc_uint32 totalBlock = 0;
    lc_uint32 expectedTotalBlock = 0;
    lc_result result = LC_SUCCESS;
    lc_result result_timer = LC_SUCCESS;	
    lc_uint32 crc32Org = 0;
    lc_uint32 crc32Cal = 0;
    lc_buffer_st ddbSection = {LC_NULL, 0};
    lc_uint32 bytePos = 0;	
    lc_uint32 ddbMemSkip = 0;
    lc_uint16 count = 0;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uint32 sectionLength = 0;
    lc_filter_info filterInfo;

    lc_uint32 timerRefId = 0;
    lc_timer_info timerOpenData = {LC_NULL, 0, LC_FALSE , LC_NULL} ;

    LC_memset(&filterInfo, 0x0, sizeof(lc_filter_info));

    pModuleInfoStruct = gpModuleInfoStruct;
    TRACE_LOG1(TRACE_DEBUG, "BLOADER_ProcessDDB: gpModuleInfoStruct 0x%08x\n", gpModuleInfoStruct);

    for(i=0; i<gNumberOfModules; i++)
    {
        TRACE_LOG1(TRACE_INFO, "BLOADER_ProcessDDB: moduleId 0x%04x\n", pModuleInfoStruct->moduleId);
        filterExtension |= pModuleInfoStruct->moduleId;
        maskExtension &= pModuleInfoStruct->moduleId;
       
        pDDBInfoStruct = (ddb_info_st*)LC_MALLOC(sizeof(ddb_info_st) * pModuleInfoStruct->maxBlockNumber);
        
        if(LC_NULL != pDDBInfoStruct)
        {
            pModuleInfoStruct->pDDBInfoStruct = pDDBInfoStruct;

            for(j=0; j<pModuleInfoStruct->maxBlockNumber; j++)
            {
                pDDBInfoStruct->blockNumber = j;
                pDDBInfoStruct->blockSize = 0;
                pDDBInfoStruct->NumberReceived = 0;				
                pDDBInfoStruct->pBlockData = LC_NULL;
                pDDBInfoStruct ++;
            }

            expectedTotalBlock += pModuleInfoStruct->maxBlockNumber;
        }
        else
        {
            TRACE_LOG0(TRACE_FATAL, "  [DDB] lack of memory\n");
            result = LC_ERROR_INSUFFICIENT_BUFFER;
            break;
        }
        pModuleInfoStruct ++;
    }
    maskExtension |= ~filterExtension;

    if(LC_SUCCESS == result)
    {
        pModuleInfoStruct = gpModuleInfoStruct;
        TRACE_LOG2(TRACE_DEBUG, "BLOADER_ProcessDDB: filterExtension 0x%04x, maskExtension 0x%04x\n", filterExtension, maskExtension);

        filterInfo.match[0] = DDB_TID;
        filterInfo.match[1] = (filterExtension >> 8) & 0xFF;
        filterInfo.match[2] = (filterExtension) & 0xFF;
        filterInfo.match[3] = (gpModuleInfoStruct->moduleVersion << 1) | 0xC1;
        filterInfo.mask[0] = 0xFF;
        filterInfo.mask[1] = (maskExtension >> 8) & 0xFF;
        filterInfo.mask[2] = maskExtension & 0xFF;
        filterInfo.mask[3] = 0xFF;
        filterInfo.filterDepth = 4;

        TRACE_LOG4(TRACE_INFO, "BLOADER_ProcessDDB: match 0x%02x %02x %02x %02x\n", 
                        filterInfo.match[0], filterInfo.match[1], filterInfo.match[2], filterInfo.match[3]);
        TRACE_LOG4(TRACE_INFO, "BLOADER_ProcessDDB: mask 0x%02x %02x %02x %02x\n", 
                        filterInfo.mask[0], filterInfo.mask[1],filterInfo.mask[2], filterInfo.mask[3]);
    }

    if(LC_SUCCESS == result)
    {
        /*Set filter conditions.*/
        result = LC_SetFilter(&filterInfo);
    }

    if(LC_SUCCESS == result)
    {
        /*Start demux.*/
        result = LC_StartDemux();
    }

    groupSize = 0;

    timerOpenData.timeout = timeoutDownload;
    timerOpenData.isRepetitive = LC_TRUE;
    timerOpenData.timerContext = LC_NULL;
    timerOpenData.onTimeCallback = LC_TimerNotifyProc;

	if(LC_SUCCESS == result )
	{	
		result_timer = LoaderCoreSPI_Timer_Open(&timerRefId, &timerOpenData);	
	
     	if(LC_SUCCESS == result_timer )
     	{	
			result_timer = LoaderCoreSPI_Timer_Start(timerRefId);		
     	}
	}	
	
    if((LC_SUCCESS == result) && (LC_SUCCESS == result_timer ))
    {
        /* If lack of memory, stops receiving ddb. If other errors, discards the section and receive the next one */
        while( ( LC_FALSE == isTimeoutDownload) && ((groupSize < gDownloadGroup.groupSize) && ((LC_SUCCESS == result) || (LC_ERROR_INCORRECT_SECTION_CRC32 == result))))
        {
            /*Once the demux has started, we can call this function to get a section.*/
            if((LC_SUCCESS == result) || (LC_ERROR_INCORRECT_SECTION_CRC32 == result))
            {
                result = LC_ReadSection(&pBuffer,
                                    &sectionLength,
                                    SSU_DOWNLOAD_TIMEOUT);    /* if 0 is used as the timeout. This function will not return untile a section is got.*/
                if(LC_SUCCESS != result)
                {
                    errCode = ERROR_CODE_TABLE_TIMEOUT;
					result = LC_ERROR_TIMEOUT;
                    break;
                }
            }

            if(LC_SUCCESS == result)
            {
                ddbSection.bytes = pBuffer;
                ddbSection.length = sectionLength;
                crc32Cal = CRC_MPEG32(ddbSection.bytes, sectionLength - 4);
                crc32Org = LC_GetUint32(ddbSection.bytes, sectionLength - 4);
                if(crc32Cal != crc32Org)
                {
                    result = LC_ERROR_INCORRECT_SECTION_CRC32;
                    TRACE_LOG2(TRACE_ERROR, "BLOADER_ProcessDDB: org crc32 0x%08x, cal crc32 0x%08x\n", crc32Org, crc32Cal);
                }
            }


            bytePos = 0;
			
            if(LC_SUCCESS == result)
            {
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &ddbTID);
                if(DDB_TID != ddbTID)
                {
                    TRACE_LOG1(TRACE_ERROR, "  [DDB] Wrong DDB. Table ID 0x%02X\n", ddbTID);
                    result = LC_ERROR_WRONG_SECTION;
                    errCode = ERROR_CODE_DDB_WRONG_SECTION;
                }
            }
        
            /* Analyse DDB table */
            if(LC_SUCCESS == result)
            {
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 2, &ddbSectionLength);
                N2H16(&ddbSectionLength);
                ddbSectionLength &= 0x0FFF;
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 2, &tidExtension);
                N2H16(&tidExtension);
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &ddbVersion);
                ddbVersion = (ddbVersion & 0x3E) >> 1;
            
                TRACE_LOG2(TRACE_DEBUG, "  [DDB] ddbSectionLength %d, ddbVersion %d\n", ddbSectionLength, ddbVersion);
            
                if((lc_uint32)(ddbSectionLength + 3) != sectionLength)
                {
                    TRACE_LOG2(TRACE_ERROR, "  [DDB] Invalid section length. ddbSectionLength %d, sectionLength %d\n", 
                                    ddbSectionLength, sectionLength);
                    result = LC_ERROR_WRONG_SECTION;
                    errCode = ERROR_CODE_WRONG_DDB_SECTION_SIZE;
                }
            }

            if(LC_SUCCESS == result)
            {
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &sectionNumber);                
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &lastSectionNumber);                         
                if(sectionNumber > lastSectionNumber)
                {
                    result = LC_ERROR_WRONG_SECTION;
                    errCode = ERROR_CODE_DDB_WRONG_SECTION;
                }
            }
             
            if(LC_SUCCESS == result)
            {
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &protocolDiscrimitor);                             
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &dsmccType);     
                /* Check protocolDiscrimitor and dsmccType in DownloadServerInitiate message */
                if((0x11 != protocolDiscrimitor) || (0x03 != dsmccType))
                {
                    TRACE_LOG2(TRACE_ERROR, "  [DDB] Invalid protocolDiscrimitor or dsmccType. protocolDiscrimitor %02X, dsmccType %02X\n",
                                    protocolDiscrimitor, dsmccType);
                
                    result = LC_ERROR_WRONG_MESSAGE_ID;
                    errCode = ERROR_CODE_DDB_WRONG_MESSAGE_ID;
                }
            }

            if(LC_SUCCESS == result)
            {
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 2, &messageId);
                N2H16(&messageId);

                if(DDB_MESSAGE_ID != messageId) /* 0x1003 */
                {
                    result = LC_ERROR_WRONG_MESSAGE_ID;
                    errCode = ERROR_CODE_DDB_WRONG_MESSAGE_ID;
                }
            }
        
            if(LC_SUCCESS == result)
            {
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 4, &downloadId);
                N2H32(&downloadId);
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &reservedByte);                
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &adaptionLen);                
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 2, &messageLen);
                N2H16(&messageLen);
            
                TRACE_LOG4(TRACE_DEBUG, "  [DDB] messageId 0x%04x, downloadId 0x%08x, adaptionLen %d, messageLen %d\n",
                                messageId, downloadId, adaptionLen, messageLen);
                   
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 2, &moduleId);                
                N2H16(&moduleId);
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &moduleVersion);                       
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 1, &reservedByte);                     

                TRACE_LOG2(TRACE_DEBUG, "  [DDB] moduleId 0x%04x, moduleVersion %d\n", moduleId, moduleVersion);
                pModuleInfoStruct = LC_NULL;
                ddbMemSkip = 0;
                for(i=0; i<gNumberOfModules; i++)
                {
                    if(moduleId == (gpModuleInfoStruct + i)->moduleId)
                    {
                        pModuleInfoStruct = gpModuleInfoStruct + i;
                        break;
                    }
                    ddbMemSkip += (gpModuleInfoStruct + i)->moduleSize;
                }
				
                if( (LC_SUCCESS == result) && (i == gNumberOfModules) )
                {
                    result = LC_ERROR_WRONG_MODULE_ID;
                    errCode = ERROR_CODE_DDB_WRONG_MODULE_ID;
                }

                if( (LC_SUCCESS == result) && (LC_NULL == pModuleInfoStruct) )
                {
                    result = LC_ERROR_MISSING_DATA;
                }
				
            }

            if(LC_SUCCESS == result)
            {
                TRACE_LOG2(TRACE_DEBUG, "  [DDB] moduleVersion %d, expected moduleVersion %d\n", 
                                moduleVersion, pModuleInfoStruct->moduleVersion);

                if(moduleVersion != pModuleInfoStruct->moduleVersion)
                {
                    result = LC_ERROR_DDB_WRONG_MODULE_VERSION;
                    errCode = ERROR_CODE_DDB_WRONG_MODULE_VERSION;
                }
            }

            if(LC_SUCCESS == result)
            {
                result = MessageParser_ReadBytes(&ddbSection, &bytePos, 2, &blockNumber);                    
                N2H16(&blockNumber);

                blockSize = (lc_uint16)(ddbSectionLength - bytePos - 4 + 3); 
            
                TRACE_LOG2(TRACE_DEBUG, "  [DDB] blockNumber %d, blockSize %d\n", blockNumber, blockSize);

                pDDBInfoStruct = pModuleInfoStruct->pDDBInfoStruct + blockNumber;
                if((LC_NULL != pDDBInfoStruct->pBlockData) && (blockNumber == pDDBInfoStruct->blockNumber))
                {
                    pDDBInfoStruct->NumberReceived++;
                    TRACE_LOG2(TRACE_INFO, "\n&[DDB] pDDBInfoStruct->blockNumber %d, Received Num %d\n", pDDBInfoStruct->blockNumber, pDDBInfoStruct->NumberReceived);
                
                    /*if(pDDBInfoStruct->NumberReceived > SSU_DOWNLOAD_ATTEMPT_MAX)
                    {
                        TRACE_LOG2(TRACE_INFO, "\n&[DDB]  the pDDBInfoStruct->blockNumber %d has Received %d times \n", pDDBInfoStruct->blockNumber, pDDBInfoStruct->NumberReceived);
                        result = LC_ERROR_TIMEOUT;
                        errCode = ERROR_CODE_TABLE_TIMEOUT;
                    }*/
                }
                if((LC_NULL == pDDBInfoStruct->pBlockData) && (blockNumber == pDDBInfoStruct->blockNumber) && (LC_SUCCESS == result))
                {   /* new block data. If the block data has beed received, will not save again */
                
                    /* For those who can malloc big memory at once, just as loader core currently do */
                    /* Big memory must be needed for decompress operation for the whole module */
                    pMem = gSSUDataBuffer.bytes + ddbMemSkip + blockNumber * pModuleInfoStruct->generalBlockSize;
                    TRACE_LOG1(TRACE_INFO, "\n&[DDB] Received pDDBInfoStruct->blockNumber %d\n", pDDBInfoStruct->blockNumber);
                                
                    if(LC_NULL != pMem)
                    {
                        LC_memcpy(pMem, ddbSection.bytes + bytePos, blockSize);                        
                        pDDBInfoStruct->blockSize = blockSize;
                        pDDBInfoStruct->pBlockData = pMem;

                        /* Memory handling */
                        pModuleInfoStruct->receivedBlockNumber ++;
                        groupSize += blockSize;
                        totalBlock ++;
                        pDDBInfoStruct->NumberReceived++;
                        TRACE_LOG2(TRACE_INFO, "&[DDB] totalBlock %d, groupSize 0x%08x\n", totalBlock, groupSize);
                    }
                    else /* reserved for those who want to malloc memory block by block */
                    {
                        TRACE_LOG0(TRACE_FATAL, "  [DDB] lack of memory\n");
                        result = LC_ERROR_INSUFFICIENT_BUFFER;
                    }
                }
            }
        }
    }

	if(LC_SUCCESS == result_timer )
	{	
		result_timer = LoaderCoreSPI_Timer_Stop(timerRefId);	
	
     	if(LC_SUCCESS == result_timer )
     	{	
     		result_timer = LoaderCoreSPI_Timer_Close(timerRefId);		
     	}
	}
	
	if(LC_SUCCESS != result_timer )
	{
		result = result_timer;
	}

    if((LC_SUCCESS == result) || (LC_ERROR_TIMEOUT == result))
    {
        LC_StopDemux();
    }

    if(LC_TRUE == isTimeoutDownload)
    {
        isTimeoutDownload = LC_FALSE;
        errCode = ERROR_CODE_TABLE_TIMEOUT;
        result = LC_ERROR_TIMEOUT;
    }

    ERR_REPORT_SetErrorCode(errCode);

    TRACE_LOG2(TRACE_INFO, "[DDB]: total blocks %d, expected total block %d\n", totalBlock, expectedTotalBlock);
   
    return  result;
}

lc_result LC_SetupCarousel(nim_setup func)
{

    lc_result result = LC_SUCCESS;
    lc_channel_info channelInfo;
    lc_dvbssu_dl_info_st dvbssuParameters;
    lc_uchar privateInfo[LC_MANUFACTURER_PRIVATE_INFO_LENGTH];


    /* Global variables Initialization. */
    gpModuleInfoStruct = LC_NULL;
    gNumberOfModules = 0;
    LC_memset(&gDownloadGroup, 0, sizeof(gDownloadGroup));
    LC_memset(&gSSUDataBuffer, 0, sizeof(gSSUDataBuffer));

    /* Get and check DVB-SSU download parameters from Loader Partition. */
    if (LC_SUCCESS == result)
    {
        result = LC_UtilGetDvbssuDownloadParameters(&dvbssuParameters, privateInfo);
    }

    if (LC_SUCCESS == result)
    {
        result = LC_VerifyDVBSSUParameters(&dvbssuParameters);
        if( LC_SUCCESS != result ) /* both of them are corrupted. */
        {
            ERR_REPORT_SetErrorCode(ERROR_CODE_INVALID_OTA_PARA);
        }
    }
    if(func)
    {
       func(privateInfo,dvbssuParameters.pid);
    }

    /* Init variables. */
    if (LC_SUCCESS == result)
    {
        LC_memset(&channelInfo, 0x0, sizeof(channelInfo));
        channelInfo.channelType = LC_CHANNEL_TYPE_DVB;
        channelInfo.channel.dvbChannel.pid = dvbssuParameters.pid;
        LC_memcpy(channelInfo.manufacturerPrivateInfo, privateInfo, LC_MANUFACTURER_PRIVATE_INFO_LENGTH);
    }

    /* Enable demux. We will send PID/IP/port to demux. */
    if(LC_SUCCESS == result)
    {
        result = LC_OpenDemux(&channelInfo);
    }

    if(LC_SUCCESS != result)
    {
        TRACE_LOG0(TRACE_ERROR, "[BLOADER] Carousel init failed.\n");
    }
    else
    {
        TRACE_LOG0(TRACE_INFO, "[BLOADER] Carousel init ok.\n");
    }

    return result;
}


lc_result LC_ProcessCarousel(void)
{
    /* These codes reserved for those who wants to malloc memory block by block 
     * because some OS may refuse malloc big memory at once.
     * Unfortunately, big memory must be needed for decompress operation for the whole module. 
     */
    lc_result result = LC_SUCCESS;
    lc_sint32 i = 0;
    module_info_st* pModuleInfoStruct = LC_NULL;
    ddb_info_st* pDDBInfoStruct = LC_NULL;

    /* DSI */
    if(LC_SUCCESS == result)
    {
        LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_DOWNLOAD_DSI);
        TRACE_LOG0(TRACE_INFO, "#[CAROUSEL] Loader V5 DSI parsing ...\n");

        LC_LedDisplay(LED_CHAR_NONE, CHAR_H, CHAR_BLNK, CHAR_BLNK );

        result = LC_ProcessDSI();
    }

    if(LC_SUCCESS == result)
    {
        if((0 == gDownloadGroup.groupId) || (0 == gDownloadGroup.groupSize))
        {
            result = LC_ERROR_MISSING_DATA;
            ERR_REPORT_SetErrorCode(ERROR_CODE_NO_VALID_DOWNLOAD_IN_COMP_DESC);
        }
    }

    /* DII */
    if(LC_SUCCESS == result)
    {
        LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_DOWNLOAD_DII);
        TRACE_LOG0(TRACE_INFO, "#[CAROUSEL] Loader V5 DII parsing ...\n");
        result = LC_ProcessDII();
    }

    if(LC_SUCCESS == result)
    {
        if(LC_NULL == gpModuleInfoStruct)
        {
            result = LC_ERROR_MISSING_DATA;
        }
    }

    if(LC_SUCCESS == result)
    {
        TRACE_LOG0(TRACE_INFO, "#[CAROUSEL] Loader V5 DDB parsing ...\n");
        
        gSSUDataBuffer.bytes = (lc_uchar *)LC_MALLOC(gDownloadGroup.groupSize);
        if(LC_NULL == gSSUDataBuffer.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }

    }

    /* DDB */
    if(LC_SUCCESS == result)
    {
        LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_DOWNLOAD_DDB);
        LC_LedDisplay(LED_CHAR_NONE, CHAR_D, CHAR_BLNK, CHAR_BLNK );
        result = LC_ProcessDDB();
    }

    /* These codes reserved for those who wants to malloc memory block by block 
     * because some OS may refuse malloc big memory at once.
     * Unfortunately, big memory must be needed for decompress operation for the whole module. 
     */
    if(LC_SUCCESS == result)
    {
        pModuleInfoStruct = gpModuleInfoStruct;
        if(LC_NULL != pModuleInfoStruct)
        {
            for(i=0; i<gNumberOfModules; i++)
            {
                if(LC_NULL != pModuleInfoStruct->pDDBInfoStruct)
                {
                    pDDBInfoStruct = pModuleInfoStruct->pDDBInfoStruct;

                    if(LC_NULL != pModuleInfoStruct->pDDBInfoStruct)
                    {
                        LC_Free_Memory((void **)&pModuleInfoStruct->pDDBInfoStruct);
                    }
                }
                pModuleInfoStruct ++;
            }
            TRACE_LOG2(TRACE_DEBUG, "Free %d modules for group 0x%08x\n", i, gDownloadGroup.groupId);
            if(LC_NULL != gpModuleInfoStruct)
            {
                LC_Free_Memory((void **)&gpModuleInfoStruct);
            }
        }
    }

    return  result;
}


lc_result LC_FinalizeCarousel(void)
{
    lc_result result = LC_SUCCESS;
    
    LC_Free_Memory((void **)&gSSUDataBuffer.bytes);

    return result;
}


lc_result 
LC_AcquireUpgradeDataFromSSUStream(
    lc_uart_packet_type dataId,
    lc_buffer_st* pBytes)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_buffer_st bytes = {LC_NULL, 0};
    lc_serial_download_packet serialData;

    bytes.bytes = gSSUDataBuffer.bytes;
    bytes.length = gDownloadGroup.groupSize;

    LC_memset(&serialData, 0, sizeof(lc_serial_download_packet));

    if (LC_SUCCESS == result)
    {
       result = MessageParser_ParseSDPSerialDownloadPacketBytes(&bytes, &gSSUDataBuffer.length, &serialData);        

        /* Check data ID. */
        if( serialData.data_id != dataId )
        {
            result = LC_FAILURE;
            
            switch (dataId)
            {
                case UART_DLH_ID: /* Download Header */
                    TRACE_LOG0(TRACE_ERROR, "[BLOADER] Error: Download Header data_id error!\n");
                    errCode = ERROR_CODE_INVALID_DLH_ID;
                    break;

                case UART_MH_ID: /* Module Header */
                    TRACE_LOG0(TRACE_ERROR, "[BLOADER] ERROR: Module Header data_id error.\n");
                    errCode = ERROR_CODE_INVALID_MH_ID;
                    break;

                case UART_DG_ID: /* Datagram */
                    TRACE_LOG0(TRACE_ERROR, "[BLOADER] ERROR: Datagram data_id error.\n");
                    errCode = ERROR_CODE_INVALID_DG_ID;
                    break;
            }
        }
        /* Check length. */
        else if( serialData.length == 0 )
        {
            result = LC_FAILURE;
            
            switch (dataId)
            {
                case UART_DLH_ID: /* Download Header */
                    TRACE_LOG0(TRACE_DEBUG, "[BLOADER] ERROR: DLH length error.\n");
                    errCode = ERROR_CODE_INVALID_DLH_SIZE;
                    break;

                case UART_MH_ID: /* Module Header */
                    TRACE_LOG0(TRACE_DEBUG, "[BLOADER] ERROR: PH length error.\n");
                    errCode = ERROR_CODE_INVALID_MH_SIZE;
                    break;

                case UART_DG_ID: /* Datagram */
                    TRACE_LOG0(TRACE_DEBUG, "[BLOADER] ERROR: DG length error.\n");
                    errCode = ERROR_CODE_DATAGRAM_SIZE;
                    break;
            }
        }
    }

    if (LC_SUCCESS == result)
    {
        LC_ASSERT(dataId == serialData.data_id);
        
        LC_memcpy(pBytes->bytes, serialData.payload, serialData.length);
        pBytes->length = serialData.length;

        gSSUDataBuffer.length +=  pBytes->length;
    }

    return result;
}    

lc_result 
LC_GetSSUStreamData(lc_buffer_st* pBytes)
{
    pBytes->bytes = gSSUDataBuffer.bytes;
    pBytes->length = gSSUDataBuffer.length;
}



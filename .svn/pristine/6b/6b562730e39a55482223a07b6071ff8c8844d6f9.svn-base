
/*
 * This file provides SSU download location code for HighLevel.
 */

#include "LoaderCoreAPI_ApplicationHelper.h"
#include "LoaderCorePrivate.h"
#include "IrdEmm.h"


#define  SERVICE_TYPE_DATA_BROADCAST_SERVICE  0xC

#define  INVALID_SERVICE_ID  0xFFFF
#define  INVALID_PID  0x1FFF

#define BOUQUET_ID_FOR_LOADER_V5 (0xFF00)


/*
 * Selector byte definition:
 * Manufacturer_ID  16 bits
 * Hardware_Vesion  16 bits
 * Reserved         16 bits
 * Software Model (Variant)  16 bits
 * Sub Software Model (Sub Variant)  16 bits
 * Software Version (Download Sequence Number) 16 bits
 * Trigger Control Byte  8 bits
 * Download Mode         8 bits
 */
#define  SELECTOR_BYTE_LENGTH  14

typedef struct _lc_si_catche_memory
{
    lc_uchar triggerControlMode;
    lc_uchar downloadMode;
    lc_bool nitMatch;   /* if find valid linkage_descriptor in NIT or BAT */
    lc_bool pmtMatch;   /* if find valid data_broadcast_id_descriptor in PMT  */
    lc_uint16 serviceId;
    lc_uchar privateData[LC_MANUFACTURER_PRIVATE_INFO_LENGTH];
    lc_uint16 transportStreamId;
    lc_uint16 originalNetworkId;
    lc_bool networkMatch;
    
} lc_si_catche_memory;

typedef struct _lc_selector_byte
{
    lc_uint16 manufacturerId;
    lc_uint16 hardwareVersion;
    lc_uint16 reserved;
    lc_uint16 variant;
    lc_uint16 subVariant;
    lc_uint16 softwareVersion;
    lc_uchar triggerControlByte;
    lc_uchar downloadMode;
    
} lc_selector_byte;


typedef struct _lc_bat_section
{
    lc_uchar tableId;
    lc_uint16 sectionLength;
    lc_uint16 bouquetId;
    lc_uchar version;
    lc_uchar sectionNumber;
    lc_uchar lastSectionNumber;
    lc_uint16 bouquetDescLength;
    lc_uint16 transportStreamLoopLength;
    lc_uint16 transportStreamId;
    lc_uint16 originalNetworkId;
    lc_uint16 transportDescLength;
    
} lc_bat_section;

/*
 * triggerControlMode: default 0x00, all disabled
 * downloadMode: default 0x00, force download
 * nitMatch: default LC_FALSE
 * pmtMatch: default LC_FALSE
 * serviceId: default 0xFFFF
 * pmtPID: default 0x1FFF
 * manufacturer private data: filled with ZERO
 * transportStreamId: default 0x00
 * originalNetworkId: default 0x00
 * networkMatch: default LC_FALSE
 */
static lc_si_catche_memory gDownloadInfo = 
{
    0x00, 0x00, 
    LC_FALSE, LC_FALSE, /*LC_FALSE,*/ 
    INVALID_SERVICE_ID, 
    {0},
    0,
    0,
    LC_FALSE
};

/* Get manufacturer information */
static void GetOUI(lc_uchar *pOUI)
{
    lc_result result = LC_SUCCESS;
    lc_bbcb_st bbcb;
    lc_bool checksum = LC_FALSE;

    LC_memset(&bbcb, 0, sizeof(lc_bbcb_st));

    result = BBCB_GetBBCB(&bbcb, &checksum);
    if (LC_SUCCESS == result)
    {
        LC_memcpy(pOUI, bbcb.OUI, 3);
    }
}

static lc_uint16 GetManufacturerCode(void)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 manufacturerId = 0;
    lc_bbcb_st bbcb;
    lc_bool checksum = LC_FALSE;

    LC_memset(&bbcb, 0, sizeof(lc_bbcb_st));

    result = BBCB_GetBBCB(&bbcb, &checksum);
    if (LC_SUCCESS == result)
    {
        manufacturerId = bbcb.manufacturer_id;
    }
    
    return  manufacturerId;
}

static lc_uint16 GetHardwareVersion(void)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 hardwareVer = 0;
    lc_bbcb_st bbcb;
    lc_bool checksum = LC_FALSE;

    LC_memset(&bbcb, 0, sizeof(lc_bbcb_st));

    result = BBCB_GetBBCB(&bbcb, &checksum);
    if (LC_SUCCESS == result)
    {
        hardwareVer = bbcb.hardware_version;
    }
    
    return  hardwareVer;
}


/* Parse descriptors for PSI */

static lc_result HL_ParseSelectorByte(const lc_buffer_st *pData, lc_uint32 *pBitPos, lc_uint16 length, lc_bool *pMatch)
{
    lc_result result = LC_SUCCESS;
    lc_selector_byte selectorByte;
    lc_uint16 deviceManufacturerId = 0;
    lc_uint16 deviceHardwareVersion = 0;
    lc_uint16 deviceVariant = 0xFFFF;
    lc_uint16 deviceSubVariant = 0xFFFF;
    lc_uint16 deviceDownloadSequence = 0;
    lc_bool migration = LC_FALSE;
    

    LC_memset(&selectorByte, 0, sizeof(lc_selector_byte));

    if(SELECTOR_BYTE_LENGTH == length)
    {
        gDownloadInfo.triggerControlMode = 0x00;
        gDownloadInfo.downloadMode = 0x00;
                
        result = MessageParser_ReadBits(pData, pBitPos, 16, &selectorByte.manufacturerId);
        N2H16(&selectorByte.manufacturerId);
        result = MessageParser_ReadBits(pData, pBitPos, 16, &selectorByte.hardwareVersion);
        N2H16(&selectorByte.hardwareVersion);
        result = MessageParser_ReadBits(pData, pBitPos, 16, &selectorByte.reserved);
        N2H16(&selectorByte.reserved);
        result = MessageParser_ReadBits(pData, pBitPos, 16, &selectorByte.variant);
        N2H16(&selectorByte.variant);
        result = MessageParser_ReadBits(pData, pBitPos, 16, &selectorByte.subVariant);
        N2H16(&selectorByte.subVariant);
        result = MessageParser_ReadBits(pData, pBitPos, 16, &selectorByte.softwareVersion);
        N2H16(&selectorByte.softwareVersion);
        result = MessageParser_ReadBits(pData, pBitPos, 8, &selectorByte.triggerControlByte);
        result = MessageParser_ReadBits(pData, pBitPos, 8, &selectorByte.downloadMode);

        TRACE_LOG4(TRACE_INFO, "Selector bytes:  manuId 0x%04x, hwVer 0x%04x, var 0x%04x, subVar 0x%04x\n",
            selectorByte.manufacturerId, 
            selectorByte.hardwareVersion, 
            selectorByte.variant, 
            selectorByte.subVariant);
        TRACE_LOG3(TRACE_INFO, "Selector bytes:  softwareVersion 0x%04x, triggerControlMode 0x%02x, downloadMode 0x%02x\n",
            selectorByte.softwareVersion, 
            selectorByte.triggerControlByte, 
            selectorByte.downloadMode);

        if (LC_SUCCESS == result)
        {
            result = IRDEMM_GetMigrationVariant(&deviceVariant, &deviceSubVariant);
            if (LC_SUCCESS == result)
            {
                if (LC_TRUE == LC_IsVariantValid(&deviceVariant, &deviceSubVariant))
                {
                    migration = LC_TRUE;
                }
            }
        }
        
        if (LC_SUCCESS == result)
        {
            if (LC_TRUE != migration)
            {
                result = LC_GetVariant(&deviceVariant, &deviceSubVariant);
            }
        }
        
        if (LC_SUCCESS == result)
        {
            deviceManufacturerId = GetManufacturerCode();
            deviceHardwareVersion = GetHardwareVersion();
            TRACE_LOG4(TRACE_INFO, "Device info: manuId 0x%04x, hwVer 0x%04x, var 0x%04x, subVar 0x%04x\n", 
                deviceManufacturerId, deviceHardwareVersion, deviceVariant, deviceSubVariant);
        }

        if (LC_SUCCESS == result)
        {
            if(LC_TRUE != migration)
            {
                result = LC_GetDownloadSequence(&deviceDownloadSequence);
                if (LC_SUCCESS == result)
                {
                    result = LC_CheckDownloadSequence(selectorByte.softwareVersion, deviceDownloadSequence);
                }
            }
        }

        if (LC_SUCCESS == result)
        {
            if( (deviceManufacturerId != selectorByte.manufacturerId) || 
                (deviceHardwareVersion != selectorByte.hardwareVersion))
            {
                result = LC_FAILURE;
            }
        }

        if (LC_SUCCESS == result)
        {
            if(LC_TRUE != migration)
            {
                if( (LC_TRUE != LC_CheckVariant(LC_FALSE, selectorByte.variant, deviceVariant)) || 
                    (LC_TRUE != LC_CheckVariant(LC_TRUE, selectorByte.subVariant, deviceSubVariant)))

                {
                    result = LC_FAILURE;
                }
            }
            else
            {
                if( (selectorByte.variant != deviceVariant) || 
                    (selectorByte.subVariant != deviceSubVariant) )

                {
                    result = LC_FAILURE;
                }
            }
        }

        if (LC_SUCCESS == result)
        {
            /* Update triggerControlMode anad downloadMode. */
            gDownloadInfo.triggerControlMode = selectorByte.triggerControlByte;
            gDownloadInfo.downloadMode = selectorByte.downloadMode;
                
            *pMatch = LC_TRUE;

            if (LC_TRUE == migration)
            {
                IRDEMM_SetMigrationVariant(0xFFFF, 0xFFFF);
            }

            TRACE_LOG0(TRACE_INFO, "MATCHED Selector bytes!\n");
        }
    }

    return result;
}

static lc_result HL_ParseServiceListDescriptor(const lc_buffer_st *pData, lc_uint32 *pBitPos, lc_uchar descLength)
{
    lc_result result = LC_SUCCESS;
    lc_uchar skipLength = 0;
    lc_uint16 serviceId = INVALID_SERVICE_ID;
    lc_uchar serviceType = 0;

    
    while(skipLength < descLength)
    {
        result = MessageParser_ReadBits(pData, pBitPos, 16, &serviceId);
        N2H16(&serviceId);
        result = MessageParser_ReadBits(pData, pBitPos, 8, &serviceType);
        TRACE_LOG2(TRACE_INFO, "  service list descriptor: serviceId 0x%04x, serviceType 0x%02x\n", serviceId, serviceType);
        if(SERVICE_TYPE_DATA_BROADCAST_SERVICE == serviceType)
        {
            /* gDownloadInfo.serviceId = serviceId; */ /* uses the service id in linkage descriptor */
        }
        skipLength += 3;
    }

    return result;
}

static lc_result HL_ParseLinkageDescriptor(const lc_buffer_st *pData, lc_uint32 *pBitPos)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 transportId = 0;
    lc_uint16 originalNetworkId= 0;
    lc_uint16 serviceId = INVALID_SERVICE_ID;
    lc_uchar linkageType = 0;
    lc_uchar ouiDataLength = 0;
    lc_uchar oui[3];
    lc_uchar deviceOui[3];
    lc_uchar selectorLength = 0;
    lc_uchar privateDataLength = 0;
    lc_bool bMatchedSTB = LC_FALSE;


    LC_memset(&oui, 0, sizeof(oui));
    GetOUI(deviceOui);
    
    result = MessageParser_ReadBits(pData, pBitPos, 16, &transportId);
    N2H16(&transportId);
    result = MessageParser_ReadBits(pData, pBitPos, 16, &originalNetworkId);
    N2H16(&originalNetworkId);
    result = MessageParser_ReadBits(pData, pBitPos, 16, &serviceId);
    N2H16(&serviceId);
    result = MessageParser_ReadBits(pData, pBitPos, 8, &linkageType);
    
    if(linkageType == 0x09) /* system software update service */
    {
        result = MessageParser_ReadBits(pData, pBitPos, 8, &ouiDataLength);
        result = MessageParser_ReadBits(pData, pBitPos, 24, &oui);
        result = MessageParser_ReadBits(pData, pBitPos, 8, &selectorLength);

        if(selectorLength > 0)
        {
            result = HL_ParseSelectorByte(pData, pBitPos, selectorLength, &bMatchedSTB);
            if((LC_SUCCESS == result) && (LC_TRUE == bMatchedSTB) && (0 == LC_memcmp(oui, deviceOui, 3)))
            {
                gDownloadInfo.nitMatch = LC_TRUE;
                gDownloadInfo.serviceId = serviceId;
                gDownloadInfo.transportStreamId = transportId;
                gDownloadInfo.originalNetworkId = originalNetworkId;
            }
        }
        privateDataLength = ouiDataLength - (4 + selectorLength);
        if(privateDataLength > 0)
        {
            /* parsePrivateData(pSkip); */    /* todo */
        }
    }

    return result;
}

/* ETSI TS 102 006, page 13, data broadcast id descriptor with data_broadcast_id is 0x000A */
static lc_result HL_ParseDataBroadcastIdDescriptor(const lc_buffer_st *pData, lc_uint32 *pBitPos)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 dataBroadcastId = 0;
    lc_uchar ouiDataLength = 0;
    lc_uchar oui[3];
    lc_uchar deviceOui[3];
    lc_uchar updateByte = 0;
    lc_uchar versionInfo = 0;
    lc_uchar updateVersionFlag = 0;
    lc_uchar updateVersion = 0;
    lc_uchar selectorLength = 0;
    lc_uchar privateDataLength = 0;
    lc_bool bMatched = LC_FALSE;

    LC_memset(&oui, 0, sizeof(oui));
    LC_memset(&deviceOui, 0, sizeof(deviceOui));
    
    result = MessageParser_ReadBits(pData, pBitPos, 16, &dataBroadcastId);
    N2H16(&dataBroadcastId);
    
    if(dataBroadcastId == 0x000A)
    {
        result = MessageParser_ReadBits(pData, pBitPos, 8, &ouiDataLength);
        result = MessageParser_ReadBits(pData, pBitPos, 24, &oui);

        TRACE_LOG3(TRACE_INFO, "PMT data broadcast id descriptor: OUI 0x%02x%02x%02x\n", oui[0], oui[1], oui[2]);

        result = MessageParser_ReadBits(pData, pBitPos, 8, &updateByte);
        updateByte &= 0x0F;
        result = MessageParser_ReadBits(pData, pBitPos, 8, &versionInfo);
        updateVersionFlag = (versionInfo >> 5) & 0x01;
        updateVersion = versionInfo & 0x1F;
        result = MessageParser_ReadBits(pData, pBitPos, 8, &selectorLength);

        TRACE_LOG3(TRACE_INFO, "PMT data broadcast id descriptor: updateByte 0x%02x, updateVersionFlag %d, updateVersion %02x\n", updateByte, updateVersionFlag, updateVersion);
        /* updateByte should be 1 */
        if(selectorLength > 0)
        {
            /* optional. Currently no selector bytes in DataBroadcastIdDescriptor */
            result = HL_ParseSelectorByte(pData, pBitPos, selectorLength, &bMatched);            
        }

        privateDataLength = ouiDataLength - (6 + selectorLength);
        if(privateDataLength > 0)
        {
            /* HL_ParsePrivateDataByte(); */
        }

        GetOUI(deviceOui);
        if(LC_memcmp(oui, deviceOui, 3) == 0)
        {
            gDownloadInfo.pmtMatch = LC_TRUE;
        }
    }

    return result;
}

static lc_result HL_ParseDescriptor(const lc_buffer_st *pData, lc_uint32 *pBitPos, lc_uint16 length)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 skipLength = 0;
    lc_uchar descTag = 0;
    lc_uchar descLength = 0;
    lc_uchar network_name[256];
    lc_uchar bouquet_name[256];
    lc_uchar privateData[LC_MANUFACTURER_PRIVATE_INFO_LENGTH];

    LC_memset(&network_name, 0, sizeof(network_name));
    LC_memset(&bouquet_name, 0, sizeof(bouquet_name));
    
    
    while(skipLength < length)
    {
        result = MessageParser_ReadBits(pData, pBitPos, 8, &descTag);
        result = MessageParser_ReadBits(pData, pBitPos, 8, &descLength);
        TRACE_LOG2(TRACE_INFO, "HL_ParseDescriptor: descTag 0x%02x, length %d\n", descTag, descLength);
        switch(descTag)
        {
            case 0x40:  /* network_name_descriptor */
                TRACE_LOG0(TRACE_INFO, "  network_name_descriptor:");
                result = MessageParser_ReadBits(pData, pBitPos, descLength * 8, &network_name);
                network_name[descLength] = '\0';
                TRACE_LOG1(TRACE_INFO, "    network name %s\n", network_name);
                break;
            case 0x41:  /* service_list_descriptor */
                TRACE_LOG0(TRACE_INFO, "  service_list_descriptor\n");
                result = HL_ParseServiceListDescriptor(pData, pBitPos, descLength);
                break;
            case 0x43:  /* satellite_delivery_system_descriptor */
                TRACE_LOG0(TRACE_INFO, "  satellite_delivery_system_descriptor\n");
                result = MessageParser_ReadBits(pData, pBitPos, descLength * 8, privateData);
                if(LC_TRUE == gDownloadInfo.networkMatch)
                {
                    LC_memcpy(gDownloadInfo.privateData, privateData, LC_MANUFACTURER_PRIVATE_INFO_LENGTH);
                }
                break;
            case 0x44:  /* cable_delivery_system_descriptor */
                TRACE_LOG0(TRACE_INFO, "  cable_delivery_system_descriptor\n");
                result = MessageParser_ReadBits(pData, pBitPos, descLength * 8, privateData);
                if(LC_TRUE == gDownloadInfo.networkMatch)
                {
                    LC_memcpy(gDownloadInfo.privateData, privateData, LC_MANUFACTURER_PRIVATE_INFO_LENGTH);
                }
                break;
            case 0x47:
                TRACE_LOG0(TRACE_INFO, "  bouquet name descriptor:");
                result = MessageParser_ReadBits(pData, pBitPos, descLength * 8, &bouquet_name);
                bouquet_name[descLength] = '\0';
                TRACE_LOG1(TRACE_INFO, "    bouquet name %s\n", bouquet_name);
                break;
            case 0x4A:  /* linkage_descriptor. HERE !!! */
                TRACE_LOG0(TRACE_INFO, "  linkage_descriptor\n");
                result = HL_ParseLinkageDescriptor(pData, pBitPos);
                break;
            case 0x5A:  /* terrestrial_delivery_system_descriptor */
                TRACE_LOG0(TRACE_INFO, "  terrestrial_delivery_system_descriptor\n");
                result = MessageParser_ReadBits(pData, pBitPos, descLength * 8, privateData);
                if(LC_TRUE == gDownloadInfo.networkMatch)
                {
                    LC_memcpy(gDownloadInfo.privateData, privateData, LC_MANUFACTURER_PRIVATE_INFO_LENGTH);
                }
                break;
            case 0x5F:  /* private_data_specifier_descriptor */
                TRACE_LOG0(TRACE_INFO, "  private_data_specifier_descriptor\n");
                break;
            case 0x65:  /* scrambling_descriptor */
                TRACE_LOG0(TRACE_INFO, "  scrambling_descriptor\n");
                break;
            case 0x66:  /* data_broadcast_id_descriptor */
                TRACE_LOG0(TRACE_INFO, "  data_broadcast_id_descriptor\n");
                result = HL_ParseDataBroadcastIdDescriptor(pData, pBitPos);
                break;
            default:
                TRACE_LOG0(TRACE_INFO, "parseNetworkDescriptor: default descriptor. Unhandled.");
                break;
        }
        skipLength += (2 + descLength);
    }

    return result;
}

static lc_result HL_ParseNITTransportLoop(const lc_buffer_st *pData, lc_uint32 *pBitPos, lc_uint16 length)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 skipLength = 0;
    lc_uint16 transportStreamId = 0;
    lc_uint16 originalNetworkId = 0;
    lc_uint16 transportDescLength = 0;
    
    while(skipLength < length)
    {
        gDownloadInfo.networkMatch = LC_FALSE;
        result = MessageParser_ReadBits(pData, pBitPos, 16, &transportStreamId);
        N2H16(&transportStreamId);
        result = MessageParser_ReadBits(pData, pBitPos, 16, &originalNetworkId);
        N2H16(&originalNetworkId);
        result = MessageParser_ReadBits(pData, pBitPos, 16, &transportDescLength);
        N2H16(&transportDescLength);
        transportDescLength &= 0xFFF;

        if((transportStreamId == gDownloadInfo.transportStreamId) && (originalNetworkId == gDownloadInfo.originalNetworkId))
        {
            gDownloadInfo.networkMatch = LC_TRUE;
        }
        result = HL_ParseDescriptor(pData, pBitPos, transportDescLength);
        skipLength += (6 + transportDescLength);
    }

    return result;
}


lc_result 
LoaderCoreAPI_SearchValidUpdateInNIT(
    const lc_buffer_st *pSection, 
    lc_si_parameters_for_dvb_ssu *pParameters)
{
    lc_result  result = LC_SUCCESS;
    lc_uchar   nitTID = 0x00;
    lc_uint16  sectionLength = 0;
    lc_uint16  networkId = 0;
    lc_uchar   version = 0x00;
    lc_uchar   sectionNumber = 0x00;
    lc_uchar   lastSectionNumber = 0x00;
    lc_uint16  networkDescLength = 0;
    lc_uint16  transportLoopLength = 0;
    lc_uint32  bitPos = 0;
    lc_uint32  crc32Org = 0;
    lc_uint32  crc32Cal = 0;


    if (LC_NULL == pParameters)
    {
        result = LC_ERROR_NULL_PARAM;
    }
    
    if (LC_SUCCESS == result)
    {
        result = LC_CheckType_Bytes(pSection);
    }
    
    if(LC_SUCCESS == result)
    {
        crc32Cal = CRC_MPEG32(pSection->bytes, pSection->length - 4);
        crc32Org = LC_GetUint32(pSection->bytes, pSection->length - 4);
        if(crc32Cal != crc32Org)
        {
            TRACE_LOG2(TRACE_DEBUG, "NIT: org crc32 0x%08x, cal crc32 0x%08x\n", crc32Org, crc32Cal);
            result = LC_ERROR_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &nitTID);
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &sectionLength);
        N2H16(&sectionLength);
        sectionLength &= 0x0FFF;
        if((0x40 != nitTID) || ((lc_uint32)(sectionLength + 3) != pSection->length))
        {
            result = LC_ERROR_WRONG_SECTION;
        }
    }
    
    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &networkId);
        N2H16(&networkId);
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &version);
        version = (version >> 1) & 0x1F;
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &sectionNumber);
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &lastSectionNumber);
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &networkDescLength);
        if (LC_SUCCESS == result)
        {
            N2H16(&networkDescLength);
            networkDescLength &= 0x0FFF;
            if(networkDescLength > 0)
            {
                /* Reset state flag to FALSE. */
                gDownloadInfo.nitMatch = LC_FALSE;
                /* Try to find and process a linkage descriptor. */
                HL_ParseDescriptor(pSection, &bitPos, networkDescLength);
            }
        }
    }
    
    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &transportLoopLength);
        if (LC_SUCCESS == result)
        {
            N2H16(&transportLoopLength);
            transportLoopLength &= 0x0FFF;

            if(transportLoopLength > 0)
            {
                HL_ParseNITTransportLoop(pSection, &bitPos, transportLoopLength);
            }
        }
    }

    if(LC_SUCCESS == result)
    {
        pParameters->validUpdate = gDownloadInfo.nitMatch; /* Set to TRUE when we find a matched download service for this client. */
        pParameters->data.nitSpec.serviceId = gDownloadInfo.serviceId;
        pParameters->data.nitSpec.selectorByte.downloadMode= gDownloadInfo.downloadMode;
        pParameters->data.nitSpec.selectorByte.triggerControlMode = gDownloadInfo.triggerControlMode;
    }

    return  result;
}


lc_result 
LoaderCoreAPI_SearchValidUpdateInPMT(
    const lc_buffer_st *pSection, 
    lc_uint16 serviceId, 
    lc_si_parameters_for_dvb_ssu *pParameters)
{
    lc_result result = LC_SUCCESS;
    lc_uchar  pmtTID = 0x00;
    lc_uint16 sectionLength = 0;
    lc_uint16 programNumber = 0;
    lc_uchar version = 0x00;
    lc_uchar sectionNumber = 0x00;
    lc_uchar lastSectionNumber = 0x00;
    lc_uint16 pcrPID = INVALID_PID;
    lc_uint16 programInfoLength = 0;
    lc_uchar  streamType = 0x00;
    lc_uint16 elementPID = INVALID_PID;
    lc_uint16 esInfoLength = 0;
    lc_uint32 bitPos = 0;
    lc_uint32 crc32Org = 0;
    lc_uint32 crc32Cal = 0;
    

    if (LC_NULL == pParameters)
    {
        result = LC_ERROR_NULL_PARAM;
    }
    
    if (LC_SUCCESS == result)
    {
        result = LC_CheckType_Bytes(pSection);
    }
    
    if(LC_SUCCESS == result)
    {
        crc32Cal = CRC_MPEG32(pSection->bytes, pSection->length - 4);
        crc32Org = LC_GetUint32(pSection->bytes, pSection->length - 4);
        if(crc32Cal != crc32Org)
        {
            TRACE_LOG2(TRACE_DEBUG, "PMT: org crc32 0x%08x, cal crc32 0x%08x\n", crc32Org, crc32Cal);
            result = LC_ERROR_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &pmtTID);
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &sectionLength);
        N2H16(&sectionLength);
        sectionLength &= 0x0FFF;
        if((0x02 != pmtTID) || ((lc_uint32)(sectionLength + 3) != pSection->length))
        {
            result = LC_ERROR_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &programNumber);
        N2H16(&programNumber);
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &version);
        version = (version >> 1) & 0x1F;
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &sectionNumber);
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &lastSectionNumber);
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &pcrPID);
        N2H16(&pcrPID);
        pcrPID &= 0x1FFF;
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &programInfoLength);
        N2H16(&programInfoLength);
        programInfoLength &= 0x0FFF;
        if(programInfoLength > 0)
        {
            HL_ParseDescriptor(pSection, &bitPos, programInfoLength);
        }
    }

    if(LC_SUCCESS == result)
    {
        while((bitPos / 8) < (lc_uint32)(sectionLength + 3 - 4))
        {
            result = MessageParser_ReadBits(pSection, &bitPos, 8, &streamType);
            result = MessageParser_ReadBits(pSection, &bitPos, 16, &elementPID);
            N2H16(&elementPID);
            elementPID &= 0x1FFF;
            if((streamType == 0x0B) && (programNumber == serviceId))
            {
                pParameters->data.pmtSpec.ssuPid = elementPID;
                pParameters->validUpdate = LC_TRUE;
                TRACE_LOG1(TRACE_INFO, "PMT: elementPID 0x%04x\n", elementPID);
            }
            result = MessageParser_ReadBits(pSection, &bitPos, 16, &esInfoLength);
            if(LC_SUCCESS == result)
            {
                N2H16(&esInfoLength);
                esInfoLength &= 0x0FFF;
                
                if(esInfoLength > 0)
                {
                    gDownloadInfo.pmtMatch = LC_FALSE;
                    /* Remove invalid initialization. It will output tuning parameters with all zeros. */
                    /*LC_memset(gDownloadInfo.privateData, 0x00, LC_MANUFACTURER_PRIVATE_INFO_LENGTH);*/
                    /* Try to find and process data broadcast id descriptor. */
                    result = HL_ParseDescriptor(pSection, &bitPos, esInfoLength);
                    if ((LC_SUCCESS == result) && (LC_TRUE == gDownloadInfo.pmtMatch))
                    {
                        LC_memcpy(pParameters->data.pmtSpec.manufacturerPrivateData, gDownloadInfo.privateData, LC_MANUFACTURER_PRIVATE_INFO_LENGTH);
                    }
                }
            }
        }
    }

    /* The update in PMT is valide when: streamType = 0x0B; program number matches the one in linkage descriptor, OUI matches the one in STB */
    if((LC_TRUE == pParameters->validUpdate) && (LC_TRUE == gDownloadInfo.pmtMatch))
    {
        pParameters->validUpdate = LC_TRUE;
    }
    else
    {
        pParameters->validUpdate = LC_FALSE;
    }

    return result;
}

lc_result 
LoaderCoreAPI_SearchValidUpdateInBAT(
    const lc_buffer_st *pSection, 
    lc_si_parameters_for_dvb_ssu *pParameters)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 crc32Cal = 0;
    lc_uint32 crc32Org = 0;
    lc_bat_section section;
    lc_uint16 skipLength = 0;
    lc_uint32 bitPos = 0;


    LC_memset(&section, 0, sizeof(lc_bat_section));

    if (LC_NULL == pParameters)
    {
        result = LC_ERROR_NULL_PARAM;
    }
    
    if (LC_SUCCESS == result)
    {
        result = LC_CheckType_Bytes(pSection);
    }
    
    if(LC_SUCCESS == result)
    {
        crc32Cal = CRC_MPEG32(pSection->bytes, pSection->length - 4);
        crc32Org = LC_GetUint32(pSection->bytes, pSection->length - 4);
        if(crc32Cal != crc32Org)
        {
            TRACE_LOG2(TRACE_DEBUG, "BAT: org crc32 0x%08x, cal crc32 0x%08x\n", crc32Org, crc32Cal);
            result = LC_ERROR_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &section.tableId);
        if(0x4A != section.tableId)
        {
            result = LC_ERROR_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &section.sectionLength);
        N2H16(&section.sectionLength);
        section.sectionLength &= 0x0FFF;
        if((lc_uint32)(section.sectionLength + 3) != pSection->length)
        {
            result = LC_ERROR_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &section.bouquetId);
        N2H16(&section.bouquetId);
        if((BOUQUET_ID_FOR_LOADER_V5 != section.bouquetId))
        {
            result = LC_ERROR_WRONG_SECTION;
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &section.version);
        section.version = (section.version >> 1) & 0x1F;
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &section.sectionNumber);
        result = MessageParser_ReadBits(pSection, &bitPos, 8, &section.lastSectionNumber);
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &section.bouquetDescLength);
        if(LC_SUCCESS == result)
        {
            N2H16(&section.bouquetDescLength);
            section.bouquetDescLength &= 0x0FFF;
            if(section.bouquetDescLength > 0)
            {
                /* Reset state flag to FALSE. */
                gDownloadInfo.nitMatch = LC_FALSE;
                /* Try to find and process a linkage descriptor. */
                HL_ParseDescriptor(pSection, &bitPos, section.bouquetDescLength);
            }
        }
    }

    if(LC_SUCCESS == result)
    {
        result = MessageParser_ReadBits(pSection, &bitPos, 16, &section.transportStreamLoopLength);
        N2H16(&section.transportStreamLoopLength);
        section.transportStreamLoopLength &= 0x0FFF;
        if(section.transportStreamLoopLength > 0)
        {
            skipLength = 0;
            while(skipLength < section.transportStreamLoopLength)
            {
                gDownloadInfo.networkMatch = LC_FALSE;
                result = MessageParser_ReadBits(pSection, &bitPos, 16, &section.transportStreamId);
                N2H16(&section.transportStreamId);
                result = MessageParser_ReadBits(pSection, &bitPos, 16, &section.originalNetworkId);
                N2H16(&section.originalNetworkId);
                result = MessageParser_ReadBits(pSection, &bitPos, 16, &section.transportDescLength);
                N2H16(&section.transportDescLength);
                section.transportDescLength &= 0x0FFF;

                if((section.transportStreamId == gDownloadInfo.transportStreamId) && (section.originalNetworkId == gDownloadInfo.originalNetworkId))
                {
                    gDownloadInfo.networkMatch = LC_TRUE;
                }
                if(section.transportDescLength > 0)
                {
                    result = HL_ParseDescriptor(pSection, &bitPos, section.transportDescLength);
                }
                skipLength += (6 + section.transportDescLength);
            }
        }
    }

    if(LC_SUCCESS == result)
    {
        pParameters->validUpdate = gDownloadInfo.nitMatch; /* Set to TRUE when we find a matched download service for this client. */
        pParameters->data.nitSpec.serviceId = gDownloadInfo.serviceId;
        pParameters->data.nitSpec.selectorByte.downloadMode= gDownloadInfo.downloadMode;
        pParameters->data.nitSpec.selectorByte.triggerControlMode = gDownloadInfo.triggerControlMode;
    }

    return result;
}


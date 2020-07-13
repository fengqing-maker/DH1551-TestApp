/*
 * This file provides loader v5 ird emm processing code for HighLevel.
 */
#include "LoaderCoreAPI_ApplicationHelper.h"
#include "LoaderCorePrivate.h"


/* EMM Routing. */
#define EMM_ROUTING_SC          (0)
#define EMM_ROUTING_CAM         (1)
#define EMM_ROUTING_IRD         (2)

/**
 * Structure for Decoder control message, type 7
 */
typedef struct _lc_decoder_control_message_seven
{
    lc_uchar forceDownload;
            
    lc_uchar includeNewVariant;

    lc_uchar includeNewSubvariant;

    lc_uint16 newVariant;

    lc_uint16 newSubvariant;
    
} lc_decoder_control_message_seven;


/**
 * IRD EMM message structure
 *
 * This structure is used to save IRD EMM message.
 * 
 */
typedef struct _lc_ird_emm_decoder_control_message_info
{

    /**
     * This 4-bit field contains the control message type.
     */
    lc_uchar controlMessageType;

    union
    {
        lc_decoder_control_message_seven messageType7;

    } payload;

} lc_ird_emm_message_info;


static lc_uint16 gVariantFromIrdEmm = 0xFFFF;
static lc_uint16 gSubVariantFromIrdEmm = 0xFFFF;



/*     Please refer to doc705410.
        Decoder_Message()
        {
            Destination_ID                              4bits
            Message_Length                            12bits
            {
                Pay_Load()                                8*n
            }
            CRC16                                       32bits
        }
        Decoder_Control_Message() {
            Control_Message_Type                        4bits
            Spare                                                 4bits
            If (Control_Message_Type == 7) {
                Spare                                             1bit
                Forced_Download                            1bit
                Spare                                             6bit
                Include_new_variant                        1bit
                Include_new_subvariant                   1bit
                if(Include_new_variant ==1)
                {
                    New variant                                 16bits
                }
                if(Include_new_subvariant ==1)
                {
                    New sub variant                                 16bits
                }
            }
            ............
        }
*/
lc_result IRDEMM_ParseIrdEMMForMigration(const lc_buffer_st *pBuffer, lc_uint16 *pVariant, lc_uint16 *pSubvariant)
{
    lc_result result = LC_SUCCESS;
    lc_uchar *pSkip = LC_NULL;
    lc_uint32 bytePos = 0;
    lc_uchar messageDestination = 0;
    lc_ird_emm_message_info irdEmm;

    LC_memset(&irdEmm, 0, sizeof(lc_ird_emm_message_info));

    result = LC_CheckType_Bytes(pBuffer);

    if (LC_SUCCESS == result)
    {
        if (LC_NULL == pVariant || LC_NULL == pSubvariant)
        {
            result = LC_ERROR_NULL_PARAM;
        }
    }
    
    if (LC_SUCCESS == result)
    {
        pSkip = pBuffer->bytes;

        if (LC_SUCCESS == result)
        {
            /* Destination_ID. */
            messageDestination = (lc_uchar)( ( pSkip[ bytePos ] & 0xf0 ) >> 4 );

            /* ONLY support decoder control message. */
            if(1 != messageDestination)
            {
                result = LC_ERROR_INVALID_DATA;
            }
            
            if (LC_SUCCESS == result)
            {
                pSkip += bytePos;
                irdEmm.controlMessageType =  (lc_uchar)( ( pSkip[ 2 ] & 0xf0 ) >> 4 );
                
                switch (irdEmm.controlMessageType)
                {
                    case 7:  /*It's an Ird EMM for Migration(Loader v5). */
                    {
                        /* force_download must be 0b1. */
                        if (LC_SUCCESS == result)
                        {
                            irdEmm.payload.messageType7.forceDownload = (lc_uchar)( ( pSkip[  3 ] & 0x40 ) >> 6 );
                            if (1 != irdEmm.payload.messageType7.forceDownload)
                            {
                                result = LC_ERROR_INVALID_DATA;
                            }
                        }

                        /* At least one of include_variant and include_subvariant should be 0b1. */
                        if (LC_SUCCESS == result)
                        {
                            irdEmm.payload.messageType7.includeNewVariant = (lc_uchar)( ( pSkip[ 4 ] & 0x80 ) >> 7 );
                            irdEmm.payload.messageType7.includeNewSubvariant = (lc_uchar)( ( pSkip[  4 ] & 0x40 ) >> 6 );
                            
                            if (0 == irdEmm.payload.messageType7.includeNewVariant && 
                                0 == irdEmm.payload.messageType7.includeNewVariant )
                            {
                                result = LC_ERROR_INVALID_DATA;
                            }
                        }

                        if (LC_SUCCESS == result)
                        {
                            /* Initialize. */
                            irdEmm.payload.messageType7.newVariant = 0xFFFF;
                            irdEmm.payload.messageType7.newSubvariant = 0xFFFF;

                            /* Update if necessary */
                            if (1 == irdEmm.payload.messageType7.includeNewVariant)
                            {
                                irdEmm.payload.messageType7.newVariant = (lc_uint16)( ( pSkip[ 5 ] << 8 ) + pSkip[ 6 ] );
                            }

                            if (1 == irdEmm.payload.messageType7.includeNewSubvariant)
                            {
                                irdEmm.payload.messageType7.newSubvariant = (lc_uint16)( ( pSkip[ 7 ] << 8 ) + pSkip[ 8 ] );
                            }

                            *pVariant = irdEmm.payload.messageType7.newVariant;
                            *pSubvariant = irdEmm.payload.messageType7.newSubvariant;
                        }                 

                        break;
                     }

                     default:
                     {
                        result = LC_ERROR_INVALID_DATA;
                        break;
                     }
                 }
            }
        }

    }
     
    return result;
}


lc_result IRDEMM_SetMigrationVariant(lc_uint16 variant, lc_uint16 subVariant)
{
    lc_result result = LC_SUCCESS;

    if(LC_SUCCESS == result)
    {
        gVariantFromIrdEmm = variant;
        gSubVariantFromIrdEmm = subVariant;
    }

    return result;
}


lc_result IRDEMM_GetMigrationVariant(lc_uint16 *pVariant, lc_uint16 *pSubVariant)
{
    lc_result result = LC_SUCCESS;
    
    if (LC_NULL == pVariant && LC_NULL == pSubVariant)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if(LC_SUCCESS == result)
    {
        if (LC_NULL != pVariant)
        {
            *pVariant = gVariantFromIrdEmm;
        }

        if (LC_NULL != pSubVariant)
        {
            *pSubVariant = gSubVariantFromIrdEmm;
        }
    }

    return result;
}

lc_result 
LoaderCoreAPI_SearchValidMigrationInIrdEmm(
    const lc_buffer_st *pBuffer, 
    lc_emm_parameters_for_migration *pMigrationParameters)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 parsedVariant = 0xFFFF;
    lc_uint16 parsedSubVariant = 0xFFFF;

    if (LC_NULL == pMigrationParameters)
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if (LC_SUCCESS == result)
    {
        result = LC_CheckType_Bytes(pBuffer);
    }

    if (LC_SUCCESS == result)
    {
        result = IRDEMM_SetMigrationVariant(0xFFFF, 0xFFFF);
    }

    if (LC_SUCCESS == result)
    {
        result = IRDEMM_ParseIrdEMMForMigration(pBuffer, &parsedVariant, &parsedSubVariant);
    }

    if (LC_SUCCESS == result)
    {
        if (LC_TRUE != LC_IsVariantValid(&parsedVariant, &parsedSubVariant))
        {
            result = LC_FAILURE;
        }
    }

    if (LC_SUCCESS == result)
    {
        result = IRDEMM_SetMigrationVariant(parsedVariant, parsedSubVariant);

        if (LC_SUCCESS == result)
        {
            pMigrationParameters->validMigrationEmm = LC_TRUE;
            pMigrationParameters->variant = parsedVariant;
            pMigrationParameters->subVariant = parsedSubVariant;
        }
    }

    return result;
}




#ifndef _REMOTEKEY_H
#define _REMOTEKEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "adi_hdicommon.h"
#include "adi_ir.h"
#include "adi_typedef.h"

typedef enum _IrCommandType
{
    IRKEY_TV_RADIO          = 0x0C,
    IRKEY_CHANNEL_LIST      = 0x10,
    IRKEY_CHANNEL_FAV_LIST  = 0x08,
    IRKEY_CHANNEL_RETURN    = 0x5C,
    IRKEY_CHANNEL_PLUS      = 0x1F,
    IRKEY_CHANNEL_MINUS     = 0x19,

    IRKEY_AUDIO             = 0x44,
    IRKEY_VOLUME_PLUS       = 0x16,
    IRKEY_VOLUME_MINUS      = 0x15,

    IRKEY_UP                = 0x52,
    IRKEY_POWER             = 0x46,
    IRKEY_EXIT              = 0x1B,
    IRKEY_MENU              = 0x07,
    IRKEY_DOWN              = 0x13,
    IRKEY_LEFT              = 0x06,
    IRKEY_SELECT            = 0x0F,
    IRKEY_RIGHT             = 0x1A,

    IRKEY_NUM_0             = 0x50,
    IRKEY_NUM_1             = 0x49,
    IRKEY_NUM_2             = 0x55,
    IRKEY_NUM_3             = 0x59,
    IRKEY_NUM_4             = 0x4D,
    IRKEY_NUM_5             = 0x51,
    IRKEY_NUM_6             = 0x5D,
    IRKEY_NUM_7             = 0x48,
    IRKEY_NUM_8             = 0x54,
    IRKEY_NUM_9             = 0x58,

    IRKEY_MUTE              = 0x5A,
    IRKEY_PAGE_UP           = 0x03,
    IRKEY_PAGE_DOWN         = 0x05,
    IRKEY_CLOCK             = 0x5F,

    IRKEY_INFO              = 0x14,
    IRKEY_RED               = 0x47,
    IRKEY_GREEN             = 0x4B,
    IRKEY_YELLOW            = 0x57,
    IRKEY_BLUE              = 0x5B,
    IRKEY_MTS               = 0x41,

    IRKEY_TTX               = 0x0A,
    IRKEY_CC                = 0x09,
    IRKEY_OUTPUT_SOURCE     = 0x04,

    IRKEY_ZOOM              = 0x4C,
    IRKEY_DASH              = 0x4E,
    IRKEY_SLEEP             = 0x45,
    IRKEY_EPG               = 0x4A,
    IRKEY_PIP               = 0x40,

    IRKEY_MIX               = 0x1C,
    IRKEY_INDEX             = 0x18,
    IRKEY_HOLD              = 0x00,

    IRKEY_PREVIOUS          =  0x02,//0x0E,
    IRKEY_NEXT              =  0x1E,//0x12,

    IRKEY_FORWARD           = 0x12,//0x02,
    IRKEY_BACKWARD          = 0x0E,//0x1E,

    IRKEY_PLAY              = 0x01,
    IRKEY_RECORD            = 0x0D,
    IRKEY_STOP              = 0x11,
    IRKEY_PAUSE             = 0x1D,

    IRKEY_SIZE              = 0x43,
    IRKEY_REVEAL            = 0x4F,
    IRKEY_SUBCODE           = 0x53,
    IRKEY_GUIDE             = 0x42,

}IrCommandType;

void AppIrCallBack(ADIKeyCallbackType eCallbackType ,void * pvUserData);
ADIIREquipList_S*  GetIrWquipList( void );
//ADIIREquipList_S*  GetIrWquipList_TSY82( void );
void HandleSpecialKey(unsigned int & unSpecialKey);
void MSAppIrInit();

#ifdef __cplusplus
}
#endif


#endif

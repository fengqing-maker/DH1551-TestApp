/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : LedDisplay.c                                               *
*                                                                            *
*   Description : 7-segements LED display.                                   *
*                                                                            *
*****************************************************************************/


#include "LoaderCorePrivate.h"
#include <osal/osal.h>


/* for HEX digit displaying */
static const lc_front_panel_char  aenDigitDisplay[16] =
{ CHAR_0, CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHAR_5, CHAR_6, CHAR_7,
  CHAR_8, CHAR_9, CHAR_A, CHAR_b, CHAR_C, CHAR_d, CHAR_E, CHAR_F };

/* for spinning 0 displaying */
static const lc_front_panel_char aenSP0Display[6] =
{ CHAR_SP0_1, CHAR_SP0_2, CHAR_SP0_3, CHAR_SP0_4, CHAR_SP0_5, CHAR_SP0_6 };


#define MAX_HEX_DIGIT_ARRAY_SIZE sizeof(aenDigitDisplay)


void LC_LedDisplay(
    lc_led_flash_mask flashMask,
    lc_front_panel_char enChar_L,
    lc_front_panel_char enChar_M,
    lc_front_panel_char enChar_R)
{
    LC_UNUSED(flashMask);

    LoaderCoreSPI_FrontPanel_Display(CHAR_BLNK, enChar_L, enChar_M, enChar_R);
}

void LC_LedDisplaySP0(lc_front_panel_char enChar_L)
{
    static lc_uchar bSP0cnt = 0;
   
    LC_LedDisplay(LED_CHAR_NONE, enChar_L, aenSP0Display[bSP0cnt++], CHAR_BLNK );
    if( bSP0cnt > 5 )
    {
        bSP0cnt = 0;
    }
}

void LC_LedDisplayClear(void)
{
    LC_LedDisplay(LED_CHAR_NONE, CHAR_BLNK, CHAR_BLNK, CHAR_BLNK);
}


lc_front_panel_char LC_LedDisplayGetHexDigit(lc_uint32 digit)
{
    lc_front_panel_char hexDigit = CHAR_BLNK;

    if (digit < MAX_HEX_DIGIT_ARRAY_SIZE)
    {
        hexDigit = aenDigitDisplay[digit];
    }

    return hexDigit;
}



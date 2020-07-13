/**
 * @file LoaderCoreSPI_FrontPanel.h
 * Header for front panel methods. This file contains the prototypes for all front panel functions 
 * that are used by the Loader Core.
 *
 */

#ifndef LOADERCORESPI_FRONTPANEL_H__INCLUDED__
#define LOADERCORESPI_FRONTPANEL_H__INCLUDED__

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup loadercorespis Loader Core SPIs
 *  Loader Core SPIs
 *
 *  
 *  @{
 */


/** @defgroup loadercorefrontpanelspis Loader Core Front Panel SPIs
 *  Loader Core Front Panel SPIs
 *
 *  Methods to interact with front panel in the client device.
 *  
 *  @{
 */

 /** 
 *  Front Panel Key Events.
 *  List of all possible values of ::lc_front_panel_key_event codes. 
 *
 *  Key IDs of front panel.
 */
typedef enum _lc_front_panel_key_event
{
    /** (0) No key was pressed.*/
    KEY_NONE        = 0,

    /** (1) Key STANDBY was pressed.*/
    KEY_STANDBY     = 1,

    /** (2) Key UP was pressed.*/
    KEY_UP          = 2,

    /** (3) Key DOWN was pressed.*/
    KEY_DOWN        = 3,

    /** (4) Unknown key was pressed.*/
    KEY_OTHER       = 4
    
} lc_front_panel_key_event;


/** 
 *  Front Panel Display Chars.
 *  List of all possible values of ::lc_front_panel_char codes. 
 *
 *  Display patterns of 7-segment LEDs on the front panel.
 *  \note Manufacturer MUST not change the value directly! Manufacturers must map the value to the platform-specific pattern values.
 */
typedef enum _lc_front_panel_char
{
    CHAR_0       = 0,    /*Char 0.*/
    CHAR_1       = 1,    /*Char 1.*/
    CHAR_2       = 2,    /*Char 2.*/
    CHAR_3       = 3,    /*Char 3.*/
    CHAR_4       = 4,    /*Char 4.*/
    CHAR_5       = 5,    /*Char 5.*/
    CHAR_6       = 6,    /*Char 6.*/
    CHAR_7       = 7,    /*Char 7.*/
    CHAR_8       = 8,    /*Char 8.*/
    CHAR_9       = 9,    /*Char 9.*/
    CHAR_A          ,    /*Char A.*/
    CHAR_b          ,    /*Char b.*/
    CHAR_C          ,    /*Char C.*/
    CHAR_d          ,    /*Char d.*/
    CHAR_E          ,    /*Char E.*/
    CHAR_F          ,    /*Char F.*/
    CHAR_H          ,    /*Char H.*/
    CHAR_L          ,    /*Char L.*/
    CHAR_P          ,    /*Char P.*/
    CHAR_r          ,    /*Char r.*/
    CHAR_t          ,    /*Char t.*/
    CHAR_U          ,    /*Char U.*/
    CHAR_D          ,    /*Char D.*/
 
    CHAR_SP0_1      ,
    CHAR_SP0_2      ,    /*    -3--    */
    CHAR_SP0_3      ,    /* 2 |    | 4 */
    CHAR_SP0_4      ,    /*    -7--    */
    CHAR_SP0_5      ,    /* 1 |    | 5 */
    CHAR_SP0_6      ,    /*    -6--    */
    CHAR_SP0_7      ,
    CHAR_SP0_dot    ,    /*Symbol for dot.*/
    CHAR_4dot       ,    /* 4. */
    CHAR_BLNK            /*Nothing.*/
    
} lc_front_panel_char;


/** 
 * Read a key event which is triggered when a front panel button is pressed.
 * 
 * The SPI gets a key event from front panel. In case of timeout, the SPI driver must return LC_SUCCESS and set the key event to ::KEY_NONE .
 *
 * @param pFrontPanelKeyEvent [OUT] Pointer to save the key event returned. See all the key events listed in \ref lc_front_panel_key_event "Front Panel Key Events". 
 * @param timeoutMillisecond  [IN]  Timeout in millisecond that Loader Core will wait for a key event. If timeout happens, the SPI driver must return LC_SUCCESS and set *pFrontPanelKeyEvent to KEY_NONE. 
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_FrontPanel_GetKey(lc_front_panel_key_event *pFrontPanelKeyEvent, lc_uint32 timeoutMillisecond);

/** 
 * Display chars on front panel 7-segment light.
 *
 * This SPI displays chars on the front panel 7-segment light. 
 * Loader Core will display chars on the front panel in order to show the status.
 * 
 * @param extensionChar [IN] Reserved to CHAR_BLNK.
 * @param leftChar      [IN] Char to be displayed on the left 7-segment light. See \ref lc_front_panel_char "Front Panel Display Chars" to get the list. 
 * @param middleChar    [IN] Char to be displayed on the middle 7-segment light. See \ref lc_front_panel_char "Front Panel Display Chars" to get the list. 
 * @param rightChar     [IN] Char to be displayed on the right 7-segment light. See \ref lc_front_panel_char "Front Panel Display Chars" to get the list. 
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_FrontPanel_Display(lc_front_panel_char extensionChar, lc_front_panel_char leftChar, lc_front_panel_char middleChar, lc_front_panel_char rightChar);

/** @} */ /* End of Loader Core Front Panel Key Events */

/** @} */ /* End of Loader Core SPIs */


#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_FRONTPANEL_H__INCLUDED__ */


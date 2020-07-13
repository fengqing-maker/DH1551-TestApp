
#ifndef LED_DISPLAY_H__INCLUDED__
#define LED_DISPLAY_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/** Public Function Prototypes **********************************************/

typedef enum _lc_led_flash_mask
{
    /** None */
    LED_CHAR_NONE = 0,
    
    /** The left charactor */
    LED_CHAR_LEFT = 4,

    /** The middle charactor */
    LED_CHAR_MIDDLE = 2,

    /** The right charactor */
    LED_CHAR_RIGHT = 1
    
} lc_led_flash_mask;

/** 
 * LED display
 * This function is used to display charactors in LED panel.
 * 
 * @param flashPos Indicates which one is going to flash.
 * @param enChar_L Charactor to be displayed in the left.
 * @param enChar_M Charactor to be displayed in the middle.
 * @param enChar_R Charactor to be displayed in the right.
 * 
 * @return Void.
 */
void LC_LedDisplay(
    lc_led_flash_mask flashMask,
    lc_front_panel_char enChar_L,
    lc_front_panel_char enChar_M,
    lc_front_panel_char enChar_R);

/** 
 * LED display together with a spinning "0".
 * 
 * @param enChar_L Charactor to be displayed in the left.
 * \note the spinning "0" is displayed in the middle one of the three available charactors.
 * 
 * @return Void.
 */
void LC_LedDisplaySP0(lc_front_panel_char enChar_L);

/** 
 * LED display clear all.
 * 
 * @param Void.
 * 
 * @return Void.
 */
void LC_LedDisplayClear(void);

/** 
 * Get hex charactor for LED display.
 * 
 * @param digit Digital number of Charactor required to be displayed.
 * 
 * @return Hex digit.
 */
lc_front_panel_char LC_LedDisplayGetHexDigit(lc_uint32 digit);


#ifdef __cplusplus
}
#endif

#endif  /* LED_DISPLAY_H__INCLUDED__ */


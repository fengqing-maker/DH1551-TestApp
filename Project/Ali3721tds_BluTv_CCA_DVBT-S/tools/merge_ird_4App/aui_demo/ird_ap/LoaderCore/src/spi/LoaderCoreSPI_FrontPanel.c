/**
 * @file LoaderCoreSPI_FrontPanel.h
 * Header for front panel methods. This file contains the prototypes for all front panel functions 
 * that are used by the Loader Core.
 *
 */

#include "LoaderCoreSPI.h"
#include <aui_input.h>
#include <aui_panel.h>
#include <aui_gpio.h>
#include <osal/osal.h>

//#define BOARD_NO_PANEL  // for vdl

//CH455 PANEL linux-PDK-XXX/drivers/alidrivers/include/ali_front_panel_common.h
static const struct aui_pannel_key_map ali_pankey_map[] =
{
	{(0xffff0000),		68},//KEY_POWER
	{(0xffff0001),		76},//KEY_ENTER/
	{(0xffff0002),		84},//KEY_UP/
	{(0xffff0003),		92},//KEY_DOWN/
	{(0xffff0004),		100},//KEY_LEFT/
	{(0xffff0005),		108},//KEY_RIGHT/
	{(0xffff0006),		116},//KEY_MENU/
};

/*//CH455 PANEL  LED VALUE aui/samples/sample_src/aui_panel_test.c
static struct led_bitmap bitmap_table[PAN_MAX_CHAR_LIST_NUM * 2] =
{
	{'.', 0x80}, // Let's put the dot bitmap into the table 
	{'0', 0x3f}, {'1', 0x06}, {'2', 0x5b}, {'3', 0x4f}, 
	{'4', 0x66}, {'5', 0x6d}, {'6', 0x7d}, {'7', 0x07}, 
	{'8', 0x7f}, {'9', 0x6f}, {'a', 0x5f}, {'A', 0x77}, 
	{'b', 0x7c}, {'B', 0x7c}, {'c', 0x39}, {'C', 0x39}, 
	{'d', 0x5e}, {'D', 0x5e}, {'e', 0x79}, {'E', 0x79}, 
	{'f', 0x71}, {'F', 0x71}, {'g', 0x6f}, {'G', 0x3d}, 
	{'h', 0x76}, {'H', 0x76}, {'i', 0x04}, {'I', 0x30}, 
	{'j', 0x0e}, {'J', 0x0e}, {'l', 0x38}, {'L', 0x38}, 
	{'n', 0x54}, {'N', 0x37}, {'o', 0x5c}, {'O', 0x3f}, 
	{'p', 0x73}, {'P', 0x73}, {'q', 0x67}, {'Q', 0x67}, 
	{'r', 0x50}, {'R', 0x77}, {'s', 0x6d}, {'S', 0x6d}, 
	{'t', 0x78}, {'T', 0x31}, {'u', 0x3e}, {'U', 0x3e}, 
	{'y', 0x6e}, {'Y', 0x6e}, {'z', 0x5b}, {'Z', 0x5b}, 
	{':', 0x80}, {'-', 0x40}, {'_', 0x08}, {' ', 0x00},
};
*/


#define STANDBY_KEY_CODE    (68)
#define UP_KEY_CODE         (84)
#define DOWN_KEY_CODE       (92)
#define DEVICE_INDEX_PANEL  (0)
#define DEVICE_INDEX_KEY    (1)
#define PANEL_ID            (0)
#define MAX_PANEL_STR_LEN   (4)

#define LC_SPI_PANEL_DEBUG(...)
//#define LC_SPI_PANEL_DEBUG LoaderCoreSPI_Stdlib_printf

#define BT_LONG_PRESS_TIME     (1000)
#define BT_PRESS_EVENT_STEP     (1000)

static aui_hdl g_key_hdl = LC_NULL;
static aui_hdl g_panel_hdl = LC_NULL;

static lc_result lc_panel_init()
{
    lc_result lc_ret = LC_SUCCESS;
    
    if(LC_NULL == g_panel_hdl)
    {
         //aui_panel_init(LC_NULL,LC_NULL);    //fixed
         if(AUI_RTN_SUCCESS != aui_find_dev_by_idx(AUI_MODULE_PANEL, DEVICE_INDEX_PANEL , &g_panel_hdl))
         {
            if(LC_NULL == g_panel_hdl)
            {
                if(AUI_RTN_SUCCESS !=aui_panel_open(PANEL_ID, LC_NULL, &g_panel_hdl))
                {
                    LC_SPI_PANEL_DEBUG("aui_panel_open fail\n");
                    lc_ret = LC_FAILURE;
                    g_panel_hdl = LC_NULL;
                }
            }
			else
			{
			   ;
			}
            
         }
         else
         {
             LC_SPI_PANEL_DEBUG("panel has been open\n");
         }
    }
    return lc_ret;
}

static lc_result lc_key_init()
{
    lc_result lc_ret = LC_SUCCESS;

	LC_SPI_PANEL_DEBUG("lc_key_init\n");
    if(LC_NULL == g_key_hdl)
    {
		 LC_SPI_PANEL_DEBUG("aui_key_find_dev\n");
         if(AUI_RTN_SUCCESS != aui_find_dev_by_idx(AUI_MODULE_PANEL, DEVICE_INDEX_KEY, &g_key_hdl))
         {
            if(LC_NULL == g_key_hdl)
            {
				LC_SPI_PANEL_DEBUG("aui_key_open\n");
         		aui_key_init(LC_NULL,LC_NULL);
                if(AUI_RTN_SUCCESS !=aui_key_open(0, LC_NULL, &g_key_hdl))
                {
                    LC_SPI_PANEL_DEBUG("aui_key_open fail\n");
                    lc_ret = LC_FAILURE;
                    g_key_hdl = LC_NULL;
                }
            }
         }
         else
         {
             LC_SPI_PANEL_DEBUG("panel has been open\n");
         }
    }
    return lc_ret;
}

static void transfer_key(lc_uint32 n_key_code ,lc_front_panel_key_event *pFrontPanelKeyEvent)
{
    switch(n_key_code)
    {
        case STANDBY_KEY_CODE:
        {
            *pFrontPanelKeyEvent = KEY_STANDBY;
             break;
        }
        case UP_KEY_CODE:
        {
            *pFrontPanelKeyEvent = KEY_UP;
             break;
        }
        case DOWN_KEY_CODE:
        {
            *pFrontPanelKeyEvent = KEY_DOWN;
             break;
        }
        default:
        {
            *pFrontPanelKeyEvent = KEY_OTHER;//will be treat enter
            break;
        }
    }
}


static void convert_panel_char(lc_char *to_be, lc_front_panel_char input_c)
{
    switch(input_c)
	{
	    case CHAR_0:
	    {
	        *to_be = '0';
	        break;
	    }
	    case CHAR_1:
	    {
	        *to_be = '1';
	        break;
	    }
	    case CHAR_2:
	    {
	        *to_be = '2';
	        break;
	    }
	    case CHAR_3:
	    {
	        *to_be = '3';
	        break;
	    }
	    case CHAR_4:
	    {
	        *to_be = '4';
	        break;
	    }
	    case CHAR_5:
	    {
	        *to_be = '5';
	        break;
	    }
	    case CHAR_6:
	    {
	        *to_be = '6';
	        break;
	    }
	    case CHAR_7:
	    {
	        *to_be = '7';
	        break;
	    }
	    case CHAR_8:
	    {
	        *to_be = '8';
	        break;
	    }
	    case CHAR_9:
	    {
	        *to_be = '9';
	        break;
	    }
	    case CHAR_A:
	    {
	        *to_be = 'A';
	        break;
	    }
	    case CHAR_b:
	    {
	        *to_be = 'b';
	        break;
	    }
	    case CHAR_C:
	    {
	        *to_be = 'C';
	        break;
	    }
	    case CHAR_d:
	    {
	        *to_be = 'd';
	        break;
	    }
	    case CHAR_E:
	    {
	        *to_be = 'E';
	        break;
	    }
	    case CHAR_F:
	    {
	        *to_be = 'F';
	        break;
	    }
	    case CHAR_H:
	    {
	        *to_be = 'H';
	        break;
	    }
	    case CHAR_L:
	    {
	        *to_be = 'L';
	        break;
	    }
	    case CHAR_P:
	    {
	        *to_be = 'P';
	        break;
	    }
	    case CHAR_r:
	    {
	        *to_be = 'r';
	        break;
	    }
	    case CHAR_t:
	    {
	        *to_be = 't';
	        break;
	    }
	    case CHAR_U:
	    {
	        *to_be = 'U';
	        break;
	    }
	    case CHAR_D:
	    {
	        *to_be = 'D';
	        break;
	    }
	    case CHAR_SP0_1:
	    {
	        *to_be = 0x5;
	        break;
	    }
	    case CHAR_SP0_2:
	    {
	        *to_be = 0x6;
	        break;
	    }
	    case CHAR_SP0_3:
	    {
	        *to_be = 0x1;
	        break;
	    }
	    case CHAR_SP0_4:
	    {
	        *to_be = 0x2;
	        break;
	    }
	    case CHAR_SP0_5:
	    {
	        *to_be = 0x3;//ok
	        break;
	    }
	    case CHAR_SP0_6:
	    {
	        *to_be = 0x4;//ok
	        break;
	    }
	    case CHAR_SP0_7:
	    {
	        *to_be = '-';//ok
	        break;
	    }
	    case CHAR_SP0_dot:
	    {
	        *to_be = '.';
	        break;
	    }
	    case CHAR_4dot:
	    {
	        *to_be = '4';
	        break;
	    }
	    case CHAR_BLNK:
	    {
	        *to_be = ' ';
	        break;
	    }
	    default:
	    {
	        *to_be = ' ';
	        break;
	    }
	}
}
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
lc_result LoaderCoreSPI_FrontPanel_GetKey(lc_front_panel_key_event *pFrontPanelKeyEvent, lc_uint32 timeoutMillisecond)   //500
{
    aui_key_info pkey_info;
    aui_hdl pv_hdl_key = LC_NULL;
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;
    lc_result lc_ret = LC_SUCCESS;
    lc_uint32 timeout = timeoutMillisecond;
    lc_uint32 time_step = 200;
    lc_uint32 i = 0;
    lc_sint32 ret = -1;
    lc_uint32 pressCnt = 0;

    if(LC_NULL == pFrontPanelKeyEvent)
    {
        LC_SPI_PANEL_DEBUG("LoaderCoreSPI_FrontPanel_GetKey invalid parametor\n");
        lc_ret = LC_FAILURE;
        return lc_ret;
    }
    // check the device has been open or not
    if(LC_NULL == g_key_hdl)
    {
		LC_SPI_PANEL_DEBUG("key handle is NULL\n");
        if(LC_SUCCESS != lc_key_init())
        {
            LC_SPI_PANEL_DEBUG("lc_key_init fail\n");
            lc_ret = LC_FAILURE;
            return lc_ret;
        }
    }
    pv_hdl_key = g_key_hdl;
    LoaderCoreSPI_Stdlib_memset(&pkey_info,0,sizeof(aui_key_info));
    pkey_info.e_type = AUI_KEY_TYPE_FRONTPANEL;

    do
    {
        rtn = aui_key_key_get(pv_hdl_key, &pkey_info);
        if(AUI_RTN_SUCCESS != rtn)
        {
            //LC_SPI_PANEL_DEBUG("Can not get the key from panel\n");   
            *pFrontPanelKeyEvent = KEY_NONE;
        }
        else
        {
			LC_SPI_PANEL_DEBUG("get the key from panel\n");
            if(AUI_KEY_STATUS_PRESS == pkey_info.e_status)
            {
                transfer_key(pkey_info.n_key_code & 0xFF,pFrontPanelKeyEvent);
				LC_SPI_PANEL_DEBUG("key pressed, FrontPanelKeyEvent: %d, pkey_info.n_key_code: %d\n", *pFrontPanelKeyEvent, pkey_info.n_key_code & 0xFF);
				break;
            }
            else
            {
                *pFrontPanelKeyEvent = KEY_NONE;
            }
        }
        i++;
        LoaderCoreSPI_Thread_Sleep(time_step);            
    }while(i< timeout/time_step);
    
	return lc_ret;
}


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
lc_result LoaderCoreSPI_FrontPanel_Display(lc_front_panel_char extensionChar, lc_front_panel_char leftChar, lc_front_panel_char middleChar, lc_front_panel_char rightChar)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_char str[MAX_PANEL_STR_LEN] ={0};
    AUI_RTN_CODE rtn = AUI_RTN_SUCCESS;

    if(LC_NULL == g_panel_hdl)
    {
        if(LC_SUCCESS != lc_panel_init())
        {
            LC_SPI_PANEL_DEBUG("lc_panel_init fail\n");
            lc_ret = LC_FAILURE;
            return lc_ret;
        }
    }
	
    convert_panel_char(&str[0],extensionChar);
    convert_panel_char(&str[1],leftChar);
    convert_panel_char(&str[2],middleChar);
    convert_panel_char(&str[3],rightChar);
    rtn = aui_panel_display(g_panel_hdl, AUI_PANEL_DATA_ANSI,    \
             			(unsigned char *)str, 4);
    if(AUI_RTN_SUCCESS != rtn)
    {
        LC_SPI_PANEL_DEBUG("aui_panel_display fail\n");   
        lc_ret = LC_FAILURE;
    }

	return lc_ret;
    
}



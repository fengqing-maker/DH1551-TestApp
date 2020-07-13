 /*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_dvt_mainmenu.h
*
*    Description:   The main menu of dvt
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#ifndef _WIN_MAINMENU_H_
#define _WIN_MAINMENU_H_

#ifdef __cplusplus
extern "C"
{
#endif

extern CONTAINER    g_win_mainmenu;
extern TEXT_FIELD    mainmenu_bg;

extern CONTAINER    mm_item_con1;
extern CONTAINER    mm_item_con2;
extern CONTAINER    mm_item_con3;
extern CONTAINER    mm_item_con4;
extern CONTAINER    mm_item_con5;
#ifndef DISABLE_USB
extern CONTAINER    mm_item_con6;
#endif

extern BITMAP       mm_item_bmp1;
extern BITMAP       mm_item_bmp2;
extern BITMAP       mm_item_bmp3;
extern BITMAP       mm_item_bmp4;
extern BITMAP       mm_item_bmp5;
extern BITMAP       mm_item_bmp6;


//TEXT_FIELD   mm_item_txt1;
//TEXT_FIELD   mm_item_txt2;
//TEXT_FIELD   mm_item_txt3;
//TEXT_FIELD   mm_item_txt4;
//TEXT_FIELD   mm_item_txt5;
//TEXT_FIELD   mm_item_txt6;

extern BOOL mainmenu_is_opening;


#ifdef __cplusplus
}
#endif

#endif//_WIN_MAINMENU_SUBMENU_H_

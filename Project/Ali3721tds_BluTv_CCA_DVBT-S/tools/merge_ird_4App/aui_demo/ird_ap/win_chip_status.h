/*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_chip_status.h
*
*    Description: The menu for chip status
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#ifndef _WIN_CHIP_STATUS_H_
#define _WIN_CHIP_STATUS_H_
#include <sys_config.h>

#ifdef __cplusplus
extern "C"{
#endif

extern CONTAINER win_cs_test_con;

extern CONTAINER cs_item_con1;
extern CONTAINER cs_item_con2;
extern CONTAINER cs_item_con3;
extern CONTAINER cs_item_con4;
extern CONTAINER cs_item_con5;
extern CONTAINER cs_item_con6;
extern CONTAINER cs_item_con7;

extern TEXT_FIELD cs_item_txtname1;
extern TEXT_FIELD cs_item_txtname2;
extern TEXT_FIELD cs_item_txtname3;
extern TEXT_FIELD cs_item_txtname4;
extern TEXT_FIELD cs_item_txtname5;
extern TEXT_FIELD cs_item_txtname6;
extern TEXT_FIELD cs_item_txtname7;

extern TEXT_FIELD cs_item_txtset1;
extern EDIT_FIELD cs_item_edit2;
extern EDIT_FIELD cs_item_edit3;
extern EDIT_FIELD cs_item_edit4;
extern EDIT_FIELD cs_item_edit5;
extern EDIT_FIELD cs_item_edit6;
extern TEXT_FIELD cs_item_txtset7;

extern TEXT_FIELD cs_item_line1;
extern TEXT_FIELD cs_item_line2;
extern TEXT_FIELD cs_item_line3;
extern TEXT_FIELD cs_item_line4;
extern TEXT_FIELD cs_item_line5;
extern TEXT_FIELD cs_item_line6;
extern TEXT_FIELD cs_item_line7;
extern TEXT_FIELD cs_btn_ok;
extern TEXT_FIELD cs_btn_ok2;

extern MULTI_TEXT cs_mtxt_zone_city;


extern TEXT_CONTENT cszone_mtxt_content[];

#ifdef __cplusplus
 }
#endif
#endif//_WIN_CHIP_STATUS_H_


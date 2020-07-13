 /*****************************************************************************
*    Copyright (c) 2018 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: win_dvt_mainmenu_submenu_data.c
*
*    Description:   The members define of sub menu
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
*****************************************************************************/
#include "win_dvt_mainmenu_submenu.h"

POBJECT_HEAD tools_sub_menus[] = {
    // test app
    (POBJECT_HEAD)&win_loader_status_con,
    (POBJECT_HEAD)&win_mem_con,
    (POBJECT_HEAD)&win_md_test_con,
    (POBJECT_HEAD)&win_otaupg_con,
    (POBJECT_HEAD)&win_upg_con,
    (POBJECT_HEAD)&win_cs_test_con,
};


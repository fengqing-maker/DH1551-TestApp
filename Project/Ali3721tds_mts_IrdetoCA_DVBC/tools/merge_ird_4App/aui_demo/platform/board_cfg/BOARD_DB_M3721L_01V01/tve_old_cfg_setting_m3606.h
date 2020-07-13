#define CB_LEVEL_PAL				0x8f
#define CB_LEVEL_NTSC				0xd4 //0x70
#define CR_LEVEL_PAL				0x53
#define CR_LEVEL_NTSC				0x06 //0x82
#define LUMA_LEVEL_PAL				0x51
#define LUMA_LEVEL_NTSC			    0x4d
#define CHRMA_LEVEL_PAL			    0x65
#define CHRMA_LEVEL_NTSC			0x63
#define FREQ_RESPONSE_PAL			0x102
#define FREQ_RESPONSE_NTSC		    0x102

#define CB_LEVEL_PAL_SD				0x85
#define CB_LEVEL_NTSC_SD            0x85
#define CR_LEVEL_PAL_SD				0x55
#define CR_LEVEL_NTSC_SD			0x55
#define LUMA_LEVEL_PAL_SD			0x52 //0x53
#define LUMA_LEVEL_NTSC_SD			0x4d //0x4f
#define CHRMA_LEVEL_PAL_SD			0x6
#define CHRMA_LEVEL_NTSC_SD		    0x6
#define FREQ_RESPONSE_PAL_SD		0x102
#define FREQ_RESPONSE_NTSC_SD		0x102

// for de_n
__MAYBE_UNUSED__ static struct tve_adjust g_tve_adjust_table[] = {
    {TVE_ADJ_COMPOSITE_Y_DELAY, SYS_625_LINE, 3}, {TVE_ADJ_COMPOSITE_Y_DELAY, SYS_525_LINE, 7},
    {TVE_ADJ_COMPOSITE_C_DELAY, SYS_625_LINE, 6}, {TVE_ADJ_COMPOSITE_C_DELAY, SYS_525_LINE, 7},
    {TVE_ADJ_COMPONENT_Y_DELAY, SYS_625_LINE, 0}, {TVE_ADJ_COMPONENT_Y_DELAY, SYS_525_LINE, 3},
    {TVE_ADJ_COMPONENT_CB_DELAY, SYS_625_LINE, 0}, {TVE_ADJ_COMPONENT_CB_DELAY, SYS_525_LINE, 4},
    {TVE_ADJ_COMPONENT_CR_DELAY, SYS_625_LINE, 0}, {TVE_ADJ_COMPONENT_CR_DELAY, SYS_525_LINE, 4},
    {TVE_ADJ_BURST_LEVEL_ENABLE, SYS_625_LINE, 0}, {TVE_ADJ_BURST_LEVEL_ENABLE, SYS_525_LINE, 0},
    {TVE_ADJ_BURST_CB_LEVEL, SYS_625_LINE, CB_LEVEL_PAL/**/}, {TVE_ADJ_BURST_CB_LEVEL, SYS_525_LINE, CB_LEVEL_NTSC/**/},
    {TVE_ADJ_BURST_CR_LEVEL, SYS_625_LINE, CR_LEVEL_PAL/**/}, {TVE_ADJ_BURST_CR_LEVEL, SYS_525_LINE, CR_LEVEL_NTSC/**/},
    {TVE_ADJ_COMPOSITE_LUMA_LEVEL, SYS_625_LINE, LUMA_LEVEL_PAL/**/}, {TVE_ADJ_COMPOSITE_LUMA_LEVEL, SYS_525_LINE, LUMA_LEVEL_NTSC/**/},
    {TVE_ADJ_COMPOSITE_CHRMA_LEVEL, SYS_625_LINE, CHRMA_LEVEL_PAL/**/}, {TVE_ADJ_COMPOSITE_CHRMA_LEVEL, SYS_525_LINE, CHRMA_LEVEL_NTSC/**/},
    {TVE_ADJ_PHASE_COMPENSATION, SYS_625_LINE, 0x21f0}, {TVE_ADJ_PHASE_COMPENSATION, SYS_525_LINE, 0x3000},
    {TVE_ADJ_VIDEO_FREQ_RESPONSE, SYS_625_LINE, FREQ_RESPONSE_PAL/**/}, {TVE_ADJ_VIDEO_FREQ_RESPONSE, SYS_525_LINE, FREQ_RESPONSE_NTSC/**/}, 
};

__MAYBE_UNUSED__ static struct tve_adjust tve_adjust_table_adv[] = {
    {TVE_ADJ_ADV_PEDESTAL_ONOFF, SYS_625_LINE, 0},              {TVE_ADJ_ADV_PEDESTAL_ONOFF, SYS_525_LINE, 1},
    {TVE_ADJ_ADV_COMPONENT_LUM_LEVEL, SYS_625_LINE, 0x52},      {TVE_ADJ_ADV_COMPONENT_LUM_LEVEL, SYS_525_LINE, 0x4c},
    {TVE_ADJ_ADV_COMPONENT_CHRMA_LEVEL, SYS_625_LINE, 0x63},    {TVE_ADJ_ADV_COMPONENT_CHRMA_LEVEL, SYS_525_LINE, 0x50},
    {TVE_ADJ_ADV_COMPONENT_PEDESTAL_LEVEL, SYS_625_LINE, 0xb},  {TVE_ADJ_ADV_COMPONENT_PEDESTAL_LEVEL, SYS_525_LINE, 0xb},
    {TVE_ADJ_ADV_COMPONENT_SYNC_LEVEL, SYS_625_LINE, 0x4},      {TVE_ADJ_ADV_COMPONENT_SYNC_LEVEL, SYS_525_LINE, 0x4},
    {TVE_ADJ_ADV_RGB_R_LEVEL, SYS_625_LINE, 0x47},              {TVE_ADJ_ADV_RGB_R_LEVEL, SYS_525_LINE, 0x49},
    {TVE_ADJ_ADV_RGB_G_LEVEL, SYS_625_LINE, 0x47},              {TVE_ADJ_ADV_RGB_G_LEVEL, SYS_525_LINE, 0x49},
    {TVE_ADJ_ADV_RGB_B_LEVEL, SYS_625_LINE, 0x47},              {TVE_ADJ_ADV_RGB_B_LEVEL, SYS_525_LINE, 0x49},
    {TVE_ADJ_ADV_COMPOSITE_PEDESTAL_LEVEL, SYS_625_LINE, 0x0},  {TVE_ADJ_ADV_COMPOSITE_PEDESTAL_LEVEL, SYS_525_LINE, 0x2b},
    {TVE_ADJ_ADV_COMPOSITE_SYNC_LEVEL, SYS_625_LINE, 0x4},      {TVE_ADJ_ADV_COMPOSITE_SYNC_LEVEL, SYS_525_LINE, 0x2},
};

//for de_o
static struct tve_adjust g_sd_tve_adjust_table[] = {
    {TVE_ADJ_COMPOSITE_Y_DELAY, SYS_625_LINE, 1}, {TVE_ADJ_COMPOSITE_Y_DELAY, SYS_525_LINE, 1},
    {TVE_ADJ_COMPOSITE_C_DELAY, SYS_625_LINE, 1}, {TVE_ADJ_COMPOSITE_C_DELAY, SYS_525_LINE, 1},
    {TVE_ADJ_COMPONENT_Y_DELAY, SYS_625_LINE, 4}, {TVE_ADJ_COMPONENT_Y_DELAY, SYS_525_LINE, 4},
    {TVE_ADJ_COMPONENT_CB_DELAY, SYS_625_LINE, 3}, {TVE_ADJ_COMPONENT_CB_DELAY, SYS_525_LINE, 3},
    {TVE_ADJ_COMPONENT_CR_DELAY, SYS_625_LINE, 1}, {TVE_ADJ_COMPONENT_CR_DELAY, SYS_525_LINE, 1},
    {TVE_ADJ_BURST_LEVEL_ENABLE, SYS_625_LINE, 1}, {TVE_ADJ_BURST_LEVEL_ENABLE, SYS_525_LINE, 0},
    {TVE_ADJ_BURST_CB_LEVEL, SYS_625_LINE, CB_LEVEL_PAL_SD/**/}, {TVE_ADJ_BURST_CB_LEVEL, SYS_525_LINE, CB_LEVEL_NTSC_SD/**/},
    {TVE_ADJ_BURST_CR_LEVEL, SYS_625_LINE, CR_LEVEL_PAL_SD/**/}, {TVE_ADJ_BURST_CR_LEVEL, SYS_525_LINE, CR_LEVEL_NTSC_SD/**/},
    {TVE_ADJ_COMPOSITE_LUMA_LEVEL, SYS_625_LINE, LUMA_LEVEL_PAL_SD/**/}, {TVE_ADJ_COMPOSITE_LUMA_LEVEL, SYS_525_LINE, LUMA_LEVEL_NTSC_SD/**/},
    {TVE_ADJ_COMPOSITE_CHRMA_LEVEL, SYS_625_LINE, CHRMA_LEVEL_PAL_SD/**/}, {TVE_ADJ_COMPOSITE_CHRMA_LEVEL, SYS_525_LINE, CHRMA_LEVEL_NTSC_SD/**/},
    {TVE_ADJ_PHASE_COMPENSATION, SYS_625_LINE, 0x3d0}, {TVE_ADJ_PHASE_COMPENSATION, SYS_525_LINE, 0x5b0},
    {TVE_ADJ_VIDEO_FREQ_RESPONSE, SYS_625_LINE, FREQ_RESPONSE_PAL_SD/**/}, {TVE_ADJ_VIDEO_FREQ_RESPONSE, SYS_525_LINE, FREQ_RESPONSE_NTSC_SD/**/}, 
};



static struct tve_adjust tve_sd_adjust_table_adv[] = {
    {TVE_ADJ_ADV_PEDESTAL_ONOFF, SYS_625_LINE, 0},              {TVE_ADJ_ADV_PEDESTAL_ONOFF, SYS_525_LINE, 1},
    {TVE_ADJ_ADV_COMPONENT_LUM_LEVEL, SYS_625_LINE, 0x53},      {TVE_ADJ_ADV_COMPONENT_LUM_LEVEL, SYS_525_LINE, 0x4f},
    {TVE_ADJ_ADV_COMPONENT_CHRMA_LEVEL, SYS_625_LINE, 0x51},    {TVE_ADJ_ADV_COMPONENT_CHRMA_LEVEL, SYS_525_LINE, 0x51},
    {TVE_ADJ_ADV_COMPONENT_PEDESTAL_LEVEL, SYS_625_LINE, 0x0},  {TVE_ADJ_ADV_COMPONENT_PEDESTAL_LEVEL, SYS_525_LINE, 0x9},
    {TVE_ADJ_ADV_COMPONENT_SYNC_LEVEL, SYS_625_LINE, 0x0},      {TVE_ADJ_ADV_COMPONENT_SYNC_LEVEL, SYS_525_LINE, 0x4},
    {TVE_ADJ_ADV_RGB_R_LEVEL, SYS_625_LINE, 0x8f},              {TVE_ADJ_ADV_RGB_R_LEVEL, SYS_525_LINE, 0x92},
    {TVE_ADJ_ADV_RGB_G_LEVEL, SYS_625_LINE, 0x8e},              {TVE_ADJ_ADV_RGB_G_LEVEL, SYS_525_LINE, 0x91},
    {TVE_ADJ_ADV_RGB_B_LEVEL, SYS_625_LINE, 0x8e},              {TVE_ADJ_ADV_RGB_B_LEVEL, SYS_525_LINE, 0x91},
    {TVE_ADJ_ADV_COMPOSITE_PEDESTAL_LEVEL, SYS_625_LINE, 0x0},  {TVE_ADJ_ADV_COMPOSITE_PEDESTAL_LEVEL, SYS_525_LINE, 0x2b},
    {TVE_ADJ_ADV_COMPOSITE_SYNC_LEVEL, SYS_625_LINE, 0x0},      {TVE_ADJ_ADV_COMPOSITE_SYNC_LEVEL, SYS_525_LINE, 0x5},
    {TVE_ADJ_ADV_PLUG_OUT_EN, SYS_625_LINE, 0x0},               {TVE_ADJ_ADV_PLUG_OUT_EN, SYS_525_LINE, 0x0},
    {TVE_ADJ_ADV_PLUG_DETECT_LINE_CNT_SD, SYS_625_LINE, 0x0},      {TVE_ADJ_ADV_PLUG_DETECT_LINE_CNT_SD, SYS_525_LINE, 0x0},
    {TVE_ADJ_ADV_PLUG_DETECT_AMP_ADJUST_SD, SYS_625_LINE, 0x0},    {TVE_ADJ_ADV_PLUG_DETECT_AMP_ADJUST_SD, SYS_525_LINE, 0x0},
};

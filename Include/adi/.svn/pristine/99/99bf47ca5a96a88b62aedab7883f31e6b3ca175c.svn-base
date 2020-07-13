
#ifndef _ADI_DEMUX_H_
#define _ADI_DEMUX_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define ADIDEMUX_NOT_CONNECTED_ID			(0xFFFFFFFF)		// 未和任何Demux连接的TunerId

enum
{
	ADIDEMUX_ERROR_BAD_PARAMETER = ADI_DEMUX_ERROR_BASE,
	ADIDEMUX_ERROR_FEATURE_NOT_SUPPORTED,
	ADIDEMUX_ERROR_UNKNOWN_ERROR,
	ADIDEMUX_ERROR_DEVICE_BUSY,
	ADIDEMUX_ERROR_NO_MEMORY
};

/*DEMUX支持的容器注入类型*/
typedef enum
{
	EM_ADI_DEMUX_INJECT_AVI = 1 << 0,       // 支持AVI类型数据注入
	EM_ADI_DEMUX_INJECT_RM = 1 << 1,		// 支持RM类型数据注入
	EM_ADI_DEMUX_INJECT_RMVB = 1 << 2,		// 支持RMVB类型的数据注入
	EM_ADI_DEMUX_INJECT_TS = 1 << 3        // 支持TS类型的数据注入

}ADIDEMUXContainerType_E;

ADI_Error_Code ADIDEMUXGetCount( int * pnDemuxCount );

ADI_Error_Code ADIDEMUXConnectTuner( unsigned int dwTunerId, int nDemuxIndex );

ADI_Error_Code ADIDEMUXDisconnectTuner( unsigned int dwTunerId, int nDemuxIndex );

ADI_Error_Code ADIDEMUXGetAllFilterCount(int nDemuxIndex, int * pnFilterCount);

ADI_Error_Code ADIDEMUXGetFreeFilterCount(int nDemuxIndex, int * pnFreeFilterCount);


#ifdef  __cplusplus
}
#endif


#endif


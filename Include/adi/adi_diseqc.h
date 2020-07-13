
#ifndef _ADI_DISEQC_H_
#define _ADI_DISEQC_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef __cplusplus
extern "C" 
{
#endif

typedef enum 
{
	EM_ADIDISEQC_EASTERN,	// 向东转动
	EM_ADIDISEQC_WESTERN	// 向西转动
}ADIRotateDirection_E;

typedef struct 
{
	double ldSatLongitude; // 卫星经度
	double ldLongitude;    // 指定经度
	double ldLatitude;     // 指定纬度
	int    reserved[2];	   // 保留参数
}ADISatLocationInfo_S;

//指定方向转动ucTime时间 //ucTime:1-127(s)
ADI_Error_Code ADIDSC12RotateTimes(unsigned int dwTunerId, ADIRotateDirection_E eDirection, unsigned char ucTime);


/*按指定方向转动指定的弧度*/ //微调
ADI_Error_Code ADIDSC12RotateCycles (unsigned int dwTunerId, ADIRotateDirection_E eDirection,unsigned char ucCycles);

/*将当前位置保存为第XX个卫星位置*/
ADI_Error_Code ADIDSC12StorePosition (unsigned int dwTunerId, unsigned char ucPosition);

/*转到卫星的第XX个位*/
ADI_Error_Code ADIDSC12GotoPosition (unsigned int dwTunerId, unsigned char ucPosition);

/*转到刻度为0的位*/
ADI_Error_Code ADIDSC12ResetPosition (unsigned int dwTunerId);

/*电机转动直到最东边(最西边)限制位置或接收到STOP命令才停止转动*/
ADI_Error_Code ADIDSC12RotateWithoutStop (unsigned int dwTunerId, unsigned char ucDirection);

/*停止电机转动*/
ADI_Error_Code ADIDSC12RotateStop (unsigned int dwTunerId);

/*取消转动范围的限制(最东边和最西边)*/
ADI_Error_Code ADIDSC12DisableLimit (unsigned int dwTunerId);

/*设置转动范围的限制(最东边和最西边)*/
ADI_Error_Code ADIDSC12SetLimit (unsigned int dwTunerId, unsigned char ucDirection);

/*根据第XX个卫星的偏移同步所有卫星的位置*/ //用法?
ADI_Error_Code ADIDSC12AdjustTAB (unsigned int dwTunerId, unsigned char ucPosition);

/*转动到指定角度(For STAB USALS Motor)*/ //600=60°(东转60°)   -600=-60°(西转60°)
ADI_Error_Code ADIDSC12GotoSTABPosition(unsigned int dwTunerId, double dlAngle);

/*根据经纬度获取转动角度(For STAB USALS Motor)*/
ADI_Error_Code ADIDSC12GetAntennaAngle(double dlSatLongitude, double dlMyLongitude, double dlMyLatitude, double *pdlAngle);

/*调整马达到指定的经纬度*/
ADI_Error_Code ADIDSC12TurnSateWithUsals(unsigned int dwTunerId, const ADISatLocationInfo_S *psSatLocationInfo);

#ifdef __cplusplus
}
#endif

#endif


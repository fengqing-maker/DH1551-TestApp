
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
	EM_ADIDISEQC_EASTERN,	// ��ת��
	EM_ADIDISEQC_WESTERN	// ����ת��
}ADIRotateDirection_E;

typedef struct 
{
	double ldSatLongitude; // ���Ǿ���
	double ldLongitude;    // ָ������
	double ldLatitude;     // ָ��γ��
	int    reserved[2];	   // ��������
}ADISatLocationInfo_S;

//ָ������ת��ucTimeʱ�� //ucTime:1-127(s)
ADI_Error_Code ADIDSC12RotateTimes(unsigned int dwTunerId, ADIRotateDirection_E eDirection, unsigned char ucTime);


/*��ָ������ת��ָ���Ļ���*/ //΢��
ADI_Error_Code ADIDSC12RotateCycles (unsigned int dwTunerId, ADIRotateDirection_E eDirection,unsigned char ucCycles);

/*����ǰλ�ñ���Ϊ��XX������λ��*/
ADI_Error_Code ADIDSC12StorePosition (unsigned int dwTunerId, unsigned char ucPosition);

/*ת�����ǵĵ�XX��λ*/
ADI_Error_Code ADIDSC12GotoPosition (unsigned int dwTunerId, unsigned char ucPosition);

/*ת���̶�Ϊ0��λ*/
ADI_Error_Code ADIDSC12ResetPosition (unsigned int dwTunerId);

/*���ת��ֱ�����(������)����λ�û���յ�STOP�����ֹͣת��*/
ADI_Error_Code ADIDSC12RotateWithoutStop (unsigned int dwTunerId, unsigned char ucDirection);

/*ֹͣ���ת��*/
ADI_Error_Code ADIDSC12RotateStop (unsigned int dwTunerId);

/*ȡ��ת����Χ������(��ߺ�������)*/
ADI_Error_Code ADIDSC12DisableLimit (unsigned int dwTunerId);

/*����ת����Χ������(��ߺ�������)*/
ADI_Error_Code ADIDSC12SetLimit (unsigned int dwTunerId, unsigned char ucDirection);

/*���ݵ�XX�����ǵ�ƫ��ͬ���������ǵ�λ��*/ //�÷�?
ADI_Error_Code ADIDSC12AdjustTAB (unsigned int dwTunerId, unsigned char ucPosition);

/*ת����ָ���Ƕ�(For STAB USALS Motor)*/ //600=60��(��ת60��)   -600=-60��(��ת60��)
ADI_Error_Code ADIDSC12GotoSTABPosition(unsigned int dwTunerId, double dlAngle);

/*���ݾ�γ�Ȼ�ȡת���Ƕ�(For STAB USALS Motor)*/
ADI_Error_Code ADIDSC12GetAntennaAngle(double dlSatLongitude, double dlMyLongitude, double dlMyLatitude, double *pdlAngle);

/*������ﵽָ���ľ�γ��*/
ADI_Error_Code ADIDSC12TurnSateWithUsals(unsigned int dwTunerId, const ADISatLocationInfo_S *psSatLocationInfo);

#ifdef __cplusplus
}
#endif

#endif


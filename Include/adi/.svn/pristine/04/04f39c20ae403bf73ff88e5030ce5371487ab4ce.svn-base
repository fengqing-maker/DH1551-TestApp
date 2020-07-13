
#ifndef _ADI_SECTION_H_
#define _ADI_SECTION_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif


    /*解复用相关错误代码值*/
    enum
    {
        ADISECTION_ERROR_BAD_PARAMETER = ADI_SECTION_ERROR_BASE,
        ADISECTION_ERROR_FEATURE_NOT_SUPPORTED,
        ADISECTION_ERROR_UNKNOWN_ERROR,
        ADISECTION_ERROR_NO_MEMORY,
        ADISECTION_ERROR_INVALID_HANDLE,
        ADISECTION_ERROR_INVALID_STATUS,
        ADISECTION_ERROR_NO_FREE_FILTER
    };


    /*filter长度，不包含section中的length字段*/
#define ADISECTION_FILTER_LEN 16

    /*Section回调数据类型枚举*/
    typedef enum
    {
        EM_ADI_REQ_SECTION_DATA,		// 表示一个PSI、SI数据包
        EM_ADI_REQ_PES_DATA,			// 表示一个PES数据包(除音视频外要求整包数据)
        EM_ADI_REQ_RAW_DATA			    // 表示一个RAW数据包
    }ADISECTIONRequestType_E;


    typedef struct
    {
        unsigned char match [ ADISECTION_FILTER_LEN ];	    // 匹配字段
        unsigned char mask [ ADISECTION_FILTER_LEN ];	    // 关注字段
        unsigned char negate [ ADISECTION_FILTER_LEN ];	// 取反字段
    }ADIFILTERMatchMask_S;


    /*Filter信息，该信息描述所要请求的数据的特征*/
    typedef struct
    {
        ADISECTIONRequestType_E		    m_eReqType;	     // 指定请求类型，请参见ADISECTIONRequestType_E
        int 							m_nDemuxID;	     //指定Demux Index
        int                          	m_nPID;		     // 指定请求数据的pid
        ADI_BOOL                        m_bCRCCheck;     // 是否进行CRC检查，注意：对于待申请数据(PSI/SI/私有数据)在数字电视相关标准文档中已明确没有CRC字段的情况，要求中间件设置该项为ADI_FALSE，并且实现者也无需关注该项为ADI_TRUE情况下的实现机制；
        unsigned int                    m_unBufSize;     
		ADI_HANDLE                      m_hSignal;       //ADIFILTERAllocateSignal
        int                             m_nReserved;
    } ADISECTIONRequestInfo_S;

    typedef struct
    {
        ADI_HANDLE        m_hFilterHandle;
        void *	          m_pvUsrData;
        unsigned char *   m_pucSection;
        unsigned int      m_unSectionLen;
        unsigned int      m_unSectActualLen;

    }ADIFILTERData_S;


	ADI_Error_Code ADIFILTERAllocateSignal ( ADI_HANDLE * phFilterSignal );

    ADI_Error_Code ADIFILTERAllocate ( const ADISECTIONRequestInfo_S * psRequestInfo, const void * pvUserData, ADI_HANDLE * phFilterHandle );

    ADI_Error_Code ADIFILTERSet ( ADI_HANDLE hFilterHandle, const ADIFILTERMatchMask_S * psMMFilter );

    ADI_Error_Code ADIFILTERStart ( ADI_HANDLE hFilterHandle );

    ADI_Error_Code ADIFILTERStop ( ADI_HANDLE hFilterHandle );

    ADI_Error_Code ADIFILTERFree ( ADI_HANDLE hFilterHandle );

    ADI_Error_Code ADIFILTERWaitDataArrived ( ADI_HANDLE hFilterSignal, unsigned int unTimeOut);

    ADI_Error_Code ADIFILTERWaitDataAbort ( ADI_HANDLE hFilterSignal );

    ADI_Error_Code ADIFILTERReadData ( ADI_HANDLE hFilterSignal, ADIFILTERData_S pstFilterData [ ], unsigned int unFDMaxCount, unsigned int *punFDActalCount );



#ifdef  __cplusplus
}
#endif


#endif



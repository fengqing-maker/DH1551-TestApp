#include <s3_vd.h>
#include <s3_cadrv.h>
#include "ali_vd_drv.h"

ia_result CA_DRV_Message( ca_drv_message_type_e eOpcode, ia_word16 wOpSeqNo, ia_word16 wLength,
	void *pvMessage )
{
	ia_result ret = IA_SUCCESS;
	
	return ret;

}
void CA_DRV_FatalError( ia_word16 wError )
{

	DEBUG_S3_VD_PRINTF("enter fatal error! \n");

}




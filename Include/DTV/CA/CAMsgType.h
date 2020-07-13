/*
 * CAMsgType.h
 *
 *  Created on: 2015-7-2
 *      Author: timothy.liao
 */

#ifndef CAMSGTYPE_H_
#define CAMSGTYPE_H_


enum CAMsgType{
	E_CAMSG_INVALID = 0,
	E_CAMSG_PGLOCK,
	E_CAMSG_PINCODE_OK,
	E_CAMSG_PINCODE_ERROR,
	E_CAMSG_PVRRECORD_FP,
	E_CAMSG_PVRRECORD_ATTRIBMAIL,
	E_CAMSG_PVRRECORD_MSGMAIL,
	E_CAMSG_PVRRECORD_CCI,
	E_CAMSG_PVRRECORD_TRICKMODE,
	E_CAMSG_PVRRECORD_METADATA,
	E_CAMSG_PVRRECORD_EXPIRYTIME,
	E_CAMSG_PVRRECORD_NONPVRENABLE,
	E_CAMSG_PGUNLOCK,
    E_CAMSG_PVRRECORD_ECMDATA,
    E_CAMSG_PVRSUBMIT_METADATA,
    E_CAMSG_PVRSUBMIT_ECMDATA,
    E_CAMSG_PVRMODIFY_METADATA,
    E_CAMSG_PLAYBACK_NORIGHT,
    E_CAMSG_PLAYBACK_RIGHTOK,
	E_CAMSG_MAX
};



#endif /* CAMSGTYPE_H_ */

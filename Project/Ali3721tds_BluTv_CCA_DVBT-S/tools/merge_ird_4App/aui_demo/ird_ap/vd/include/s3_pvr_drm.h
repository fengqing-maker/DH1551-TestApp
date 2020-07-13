/**
 * $Id: s3_pvr_drm.h,v 1.5 2008/06/05 09:17:24 ehietbrink Exp $
 *
 * Copyright 2005-2008 Irdeto Access B.V.
 *
 * This file and the information contained herein are the subject of copyright
 * and intellectual property rights under international convention. All rights
 * reserved. No part of this file may be reproduced, stored in a retrieval
 * system or transmitted in any form by any means, electronic, mechanical or
 * optical, in whole or in part, without the prior written permission of Irdeto
 * Access B.V.
 *
 * This file is part of the SoftCell 3 Integration library.
 **/

/**
 * This file is part of the 'CA-Task API'.
 **/

#ifndef S3_PVR_DRM_H
#define S3_PVR_DRM_H

#define MSG_SM_DRM_RIGHTS_RECORD_ID_INVALID    0xFFFFFFFF /*Fit ia_word32.*/
#define MSG_SM_DRM_SEQUENCE_RECORD_ID_INVALID  0xFFFFFFFF /*Fit ia_word32.*/


typedef enum
{
	MSG_SM_DRM_SESSION_SUBTYPE_PVR_PHASE_3 = 3
} msg_sm_drm_session_subtype_e;


typedef enum
{
	MSG_SM_DRM_PVR_PURPOSE_TIMESHIFT = 1,
	MSG_SM_DRM_PVR_PURPOSE_PERMANENT
} msg_sm_drm_pvr_purpose_e;


typedef enum
{
	MSG_SM_DRM_PVR_ACTION_RECORD = 1,
	MSG_SM_DRM_PVR_ACTION_PLAYBACK
} msg_sm_drm_pvr_action_e;


typedef struct
{
	msg_sm_drm_session_subtype_e  eSessionSubtype;
	msg_sm_drm_pvr_purpose_e      ePvrPurpose;
	msg_sm_drm_pvr_action_e       ePvrAction;
} msg_sm_drm_define_st;


typedef struct
{
	ia_word16  wDescrambleServiceHandle;
	ia_bool    fFtaCheckAnySector;
	ia_byte    bFtaCheckSectorNr;
	ia_bool    fChainRecordings;
	ia_word32  wChainingSessionResourceId;
	ia_word32  wChainingRightsRecordId;
	ia_word32  wChainingSequenceRecordId;
} msg_sm_drm_define_record_st;


typedef enum
{
	MSG_SM_PLAYBACK_DIRECTION_FORWARD = 1,
	MSG_SM_PLAYBACK_DIRECTION_REWIND
} msg_sm_drm_playback_direction_e;


typedef struct
{
	ia_word32                        wRightsRecordId;
	ia_word32                        wSequenceRecordId;
	ia_bool                          fPeekRightsOnly;
	msg_sm_drm_playback_direction_e  ePlaybackDirection;
} msg_sm_drm_define_playback_st;


typedef struct
{
	ia_word32  wRightsRecordId;
	ia_word32  wSequenceRecordId;
	ia_bool    fRecordFlagsUpdated;
	ia_bool    fRightsRecordUpdated;
	ia_bool    fSequenceRecordUpdated;
} msg_sm_drm_status_st;


typedef struct
{
	ia_bool   fNonPVRable;
	ia_bool   fMustExpire;
} msg_sm_drm_record_flags_st;

typedef enum
{
	MSG_SM_DRM_COPYCONTROL_COPYFREELY = 0,
	MSG_SM_DRM_COPYCONTROL_NOFURTHERCOPY,
	MSG_SM_DRM_COPYCONTROL_COPYONCE,
	MSG_SM_DRM_COPYCONTROL_COPYNEVER
} msg_sm_drm_copycontrol_e;


typedef struct
{
	ia_word32                 wCRID;
	msg_sm_drm_copycontrol_e  eCopyControl;
	ia_word32                 wPlaybackWindowStartTime;
	ia_word32                 wPlaybackWindowDuration;
	ia_byte                   bNrOfPlaybacks;
} msg_sm_drm_rights_record_st;

/*It is only used for supporting multi slot pvr, to display if the session management of current smartcard is active for the recording or playback.
at the same time, only one card is active to do record or palyback drm service*/
typedef struct
{
  /*When flag is IA_TRUE, the session management data is valid for current recording or playback.*/
  ia_bool		fActive;
  /*To indicate the smartcard resource id for current recording or playback.*/
  vd_rsc_id	wSmartcardResourceID;
}msg_sm_drm_smartcard_info_st;

/*SCR#249328: [Whole Home Networking] SoftCell shall play back CCA format metadata*/
typedef struct
{
	ia_word32 wMetaDataLength;
}msg_sm_cca_metadata_define_st;

typedef struct
{
	ia_bool		fCopyControlInvalid;
	msg_sm_drm_copycontrol_e  eCopyControl;
}msg_sm_cca_drm_status_st;



#endif /* S3_PVR_DRM_H. */

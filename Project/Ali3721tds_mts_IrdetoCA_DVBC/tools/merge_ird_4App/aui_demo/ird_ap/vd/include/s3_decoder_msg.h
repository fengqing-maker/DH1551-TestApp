/**
 * $Id: s3_decoder_msg.h,v 1.5 2011/04/21 06:08:07 jcao Exp $
 *
 * Copyright	2001-2006 Irdeto Access B.V.
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
 * This file is part of the 'Host CA-Task driver'.
 **/

#ifndef S3_DECODER_MSG_H
#define S3_DECODER_MSG_H

#include "s3_cadrv.h"

typedef struct
{
	ia_word16  wServiceHandle;
	ia_word16  wMessageLength;
} msg_decoder_data_st;

#endif /* S3_DECODER_MSG_H. */

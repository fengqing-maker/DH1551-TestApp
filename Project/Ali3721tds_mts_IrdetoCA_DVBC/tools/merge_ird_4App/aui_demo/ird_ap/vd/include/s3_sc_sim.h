/**
 * $Id: s3_sc_sim.h,v 1.5 2005/12/23 15:08:33 ehietbrink Exp $
 *
 * Copyright © 2005 Irdeto Access B.V.
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

#include "s3_vddd.h"
 
void s3_sc_sim_GetLoaderInfo(vd_loader_secure_chip_st *pstCsInfo);
void s3_sc_sim_SetSessionKey(ia_word16 wKeyLength, ia_byte *pbKey);
void s3_sc_sim_SetKey(ia_word16 wESPid, vd_dd_key_st *pstKey, ia_byte *pbKeyOut);
void s3_sc_sim_GetCardSessionKey(ia_word16 wKeyLength, ia_byte *pbKey);
void s3_sc_sim_EncryptCodeWords( ia_word16 wDataReadSize, ia_byte *pbRead, ia_bool fEncrypt );
void s3_sc_sim_GetUniqueKey(ia_word16 wKeyLength, ia_byte *pbKey);
void s3_sc_sim_EncryptWithUniqueKey(ia_word16 wKeyLength, ia_byte *pbDataIn, ia_byte *pbDataOut);
void s3_sc_sim_EncryptWithSessionKey(ia_word16 wKeyLength, ia_byte *pbDataIn, ia_byte *pbDataOut);

extern ia_int8 *s3_sc_sim_GetTime(ia_int8 *abTime);

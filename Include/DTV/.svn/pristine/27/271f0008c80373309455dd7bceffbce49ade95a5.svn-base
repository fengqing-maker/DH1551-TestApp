/*
 * CAGlueInterface.h
 *
 *  Created on: 2015-5-7
 *      Author: timothy.liao
 */

#ifndef CAGLUEINTERFACE_H_
#define CAGLUEINTERFACE_H_
#include "CANotify.h"
#include "CAMsgType.h"
#include "CAPipeType.h"

class CAGlueInterface
{
public:
	CAGlueInterface();
	virtual ~CAGlueInterface();

public:

	virtual unsigned int AddCANotify(CANotify* pPlayerNotify) = 0;
	virtual unsigned int RemoveCANotify(CANotify* pPlayerNotify) = 0;

	virtual unsigned int SetCABouquetID(unsigned short usBouquetID) = 0;

	virtual void CAMessageNotify(CAMsgType eCAMsg, void* pvParam1, void* pvParam2) = 0;
};

#endif /* DATABASECONTAINERPLAYERCAINTERFACE_H_ */

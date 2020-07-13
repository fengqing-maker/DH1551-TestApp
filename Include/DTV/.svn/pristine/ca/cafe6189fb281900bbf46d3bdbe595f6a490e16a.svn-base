/*
 * HDMIConnnectionInterface.h
 *
 *  Created on: 2015-10-13
 *      Author: Timtohy
 */

#ifndef HDMICONNECTIONINTERFACE_H_
#define HDMICONNECTIONINTERFACE_H_
#include "HDMICECNotify.h"
class HDMIConnectionInterface
{

public:

	HDMIConnectionInterface();
	virtual ~HDMIConnectionInterface();

public:

	virtual void HDMICECDisable() = 0;
	virtual void HDMICECEnable() = 0;

	virtual unsigned int HDMICECSetDeviceOSDName(char *pacName, unsigned int unLength) = 0;
	virtual unsigned int HDMICECGetPowerStatus() = 0;
	virtual unsigned int HDMICECGetVersion() = 0;

	virtual void HDMICECStandby() = 0;
	virtual void HDMICECOneTouchPlay() = 0;
	virtual void AddHDMICECNotify(HDMICECNotify *pHDMICECNotify) = 0;
};

#endif /* QUAR7SDDQUARLED_H_ */

#ifndef HDMICECNOTIFY_H
#define HDMICECNOTIFY_H
#include "adi_hdmi_cec.h"

class HDMICECNotify
{

public:

    HDMICECNotify ( );
    virtual ~HDMICECNotify ( );

public:

    virtual void SendCommandToSTB ( ADIHDMICECOpCode_E eHDMICECOpCode_E, void *pCommandData ) = 0;
	virtual unsigned int AddMenuLanguageCode(char *pcLanguageCode, unsigned int unLength) = 0;
};

#endif

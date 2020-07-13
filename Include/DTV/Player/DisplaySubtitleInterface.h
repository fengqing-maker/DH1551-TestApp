#ifndef DISPLAYSUBTITLEINTERFACE_H_
#define DISPLAYSUBTITLEINTERFACE_H_
#include "adi_typedef.h"

class DisplaySubtitleInterface
{

public:

    DisplaySubtitleInterface ( );
    virtual ~DisplaySubtitleInterface ( );

public:

	virtual void Show ( ADI_HANDLE hSourceSurface, int nX, int nY, unsigned int unWidth, unsigned int unHeight ) = 0;
    virtual void Clear ( int nX, int nY, unsigned int unWidth, unsigned int unHeight ) = 0;
};

#endif /* DISPLAYSUBTITLEINTERFACE_H_ */

/*
 * CheckAudioPIDSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKAUDIOPIDSPEC_H_
#define CHECKAUDIOPIDSPEC_H_

#include "CheckServiceSpec.h"

class CheckAudioPIDSpec : public CheckServiceSpec
{

public:

    CheckAudioPIDSpec ( unsigned short usAudioPID );
	virtual ~CheckAudioPIDSpec( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:

    unsigned short m_usAudioPID;

};

#endif /* CHECKAUDIOPIDSPEC_H_ */

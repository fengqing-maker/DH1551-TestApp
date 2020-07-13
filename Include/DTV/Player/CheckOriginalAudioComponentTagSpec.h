/*
* CheckOriginalAudioComponentTagSpec.h
*
*  Created on: 2016-3-11
*      Author: Timothy.Liao
*/

#ifndef CHECKORIGINALAUDIOCOMPONENTTAGSPEC_H_
#define CHECKORIGINALAUDIOCOMPONENTTAGSPEC_H_
#include "CheckOriginalAudioComponentSpec.h"

class CheckOriginalAudioComponentTagSpec : public CheckOriginalAudioComponentSpec
{

public:

    CheckOriginalAudioComponentTagSpec ( unsigned char ucComponentTag );
    virtual ~CheckOriginalAudioComponentTagSpec ( );

public:

    unsigned int IsOriginalAudioComponent ( ComponentInterface * pAudioComponent );
    CheckOriginalAudioComponentSpec * ConstructSimilarCheckOriginalAudioComponentSpec ( );

private:

    unsigned char m_ucComponentTag;
};

#endif /* CHECKORIGINALAUDIOCOMPONENTTAGSPEC_H_ */
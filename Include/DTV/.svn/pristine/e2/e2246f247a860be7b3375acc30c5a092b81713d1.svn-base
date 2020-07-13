/*
* AudioOriginalAudioPrioritySpec.h
*
*  Created on: 2016-3-11
*      Author: Timothy.Liao
*/

#ifndef AUDIOORIGINALAUDIOPRIORITYSPEC_H_
#define AUDIOORIGINALAUDIOPRIORITYSPEC_H_
#include "AudioComponentPrioritySpec.h"
#include "CheckOriginalAudioComponentSpec.h"

class AudioOriginalAudioPrioritySpec : public AudioComponentPrioritySpec
{

public:

    AudioOriginalAudioPrioritySpec ( CheckOriginalAudioComponentSpec * pCheckOriginalAudioComponentSpec );
    virtual ~AudioOriginalAudioPrioritySpec ( );

public:

    unsigned int GetPriorityComponents ( ServiceInterface* pServiceInterface, vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > & m_OutputComponent );
    AudioComponentPrioritySpec* ConstructSimilarAudioComponentPrioritySpec ( );

private:

    CheckOriginalAudioComponentSpec * m_pCheckOriginalAudioComponentSpec;
};

#endif /* AUDIOORIGINALAUDIOPRIORITYSPEC_H_ */
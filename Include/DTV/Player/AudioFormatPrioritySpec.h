/*
* AudioFormatPrioritySpec.h
*
*  Created on: 2016-3-11
*      Author: Timothy.Liao
*/

#ifndef AUDIOFORMATPRIORITYSPEC_H_
#define AUDIOFORMATPRIORITYSPEC_H_

#include "AudioComponentPrioritySpec.h"
#include "AudioFormat.h"

class AudioFormatPrioritySpec : public AudioComponentPrioritySpec
{

public:

    AudioFormatPrioritySpec ( AudioFormat eAudioFormat );
    virtual ~AudioFormatPrioritySpec ( );

public:

    unsigned int GetPriorityComponents ( ServiceInterface* pServiceInterface, vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > & m_OutputComponent );
    AudioComponentPrioritySpec* ConstructSimilarAudioComponentPrioritySpec ( );

private:

    AudioFormat m_AudioFormat;
};

#endif /* AUDIOFORMATPRIORITYSPEC_H_ */
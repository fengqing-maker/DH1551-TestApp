/*
* AudioTypePrioritySpec.h
*
*  Created on: 2016-3-11
*      Author: Timothy.Liao
*/

#ifndef AUDIOTYPEPRIORITYSPEC_H_
#define AUDIOTYPEPRIORITYSPEC_H_

#include "AudioComponentPrioritySpec.h"
#include "AudioType.h"

class AudioTypePrioritySpec : public AudioComponentPrioritySpec
{

public:

    AudioTypePrioritySpec ( AudioType eAudioType );
    virtual ~AudioTypePrioritySpec ( );

public:

    unsigned int GetPriorityComponents ( ServiceInterface* pServiceInterface, vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > & m_OutputComponent );
    AudioComponentPrioritySpec* ConstructSimilarAudioComponentPrioritySpec ( );

private:

    AudioType m_AudioType;
};

#endif /* AUDIOTYPEPRIORITYSPEC_H_ */
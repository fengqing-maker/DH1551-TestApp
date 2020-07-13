/*
 * AudioPreviousSelectPrioritySpec.h
 *
 *  Created on: 2016-3-11
 *      Author: Timothy.Liao
 */

#ifndef AUDIOPREVIOUSSELECTPRIORITYSPEC_H_
#define AUDIOPREVIOUSSELECTPRIORITYSPEC_H_

#include "AudioComponentPrioritySpec.h"

class AudioPreviousSelectPrioritySpec : public AudioComponentPrioritySpec
{

public:

    AudioPreviousSelectPrioritySpec ( );
    virtual ~AudioPreviousSelectPrioritySpec ( );

public:

    unsigned int GetPriorityComponents ( ServiceInterface* pServiceInterface, vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > & m_OutputComponent );
    AudioComponentPrioritySpec* ConstructSimilarAudioComponentPrioritySpec ( );
};

#endif /* AUDIOPREVIOUSSELECTPRIORITYSPEC_H_ */

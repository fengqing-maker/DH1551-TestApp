/*
 * NotAudioComponentPrioritySpec.h
 *
 *  Created on: 2016-3-11
 *      Author: Timothy.Liao
 */

#ifndef NOTAUDIOCOMPONENTPRIORITYSPEC_H_
#define NOTAUDIOCOMPONENTPRIORITYSPEC_H_

#include "AudioComponentPrioritySpec.h"

class NotAudioComponentPrioritySpec : public AudioComponentPrioritySpec
{

public:

    NotAudioComponentPrioritySpec ( AudioComponentPrioritySpec * pAudioComponentPrioritySpec );
    virtual ~NotAudioComponentPrioritySpec ( );

public:

    unsigned int GetPriorityComponents ( ServiceInterface* pServiceInterface, vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > & m_OutputComponent );
    AudioComponentPrioritySpec* ConstructSimilarAudioComponentPrioritySpec ( );

private:
    unsigned int CheckComponentInList ( ComponentInterface* pComponent, vector < ComponentInterface* >m_InputComponent );

private:
    AudioComponentPrioritySpec * m_pAudioComponentPrioritySpec;
};

#endif /* NOTAUDIOCOMPONENTPRIORITYSPEC_H_ */

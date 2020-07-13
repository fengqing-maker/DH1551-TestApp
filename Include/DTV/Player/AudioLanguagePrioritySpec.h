/*
* AudioComponentPrioritySpec.h
*
*  Created on: 2016-3-11
*      Author: Timothy.Liao
*/

#ifndef AUDIOLANGUAGEPRIORITYSPEC_H_
#define AUDIOLANGUAGEPRIORITYSPEC_H_

#include "AudioComponentPrioritySpec.h"

class AudioLanguagePrioritySpec : public AudioComponentPrioritySpec
{

public:

    AudioLanguagePrioritySpec ( char acLangaugeCode [ 3 ] );
    virtual ~AudioLanguagePrioritySpec ( );

public:

    unsigned int GetPriorityComponents ( ServiceInterface* pServiceInterface, vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > &m_OutputComponent );
    AudioComponentPrioritySpec* ConstructSimilarAudioComponentPrioritySpec ( );

private:

    char m_acLanguageCode [ 3 ];

};

#endif /* AUDIOLANGUAGEPRIORITYSPEC_H_ */

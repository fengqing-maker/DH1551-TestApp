/*
 * AudioComponentPrioritySpec.h
 *
 *  Created on: 2016-3-11
 *      Author: Timothy.Liao
 */

#ifndef AUDIOCOMPONENTPRIORITYSPEC_H_
#define AUDIOCOMPONENTPRIORITYSPEC_H_

#include "ServiceInterface.h"
#include "ComponentInterface.h"
#include <vector>

using namespace std;
using std::vector;

class AudioComponentPrioritySpec
{

public:

    AudioComponentPrioritySpec ( );
    virtual ~AudioComponentPrioritySpec ( );

public:

    virtual unsigned int GetPriorityComponents ( ServiceInterface* pServiceInterface, vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > & m_OutputComponent ) = 0;
    virtual AudioComponentPrioritySpec* ConstructSimilarAudioComponentPrioritySpec ( ) = 0;
};

#endif /* AUDIOCOMPONENTPRIORITYSPEC_H_ */

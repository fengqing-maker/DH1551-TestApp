/*
* CompositeAudioComponentPrioritySpec.h
*
*  Created on: 2016-3-11
*      Author: Timothy.Liao
*/

#ifndef COMPOSITEAUDIOCOMPONENTPRIORITYSPEC_H_
#define COMPOSITEAUDIOCOMPONENTPRIORITYSPEC_H_

#include "AudioComponentPrioritySpec.h" 
#include <list>

using namespace std;
using std::list;

class CompositeAudioComponentPrioritySpec : public AudioComponentPrioritySpec
{

public:

    CompositeAudioComponentPrioritySpec ( );
    virtual ~CompositeAudioComponentPrioritySpec ( );

public:

    unsigned int AddSpec ( AudioComponentPrioritySpec * pAudioComponentPrioritySpec );
    unsigned int RemoveSpec ( AudioComponentPrioritySpec * pAudioComponentPrioritySpec );

    unsigned int GetPriorityComponents ( ServiceInterface* pServiceInterface, vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > & m_OutputComponent );
    AudioComponentPrioritySpec* ConstructSimilarAudioComponentPrioritySpec ( );

private:

    void CopyComponents ( vector < ComponentInterface* >m_InputComponent, vector < ComponentInterface * > & m_OutputComponent );

private:

    list< AudioComponentPrioritySpec * > m_AudioComponentPrioritySpecList;

};

#endif /* COMPOSITEAUDIOCOMPONENTPRIORITYSPEC_H_ */

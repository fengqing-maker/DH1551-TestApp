/*
 * CheckAudioTypeSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKAUDIOFORMATSPEC_H_
#define CHECKAUDIOFORMATSPEC_H_

#include "CheckServiceSpec.h"
#include "AudioFormat.h"

class CheckAudioFormatSpec : public CheckServiceSpec
{

public:

    CheckAudioFormatSpec ( AudioFormat  enAudioFormat );
    virtual ~CheckAudioFormatSpec ( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:

    AudioFormat m_enAudioFormat;

};

#endif /* CHECKAUDIOTYPESPEC_H_ */

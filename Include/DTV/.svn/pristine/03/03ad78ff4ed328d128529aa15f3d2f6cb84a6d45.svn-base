/*
 * CheckVideoFormatSpec.h
 *
 *  Created on: 2015-10-23
 *      Author: HXC
 */

#ifndef CHECKVIDEOFORMATSPEC_H_
#define CHECKVIDEOFORMATSPEC_H_

#include "CheckServiceSpec.h"
#include "VideoFormat.h"

class CheckVideoFormatSpec : public CheckServiceSpec
{

public:
	
    CheckVideoFormatSpec ( VideoFormat enVideoFormat );
    virtual ~CheckVideoFormatSpec ( );

public:

    unsigned int IsChecked ( ServiceInterface * pServiceInterface );

private:

    VideoFormat m_enVideoFormat;

};

#endif /* CHECKVIDEOFORMATSPEC_H_ */

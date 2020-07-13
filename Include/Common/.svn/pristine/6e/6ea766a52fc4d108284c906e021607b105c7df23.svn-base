/*
* APSemaphore.h
*
*  Created on: 2010-10-7
*      Author: NTT
*/

#ifndef APSEMAPHORE_H_
#define APSEMAPHORE_H_

class APSemaphore
{

public:

    APSemaphore ( unsigned int unCount = 1 );
    virtual ~APSemaphore ( );

public:

    unsigned int Wait ( unsigned int unTimeOut );
    unsigned int Wait ( );

    unsigned int Release ( );

private:

    void * m_hSemaphore;

};

#endif /* APSEMAPHORE_H_ */

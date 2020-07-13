/*
 * APEvent.h
 *
 *  Created on: 2010-10-7
 *      Author: NTT
 */
#ifndef EVENTADA_H_
#define EVENTADA_H_

class APEvent
{

public:

	APEvent( );
	virtual ~APEvent( );

public:

	unsigned int Wait( int nTimeOut );
    unsigned int Wait ( );
	void SetEvent( );
	void ResetEvent( );

private:

	void * m_hEvent;

};

#endif /* EVENTADA_H_ */

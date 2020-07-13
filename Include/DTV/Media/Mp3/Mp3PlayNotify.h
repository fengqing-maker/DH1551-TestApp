
#ifndef MP3PLAYERNNOTIFY_H
#define MP3PLAYERNNOTIFY_H

class Mp3PlayerNotify
{
public:
	Mp3PlayerNotify ( );
	virtual ~Mp3PlayerNotify ( );

public:

	virtual unsigned int Mp3PlaySuccess ( void ) = 0;

	virtual unsigned int Mp3PlayEnd ( void ) = 0;

	virtual unsigned int Mp3PlayErrFormat(void) = 0;

	virtual unsigned int Mp3PlayInvalidFile(void) = 0;

	virtual unsigned int Mp3PlayInterrupt ( void ) = 0;

	virtual unsigned int Mp3PlayFlushFinish ( void ) = 0;

	virtual unsigned int Mp3PlayUnkown ( void ) = 0;
};



#endif

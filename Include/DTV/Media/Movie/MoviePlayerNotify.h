
#ifndef MOVIEPLAYERNOTIFY_H
#define MOVIEPLAYERNOTIFY_H

class MoviePlayerNotify
{
public:
	MoviePlayerNotify ( );
	virtual ~MoviePlayerNotify ( );

public:
	virtual unsigned int FilePlayerBeginOfStream ( void ) = 0;

	virtual unsigned int FilePlayerEndOfStream ( void ) = 0;

	virtual unsigned int FilePlayerShowSubtitle ( void ) = 0;

	virtual unsigned int FilePlayerClearSubtitle ( void ) = 0;

	virtual unsigned int FilePlayerErrFormat ( void ) = 0;

	virtual unsigned int FilePlayerWorking ( unsigned int unGroupIndex , unsigned int unServiceIndex ) = 0;

};



#endif

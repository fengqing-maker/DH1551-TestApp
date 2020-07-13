
#ifndef MOVIEPLAYERINTERFACE_H
#define MOVIEPLAYERINTERFACE_H

#include "adi_player.h"
#include "MoviePlayerType.h"
#include "MoviePlayerNotify.h"

class MoviePlayerInterface
{
public:
	MoviePlayerInterface ( );

	virtual~MoviePlayerInterface ( );

public:

	virtual MoviePlayError MovieStartPlay ( char acFileNodeName [ ], unsigned int unFileNodeNameLen ) = 0;

	virtual MoviePlayError MovieStopPlay ( void ) = 0;

	virtual MoviePlayError MovieStopPlay( unsigned int unIsStartLivePlay ) = 0;

	virtual MoviePlayError MoviePausePlay ( void ) = 0;

	virtual MoviePlayError MovieResumePlay ( void ) = 0;

	virtual MoviePlayError MoviePlayOrPause ( void ) = 0;

	virtual unsigned int MovieSetPlayPosition ( unsigned int unPlayPosition ) = 0;

	virtual unsigned int MovieGetPlayPosition ( int & nPlayPosition ) = 0;

	virtual unsigned int MovieSetPlaySpeed ( ADIPlayerSpeed_E ePlayerSpeed ) = 0;

	virtual unsigned int MovieGetPlaySpeed ( ADIPlayerSpeed_E & ePlayerSpeed ) = 0;

	virtual unsigned int MovieGetTotalTime ( int & nTotalSeconds ) = 0;

	virtual unsigned int IsWorkingMoviePlayer ( ) = 0;

	virtual unsigned int GetMoviePlayerStatus ( EM_MOVIE_PLAYSTATES & eMOVIE_PLAYSTATES ) = 0;

	virtual unsigned int GetMoviePlayerFileInfo ( ADIPlayerFileInfo_S & stFileInfo ) = 0;

	virtual unsigned int GetMoviePlayerFileNodeName ( char acFileNodeName [ ], unsigned int unFileNodeNameLen ) = 0;

	virtual unsigned int GetMoviePlayerDeviceID ( unsigned int & unDeviceID ) = 0;

	virtual unsigned int NotifyMediaMuteStatus ( unsigned int unMute ) = 0;

	virtual unsigned int RegisterMoviePlayerNotify ( MoviePlayerNotify * inputMoviePlayerNotify ) = 0;

	virtual unsigned int UnregisterMoviePlayerNotify ( MoviePlayerNotify * inputMoviePlayerNotify ) = 0;
	
	virtual unsigned int GetMoviePlayerSubtitleCount(int &nSubtitleCount) = 0;

	virtual unsigned int SetMoviePlayerSubtitle(int nSubtitleIndex, bool bEnableSubtitle) = 0;

	virtual unsigned int GetMoviePlayerSubtitleInfo(int nSubtitleIndex, ADIPlayerSubtitleInfo_S & stSubtitleInfo) = 0;

	virtual unsigned int GetMoviePlayerUTFSubtitle(char aucSubtitleTextBuf [ ], unsigned int unSubtitleTextBufLength) = 0;
	
	virtual unsigned int GetMoviePlayerAudCount(int &nAudCount) = 0;

	virtual unsigned int SetMoviePlayerAud(int nAudIndex) = 0;

	virtual unsigned int GetMoviePlayerAudInfo(int nAudIndex, ADIPlayerAudInfo_S & stAudInfo) = 0;

	virtual unsigned int GetMoviePlayerSubtitleIndex(int &nSubtitleIndex) = 0;
	
	virtual unsigned int CloseMoviePlayerSubtitle(void) = 0;

	virtual unsigned int GetMoviePlayerAudIndex(int &nAudIndex) = 0;
	
	virtual unsigned int GetMoviePlayerSubtitleStatus(bool &bEnableSubtitle) = 0;

	virtual unsigned int MoviePlayerPlayingNotify ( unsigned int unGroupIndex , unsigned int unServiceIndex ) = 0;
};



#endif

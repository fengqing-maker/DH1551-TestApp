
#ifndef MP3PLAYERINTERFACE_H
#define MP3PLAYERINTERFACE_H

#include "adi_player.h"
#include "Mp3PlayNotify.h"
#include "Mp3PlayerType.h"
#include "MP3StringInfoInterface.h"

class Mp3PlayerInterface
{
public:
	Mp3PlayerInterface ( );
	virtual ~Mp3PlayerInterface ( );

public:
	virtual unsigned int Mp3PlayerStart ( char acFilePath [ ], unsigned int unFilePathLen ) = 0;

	virtual unsigned int Mp3PlayerStop ( void ) = 0;

	virtual unsigned int Mp3PlayerPause ( void ) = 0;

	virtual unsigned int Mp3PlayerResume ( void ) = 0;

	virtual unsigned int Mp3PlayerSeek ( unsigned int unSeconds ) = 0;

	virtual unsigned int Mp3PlayerGetTime ( unsigned int & unPlayerTime ) = 0;

	virtual unsigned int Mp3PlayerGetDuration ( unsigned int & unDuration ) = 0;

	virtual unsigned int Mp3PlayerGetFilePath ( char acFilePath [ ], unsigned int unFilePathLen ) = 0;

	virtual unsigned int IsWorkingMp3Player ( ) = 0;

	virtual unsigned int GetMp3PlayerStatus ( EM_MP3PlayerType & eMp3_PLAYSTATES ) = 0;

	virtual unsigned int NotifyMp3MuteStatus ( unsigned int unMute ) = 0;

	virtual unsigned int RegisterMp3PlayerNotify ( Mp3PlayerNotify * inputSMp3PlayerNotify ) = 0;

	virtual unsigned int UnregisterMp3PlayerNotify ( Mp3PlayerNotify * inputSMp3PlayerNotify ) = 0;

	virtual MP3StringInfoInterface *GetMP3StringInfoInterface ( void ) = 0;

	virtual MP3StringInfoInterface *GetMP3StringInfo ( char acMp3FileName [ ], unsigned int unLen ) = 0;

	virtual unsigned int Mp3GetDuration ( char acMp3FileName [ ], unsigned int unLen, unsigned int & unDuration ) = 0;

	virtual unsigned int Mp3GetPlaySpeed(ADIPlayerSpeed_E & ePlayerSpeed) = 0;

	virtual unsigned int Mp3SetPlaySpeed(ADIPlayerSpeed_E ePlayerSpeed) = 0;
};



#endif

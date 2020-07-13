
#ifndef MP3PLAYERTYPE_H
#define MP3PLAYERTYPE_H

#define MP3_PARSE_BUF_SIZE		(1024*64)
#define MP3_PARSE_FRAME_SIZE	(1024*3)
#define FIRST_FRAME_VALVE		(12*1024*1024)
#define MP3_IFRAME_SIZE			(418)
#define MP3_INFO_SIZE			(92)
#define MP3_YEAR_SIZE			(32)
#define MP3_ITEM_YEAR_SIZE		(16)

typedef enum
{
	EM_MP3PLAYER_PLAYING,
	EM_MP3PLAYER_STOP,
	EM_MP3PLAYER_PAUSE,
	EM_MP3PLAYER_RESUME,
	EM_MP3PLAYER_FLUSH,
	EM_MP3PLAYER_SEEK,
	EM_MP3PLAYER_INVALID
}EM_MP3PlayerType;

#endif


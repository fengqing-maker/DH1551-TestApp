
#ifndef MOVIEPLAYERTYPE_H
#define MOVIEPLAYERTYPE_H

typedef enum
{
	EM_MOVIE_PLAYING = 0,
	EM_MOVIE_STOP,
	EM_MOVIE_SPEED,
	EM_MOVIE_PAUSE,
	EM_MOVIE_STATUS_INVALID
}EM_MOVIE_PLAYSTATES;

typedef enum 
{
	EM_PLAY_SUCCESS = 0,
	EM_PLAY_ERROR_PARAM_ERROR,
	EM_PLAY_ERROR_NO_SPACE,
	EM_PLAY_ERROR_NO_DEVICE,
	EM_PLAY_ERROR_DEVICE_NOT_READY,
	EM_PLAY_ERROR_STARTED,
	EM_PLAY_ERROR_ADIOPEN_FAIL,
	EM_PLAY_ERROR_GET_STREAM_INFO_FAIL,
	EM_PLAY_ERROR_ADISTART_FAIL,
	EM_PLAY_ERROR_GET_FILE_PATH_FAIL,
	EM_PLAY_ERROR_ADI_SET_STREAM_FAIL,
	EM_PLAY_ERROR_ADICLOSE_FAIL,
	EM_PLAY_ERROR_ADISTOP_FAIL,
	EM_PLAY_ERROR_ADIPAUSE_FAIL,
	EM_PLAY_ERROR_ADIRESUME_FAIL,
	EM_PLAY_ERROR_NOT_START,
	EM_PLAY_ERROR_PLAY_SUBTITLE_FAIL,
	EM_PLAY_ERROR_MAX
}MoviePlayError;


#endif

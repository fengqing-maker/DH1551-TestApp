#ifndef MP3STRINGINFOINTERFACE_H
#define MP3STRINGINFOINTERFACE_H

class MP3StringInfoInterface 
{
public:
	MP3StringInfoInterface ( );
	virtual~MP3StringInfoInterface ( );

public:

	virtual unsigned int LoadSong ( unsigned char ucSong [ ], unsigned int unLen ) = 0;

	virtual unsigned int LoadArtist ( unsigned char ucArtist [ ], unsigned int unLen ) = 0;

	virtual unsigned int LoadAlbum ( unsigned char ucAlbum [ ], unsigned int unLen ) = 0;

	virtual unsigned int LoadYear ( unsigned char ucYear [ ], unsigned int unLen ) = 0;

	virtual unsigned int LoadComment ( unsigned char ucComment [ ], unsigned int unLen ) = 0;

	virtual unsigned int LoadTrackNumber ( unsigned char & ucTrackNumber ) = 0;

	virtual unsigned int LoadPicture ( unsigned char ucPicture [ ], unsigned int unLen ) = 0;

	virtual unsigned int LoadSringFlag ( unsigned int & unStringFlag ) = 0;

	virtual unsigned int SaveSong ( unsigned char ucSong [ ], unsigned int unLen ) = 0;

	virtual unsigned int SaveArtist ( unsigned char ucArtist [ ], unsigned int unLen ) = 0;

	virtual unsigned int SaveAlbum ( unsigned char ucAlbum [ ], unsigned int unLen ) = 0;

	virtual unsigned int SaveYear ( unsigned char ucYear [ ], unsigned int unLen ) = 0;

	virtual unsigned int SaveComment ( unsigned char ucComment [ ], unsigned int unLen ) = 0;

	virtual unsigned int SaveTrack ( unsigned char ucTrack [ ], unsigned int unLen ) = 0;

	virtual unsigned int SavePicture ( unsigned char ucPicture [ ], unsigned int unLen ) = 0;


	virtual unsigned int Clear ( void ) = 0;

};




#endif


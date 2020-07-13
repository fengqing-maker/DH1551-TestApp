#ifndef FILELISTFILTERSPECTYPE_H_
#define FILELISTFILTERSPECTYPE_H_


enum FileListFilterSpecType
{
	eFileFilterGlobalSpecType = 1,
	eFileFilterIncludePhotoSpecType,
	eFileFilterNoSpecType,
	ePVRFileFilterSpecType,
	eRecInfoFileFilterSpecType,
	eCompositeAndFileFilterSpec,
	eCompositeOrFileFilterSpec,
	eMp3FileFilterSpecType,
	eAviFileFilterSpecType,
	eBmpFileFilterSpecType,
	eGifFileFilterSpecType,
	eJpgFileFilterSpecType,
	eJpegFileFilterSpecType,
	eMovFileFilterSpecType,
	eMp4FileFilterSpecType,
	ePngFileFilterSpecType,
	eVobFileFilterSpecType,
	eMkvFileFilterSpecType,
	eWmvFileFilterSpecType,
	eTsFileFilterSpecType,
	eAc3FileFilterSpecType,
	eAacFileFilterSpecType,
	eFlvFileFilterSpecType,
	eWavFileFilterSpecType,
    eWmaFileFilterSpecType,
	eFlacFileFilterSpecType,
	eTxtFileFilterSpecType,
	eDatFileFilterSpecType
};

enum FileType
{
	eAudioType,
	ePicType,
	eMovieType,
	eFolderType,
	eEBookType,
	eOtherType
};

#endif /* FILELISTFILTERSPECTYPE_H_ */

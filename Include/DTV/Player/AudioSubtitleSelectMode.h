/*
 * AudioSubtitleSelectMode.h
 *
 *  Created on: 2015-7-2
 *      Author: timothy.liao
 */

#ifndef AUDIOSUBTITLESELECTMODE_H_
#define AUDIOSUBTITLESELECTMODE_H_

enum AudioSubtitleSelectMode{
	E_AUDIOSUBTL_NORMAL = 0, //Normal mode. select audio and subtitle component according to language settings 

    E_AUDIOSUBTL_ORIGINAL, //Original audio mode. select original audio and select subtitle according to language settings

    E_AUDIOSUBTL_TRANSLATED, //Translated mode. select primary audio (first language) firstly and but disable subtitle;
                             //if there is no primary audio select original audio and select subtitle according to language settings.
};

#endif /* AUDIOSUBTITLESELECTMODE_H_ */

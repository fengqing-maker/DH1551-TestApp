/*
 * VideoFormate.h
 *
 *  Created on: 2015-4-8
 *      Author: timothy.liao
 */

#ifndef VIDEOFORMAT_H_
#define VIDEOFORMAT_H_


enum VideoFormat{
	E_VIDEOFORMAT_NONE = 0,
	E_VIDEOFORMAT_MPEG1,
	E_VIDEOFORMAT_MPEG2,
	E_VIDEOFORMAT_H263,
	E_VIDEOFORMAT_MPEG4, //MPEG4 default
	E_VIDEOFORMAT_DIVX311, //MPEG4 (Divx311)
	E_VIDEOFORMAT_DIVX412, //MPEG4 (Divx412)
	E_VIDEOFORMAT_FLV,
	E_VIDEOFORMAT_VC1ADV,
	E_VIDEOFORMAT_VC1MAIN,
	E_VIDEOFORMAT_RV8,
	E_VIDEOFORMAT_RV9,
	E_VIDEOFORMAT_H264,
	E_VIDEOFORMAT_AVS,
	E_VIDEOFORMAT_HEVC
};



#endif /* VIDEOFORMAT_H_ */
/*
 * PlayStatus.h
 *
 *  Created on: 2015-6-23
 *      Author: linc
 */

#ifndef PLAYSTATUS_H_
#define PLAYSTATUS_H_

enum PlayStatus{
	E_PLAY_STATUS_PLAYING = 0,
	E_PLAY_STATUS_RECORDING,
	E_PLAY_STATUS_PAUSE,
	E_PLAY_STATUS_STOP,
	E_PLAY_STATUS_WAIT_PLAYING,
	E_PLAY_STATUS_WAIT_STOP,
	E_PLAY_STATUS_INVALID
};


#endif /* PLAYSTATUS_H_ */

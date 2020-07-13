/*
 * TimeZone.h
 *
 *  Created on: 2015-7-17
 *      Author: linc
 */

#ifndef TIMEZONE_H_
#define TIMEZONE_H_

#include "string.h"


enum TimeZone{
	m_enTimeZone_AUTO = 0,	//UI需根据TOT表转换为以上时区
	m_enTimeZone_WEST_12,
	m_enTimeZone_WEST_11_POINT_5,
	m_enTimeZone_WEST_11,
	m_enTimeZone_WEST_10_POINT_5,
	m_enTimeZone_WEST_10,
	m_enTimeZone_WEST_9_POINT_5,
	m_enTimeZone_WEST_9,
	m_enTimeZone_WEST_8_POINT_5,
	m_enTimeZone_WEST_8,
	m_enTimeZone_WEST_7_POINT_5,
	m_enTimeZone_WEST_7,
	m_enTimeZone_WEST_6_POINT_5,
	m_enTimeZone_WEST_6,	
	m_enTimeZone_WEST_5_POINT_5,
	m_enTimeZone_WEST_5,
	m_enTimeZone_WEST_4_POINT_5,
	m_enTimeZone_WEST_4,	
	m_enTimeZone_WEST_3_POINT_5,
	m_enTimeZone_WEST_3,
	m_enTimeZone_WEST_2_POINT_5,
	m_enTimeZone_WEST_2,
	m_enTimeZone_WEST_1_POINT_5,
	m_enTimeZone_WEST_1,
	m_enTimeZone_WEST_0_POINT_5,
	m_enTimeZone_0,
	m_enTimeZone_EAST_0_POINT_5,
	m_enTimeZone_EAST_1,
	m_enTimeZone_EAST_1_POINT_5,
	m_enTimeZone_EAST_2,
	m_enTimeZone_EAST_2_POINT_5,
	m_enTimeZone_EAST_3,
	m_enTimeZone_EAST_3_POINT_5,
	m_enTimeZone_EAST_4,
	m_enTimeZone_EAST_4_POINT_5,
	m_enTimeZone_EAST_5,
	m_enTimeZone_EAST_5_POINT_5,
    m_enTimeZone_EAST_5_PAST_45,
	m_enTimeZone_EAST_6,
	m_enTimeZone_EAST_6_POINT_5,
	m_enTimeZone_EAST_7,
	m_enTimeZone_EAST_7_POINT_5,
	m_enTimeZone_EAST_8,
	m_enTimeZone_EAST_8_POINT_5,
	m_enTimeZone_EAST_9,
	m_enTimeZone_EAST_9_POINT_5,
	m_enTimeZone_EAST_10,
	m_enTimeZone_EAST_10_POINT_5,
	m_enTimeZone_EAST_11,
	m_enTimeZone_EAST_11_POINT_5,
	m_enTimeZone_EAST_12,
	m_enTimeZone_MAX
};

#endif /* TIMEZONE_H_ */

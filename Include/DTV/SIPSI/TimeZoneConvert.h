/*
 * TimeZoneConvert.h
 *
 *  Created on: 2015-4-22
 *      Author: timothy.liao
 */

#ifndef TIMEZONECONVERT_H_
#define TIMEZONECONVERT_H_
#include "TimeZone.h"

class TimeZoneConvert
{
public:
    TimeZoneConvert ( );
    virtual ~TimeZoneConvert ( );

public:

    int ConvertTimeZone2Offset ( TimeZone eTimeZone );
    TimeZone ConvertOffset2TimeZone ( int nOffsetInMinutes );
};

#endif /* TIMEZONECONVERT_H_ */

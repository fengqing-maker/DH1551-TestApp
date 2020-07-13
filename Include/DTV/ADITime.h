/*
 * ADITime.h
 *
 *  Created on: 2015-5-8
 *      Author: timothy.liao
 */

#ifndef ADITIME_H_
#define ADITIME_H_

#include "TimeZone.h"

class ADITime
{
public:
	ADITime();
	ADITime(unsigned int Year, unsigned int Month, unsigned int Day, unsigned int Hour, unsigned int Minute, unsigned int Second, unsigned int Week);
	virtual ~ADITime();

public:

	unsigned int PlusLocalTimeOffset(TimeZone enTimeZone);
	unsigned int MinusLocalTimeOffset(TimeZone enTimeZone);

	ADITime operator + (unsigned int unDurationInSec);
	ADITime operator - (unsigned int unDurationInSec);
	int operator - (ADITime inputADITime);
	ADITime& operator = (ADITime inputADITime);
	ADITime& operator += (unsigned int unDurationInSec);
	ADITime& operator -= (unsigned int unDurationInSec);

	unsigned int operator == (ADITime inputADITime);
	unsigned int operator > (ADITime inputADITime);
	unsigned int operator < (ADITime inputADITime);
	unsigned int operator >= (ADITime inputADITime);
	unsigned int operator <= (ADITime inputADITime);
	
	void CalculateWeek ( );

    void CalculateEndTime ( unsigned int unDurationInSecond, ADITime & endTime );
    void CalCulateStartTime ( ADITime & startTime, unsigned int unDurationInSecond );
    unsigned int CalculateDuration ( ADITime startTime, ADITime endTime );
    unsigned int IsInTheTimeWindow ( ADITime startTime, ADITime endTime );
	unsigned int TOTToTDTTime(TimeZone enTimeZone);
	unsigned int TDTToTOTTime(TimeZone enTimeZone);
	int TimeCompare(ADITime targetTime); //-1, before target time; 0 equal to the target time; 1 after the target time

private:

	unsigned int MJDConvertToYMD(unsigned int unMJD);
	unsigned int YMDConvertToMJD();
	
public:

	unsigned int m_Year: 11;
	unsigned int m_Month: 5;
	unsigned int m_Day: 6;
	unsigned int m_Hour: 6;
	unsigned int m_Minute: 7;
	unsigned int m_Second: 7;
	unsigned int m_Week: 5;
};

#endif /* ADITIME_H_ */

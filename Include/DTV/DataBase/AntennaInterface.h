/*
 * AntennaInterface.h
 *
 *  Created on: 2015-5-31
 *      Author: Demo
 */

#ifndef ANTENNAINTERFACE_H_
#define ANTENNAINTERFACE_H_

class AntennaInterface
{

public:

	AntennaInterface( );
	virtual ~AntennaInterface( );

public:

	virtual unsigned short GetPowerCommand( ) = 0;
	virtual unsigned int   GetDiSEqCCommand10( ) = 0;
	virtual unsigned int   GetDiSEqCCommand11( ) = 0;
	virtual unsigned int   GetMotorCommand ( unsigned char &rucMotorType, unsigned char &rucPosition, unsigned char &rucWestEast, unsigned short &rusOrbitalPos ) = 0;

	virtual unsigned int   GetUniCableCommand( ) = 0;
	virtual unsigned short Get22KCommand( ) = 0;

	virtual unsigned int   GetHightFrequency( ) = 0;
	virtual unsigned int   GetCenterFrequency( ) = 0;
	virtual unsigned int   GetLowFrequency( ) = 0;

    virtual void SetPowerCommand ( unsigned short usPowerCommand ) = 0;
    virtual void SetDiSEqCCommand10 ( unsigned int unDiSEqCCommand ) = 0;
	virtual void SetDiSEqCCommand11 ( unsigned int unDiSEqCCommand ) = 0;
	virtual void SetMotorCommand ( unsigned char ucMotorType, unsigned char ucPosition, unsigned char ucWestEast, unsigned short usOrbitalPos ) = 0;
    virtual void SetUniCableCommand ( unsigned int unUniCableCommand ) = 0;
    virtual void Set22KCommand ( unsigned int un22KCommand ) = 0;

    virtual void SetHightFrequency ( unsigned int unHightFrequency ) = 0;
    virtual void SetCenterFrequency ( unsigned int unCenterFrequency ) = 0;
    virtual void SetLowFrequency ( unsigned int unLowFrequency ) = 0;

};

#endif /* ANTENNAINTERFACE_H_ */

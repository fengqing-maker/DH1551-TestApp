#ifndef FACTORYTESTCONSTRUCT_H_
#define FACTORYTESTCONSTRUCT_H_
#include "IrdetoOTASupport.h"
#include "VMXOTASupport.h"
#include "CastpalOTASupport.h"
#include "ConaxOTASupport.h"

OTASupport* GetOTASupport(void);

unsigned int TS_SetOptAndMarketID( int nFlag );

#endif

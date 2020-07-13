#ifndef _IRD_SPI_INTERNEL_H_
#define _IRD_SPI_INTERNEL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "exportDMD.h"

/* describes the information of one satellite band */
typedef struct
{
  uint_t                 band_start;   /* band start frequency in KHz */
  uint_t                 band_end;     /* band end frequency in KHz */
  uint_t                 lo;           /* local oscillator frequency in KHz for this band */
  uchar_t          downlink;     /* downlink frequency band (sat) */
} ird_spi_dmd_satellite_band_t;


typedef struct
{
  uint_t            frequency;         /* frequency in KHz */
  uint_t            symbol_rate;       /* symbol rate in KBAUD */
  uchar_t           modulation_system;      /* select modulation system */
  uchar_t           polarization;      /* select polarization mode(s) */
  ushort_t          modulation;        /* select modulation scheme(s) */
  uint_t            fec_rate;          /* select FEC rate(s) */
  uchar_t           roll_off;          /* select roll-off factor */
  uchar_t           lnb_tone_state;    /* select LNB tone state
                                        (use the default constant 
                                        if the current LNB tone state
                                        must not be changed) */
  uchar_t           diseqc_port;       /* select DiSEqC port */
  dmd_satellite_band_t    band;              /* select band parameters */
} ird_spi_dmd_satellite_desc_t;

typedef struct
{
	uint_t				 frequency; 		/* frequency in KHz */
	dmd_fec_rate_t		 fec_rate;			/* select FEC rate(s) */
	dmd_fec_rate_outer_t fec_rate_outer;	/* select FEC outer */
	dmd_modulation_t	 modulation;		/* select modulation scheme */
	uint_t				 symbol_rate;		/* symbol rate in KBAUD */
} ird_spi_dmd_cable_desc_t;


typedef struct
{
  dmd_device_type_t    device_type; /* Specifies if the tuner device is cable, satellite, terrestrial or IP. */
  union
  {
    ird_spi_dmd_satellite_desc_t   satellite;
    ird_spi_dmd_cable_desc_t       cable;
    dmd_terrestrial_desc_t terrestrial;
    dmd_ip_desc_t          ip;
  } delivery;                       /* information related to the stream */
  uchar_t table_id;
} ird_spi_dmd_delivery_t;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_IRD_SPI_INTERNEL_H_*/


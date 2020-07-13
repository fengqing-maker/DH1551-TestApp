/* ************************************************************************
 *
 *         IRDETO
 *
 *            PROPRIETARY DATA
 *
 *
 * COPYRIGHT (C) 2015 IRDETO. ALL RIGHTS RESERVED.
 *
 * THIS SOFTWARE IS THE CONFIDENTIAL AND PROPRIETARY INFORMATION OF IRDETO.
 * YOU SHALL NOT DISCLOSE SUCH INFORMATION AND SHALL USE IT ONLY IN
 * ACCORDANCE WITH THE TERMS OF THE LICENSE AGREEMENT YOU ENTERED INTO
 * WITH IRDETO.
 *
 * IRDETO MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, OR NON-INFRINGEMENT. IRDETO SHALL NOT BE LIABLE FOR ANY DAMAGES
 * SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
 * THIS SOFTWARE OR ITS DERIVATIVES.
 */

#ifndef _EXPORTDMD_H_
#define _EXPORTDMD_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

 
#define DMD_MAX_QUALITY     100     /* max value for a signal quality */
#define DMD_MAX_STRENGTH    100     /* max value for a signal strength */

#define DMD_MAX_THRESHOLD   10      /* max number of threshold in a threshold list */

#define DMD_MAX_SATCR_USER_BANDS 32 /* max number of user bands for SatCR */

#define DMD_IP_ADDRESS_LEN 16

/*
 *	unsigned
 */
typedef unsigned char		uchar_t;	/*  8 bits */
typedef unsigned short		ushort_t;	/* 16 bits */
typedef unsigned long		ulong_t;	/* 32 bits */
typedef unsigned int		uint_t;		/* 32 bits */

#ifndef __ARCH_CC_H__ //avoid conflicting types with __ARCH_CC_H__
typedef unsigned char		u8_t;
typedef unsigned short		u16_t;
typedef unsigned int		u32_t;
#endif

/*
 *	signed
 */
typedef signed char		schar_t;	/*  8 bits */
typedef signed short		sshort_t;	/* 16 bits */
typedef signed long		slong_t;	/* 32 bits */
typedef signed int		sint_t;		/* 32 bits */	

typedef signed char		i8_t;
typedef signed short		i16_t;
typedef signed int		i32_t;

#ifndef __bool_t_defined
#define __bool_t_defined
typedef unsigned char           bool_t;
#endif


/* tuner id (0-based-index of an opened tuner) */
typedef int dmd_id_t;
typedef uchar_t  dmd_ip_address_t[DMD_IP_ADDRESS_LEN];

/* -----------------------------------------------------------------------------
  Enumerated values
*/

/* tuner events */
typedef enum
{
  DMD_EV_LOCKED            = 0, /* The tuner is locked on a valid signal */
  DMD_EV_UNLOCKED          = 1, /* The tuner is unlocked */
  DMD_EV_SIGNAL_CHANGE     = 3, /* The tuner signal quality threshold has changed */
  DMD_EV_SCAN_FAILED       = 4, /* The scan failed and the tuner is not locked */
  DMD_EV_SCAN_NEXT         = 5, /* A transponder has been found during scanning */
  DMD_EV_SCAN_FINISHED     = 6, /* The scanning operation is finished. */
  DMD_EV_SCAN_STOPPED      = 7, /* The scanning operation has been stopped by user. */
  DMD_EV_CARRIER_LOST      = 8, /* The connection has been lost (cable unplugged for example). */
  DMD_EV_CARRIER_RETRIEVED = 9, /* The connection has been retrieved (cable plugged for example). */
  DMD_EV_SHORT_CIRCUIT     = 10,/* A short circuit has been detected on the feed cable */
  DMD_EV_NO_SHORT_CIRCUIT  = 11,/* The short circuit has been corrected on the feed cable */
  DMD_EV_DISCONNECTED      = 12,/* The disconnect operation ended, the tuner is unlocked */
} dmd_event_t;

/* tuner status */
typedef enum
{
  DMD_STATUS_UNLOCKED,     /* The tuner is not currently locked on a signal */
  DMD_STATUS_LOCKED,       /* The tuner is locked on a signal */
  DMD_STATUS_SCANNING,     /* The tuner is scanning for a valid signal */
  DMD_STATUS_SHORT_CIRCUIT /* The tuner has detected a short circuit */
} dmd_status_t;

/* SysSet options */
typedef enum
{
  DMD_SET_THRESHOLDLIST   = 0,         /* set a list of threshold values request */
  DMD_SET_CALLBACK        = 1,         /* set a callback routine to get the driver events */

  DMD_SCAN_START          = 2,         /* do scan request */
  DMD_SCAN_CONTINUE       = 3,         /* continue scan request */
  DMD_SCAN_ABORT          = 4,         /* stop the current scan request */

  DMD_SET_SATCR_CONFIG    = 5,         /* to enable/disable satCR and set user band frequencies */
  DMD_SET_SATCR_USER_BAND = 6,         /* to set a user band for a given tuner */
  DMD_SET_SOURCE_POWER    = 7          /* set the voltage supplied to the LNB or antenna on or off */
} dmd_sysset_request_t;

/* SysGet options */
typedef enum
{
  DMD_GET_DEVICE_TYPE     = 0,         /* get the the type of front-end device (sat, cab, ter) */
  DMD_GET_DEMOD_COUNT     = 1,         /* get the number of available tuners */
  DMD_GET_SIGNAL_DATA     = 2,         /* get the current signal information */
  DMD_GET_STATUS          = 3,         /* get the current tuner status */
  DMD_GET_SCAN_COMPLETION = 4,         /* get the percentage of scan completion */
  DMD_GET_CAPABILITY      = 5          /* get the capabilities of a tuner */
} dmd_sysget_request_t;

/* specifies the type of front end device */
typedef enum
{
  DMD_SATELLITE   = 0x0100,
  DMD_CABLE       = 0x0200,
  DMD_TERRESTRIAL = 0x0300,
  DMD_IP          = 0x0400
} dmd_device_type_t;

/* downlink frequency bands (sat) */
typedef enum
{
  DMD_DOWNLINK_INJECTION,
  DMD_DOWNLINK_CUSTOM,
  DMD_DOWNLINK_Ku_LOW,     /* e.g. Europe */
  DMD_DOWNLINK_Ku_HIGH,
  DMD_DOWNLINK_C           /* Asia   */
} dmd_downlink_t;

/* Specifies the state of the LNB tone */
typedef enum
{
  DMD_LNB_TONE_DEFAULT,   /* The LNB tone should be left in its current (default)
                             state - for future compatibility with DiSEqC */
  DMD_LNB_TONE_OFF,       /* The LNB tone should be disabled */
  DMD_LNB_TONE_22KHZ      /* The LNB tone should be set to 22kHz */
} dmd_lnb_tone_state_t;

/* Specifies the diseqc port to be used OR the satCR satellite position */
typedef enum
{
  DMD_DISEQC_DEFAULT,  /* Uses default port */
  DMD_DISEQC_PORTA,
  DMD_DISEQC_PORTB,
  DMD_DISEQC_PORTC,
  DMD_DISEQC_PORTD,
  DMD_DISEQC_ALL       /* To scan on all ports. */
} dmd_diseqc_port_t;

/* Polarization constants (applies to Satellite only) */
typedef enum
{
  DMD_PLR_HORIZONTAL      = 0x01,    /* Select horizontal polarization */
  DMD_PLR_VERTICAL        = 0x02,    /* Select vertical polarization */
  DMD_PLR_NONE            = 0x03,    /* No polarization (used when LNB power is off) */
  DMD_PLR_CIRCULAR_LEFT   = 0x04,    /* Select circular left polarization */
  DMD_PLR_CIRCULAR_RIGHT  = 0x05     /* Select circular right polarization */
} dmd_polarization_t;

/* RollOff constants (applies to Satellite only) */
typedef enum
{
  DMD_ROLLOFF_035 = 0x00,    /* Select roll-off 0.35 */
  DMD_ROLLOFF_025 = 0x01,    /* Select roll-off 0.25 */
  DMD_ROLLOFF_020 = 0x02     /* Select roll-off 0.20 */
} dmd_rolloff_t;

/* Modulation system constants (applies to Satellite only) */
typedef enum
{
  DMD_MODSYS_DVBS  = 0x00,    /* Select DVB-S modulation system */
  DMD_MODSYS_DVBS2 = 0x01     /* Select DVB-S2 modulation system */
} dmd_modulation_system_t;

/* FEC puncture rate constants, applicable to satellite and terrestrial devices only */
/* may be bitwise ORed together to select the required FEC rates */
typedef enum
{
  DMD_FEC_NONE    = 0x0000,    /* No FEC rate selected (valid for cable) */
  DMD_FEC_1_2     = 0x0001,    /* Select FEC rate 1/2 */
  DMD_FEC_2_3     = 0x0002,    /* Select FEC rate 2/3 */
  DMD_FEC_3_4     = 0x0004,    /* Select FEC rate 3/4 */
  DMD_FEC_4_5     = 0x0008,    /* Select FEC rate 4/5 */
  DMD_FEC_5_6     = 0x0010,    /* Select FEC rate 5/6 */
  DMD_FEC_6_7     = 0x0020,    /* Select FEC rate 6/7 */
  DMD_FEC_7_8     = 0x0040,    /* Select FEC rate 7/8 */
  DMD_FEC_8_9     = 0x0080,    /* Select FEC rate 8/9 */
  DMD_FEC_3_5     = 0x0100,    /* Select FEC rate 3/5 */
  DMD_FEC_9_10    = 0x0200,    /* Select FEC rate 9/10 */
  DMD_FEC_ALL     = 0xFFFF     /* Select all available FEC rates */
} dmd_fec_rate_t;

/* FEC outer constants, applicable to cable devices */
typedef enum
{
  DMD_FEC_OUTER_NONE        = 0x00,    /* No FEC outer selected */
  DMD_FEC_OUTER_NOT_DEFINED = 0x01,    /* Select FEC rate 1/2 */
  DMD_FEC_OUTER_RS          = 0x02     /* Select FEC rate 2/3 */
} dmd_fec_rate_outer_t;

/* Specifies the modulation scheme constants */
/* may be bitwise ORed together to select the required modulation scheme */
typedef enum
{
  DMD_MOD_NONE    = 0x0000,    /* No modulation selected */
  DMD_MOD_QPSK    = 0x0001,    /* Select QPSK modulation scheme */
  DMD_MOD_8PSK    = 0x0002,    /* Select 8PSK modulation scheme */
  DMD_MOD_QAM     = 0x0004,    /* Select QAM modulation scheme */
  DMD_MOD_4QAM    = 0x0008,    /* Select 4QAM modulation scheme */
  DMD_MOD_16QAM   = 0x0010,    /* Select 16QAM modulation scheme */
  DMD_MOD_32QAM   = 0x0020,    /* Select 32QAM modulation scheme */
  DMD_MOD_64QAM   = 0x0040,    /* Select 64QAM modulation scheme */
  DMD_MOD_128QAM  = 0x0080,    /* Select 128QAM modulation scheme */
  DMD_MOD_256QAM  = 0x0100,    /* Select 256QAM modulation scheme */
  DMD_MOD_BPSK    = 0x0200,    /* Select BPSK modulation scheme */
  DMD_MOD_ALL     = 0xFFFF     /* Select all available modulation schemes */
} dmd_modulation_t;

/* This is an integer field specifying what is the constellation in use. */
/* may be bitwise ORed together to select the required modulation scheme.*/
/* For terrestrial only. */
typedef enum
{
  DMD_CONSTELLATION_NONE    = 0x0000,    /* No modulation selected */
  DMD_CONSTELLATION_QPSK    = 0x0001,    /* Select QPSK modulation scheme */
  DMD_CONSTELLATION_16QAM   = 0x0002,    /* Select 16QAM modulation scheme */
  DMD_CONSTELLATION_64QAM   = 0x0004,    /* Select 64QAM modulation scheme */
  DMD_CONSTELLATION_32QAM   = 0x0008,    /* Select 32QAM modulation scheme */
  DMD_CONSTELLATION_128QAM  = 0x0010,    /* Select 128QAM modulation scheme */
  DMD_CONSTELLATION_256QAM  = 0x0020,    /* Select 256QAM modulation scheme */
  DMD_CONSTELLATION_1024QAM = 0x0040,    /* Select 1024QAM modulation scheme */
  DMD_CONSTELLATION_ALL     = 0xFFFF     /* Select all available modulation schemes */
} dmd_constellation_t;

/* This value indicates the number of carriers in an OFDM frame */
/* For terrestrial only. */
typedef enum
{
  DMD_TRANSMISSION_2K   = 0x01, /* FFT mode 2K  */
  DMD_TRANSMISSION_8K   = 0x02, /* FFT mode 8K  */
  DMD_TRANSMISSION_4K   = 0x03, /* FFT mode 4K  */
  DMD_TRANSMISSION_1K   = 0x04, /* FFT mode 1K  */
  DMD_TRANSMISSION_16K  = 0x05, /* FFT mode 16K */
  DMD_TRANSMISSION_32K  = 0x06  /* FFT mode 32K */
} dmd_transmission_mode_t;

/* Specifies what is the bandwidth in use. For terrestrial only. */
typedef enum
{
  DMD_BANDWIDTH_8M    = 0x01, /* 8 MHz bandwidth */
  DMD_BANDWIDTH_7M    = 0x02, /* 7 MHz bandwidth */
  DMD_BANDWIDTH_6M    = 0x03, /* 6 MHz bandwidth */
  DMD_BANDWIDTH_5M    = 0x04, /* 5 MHz bandwidth */
  DMD_BANDWIDTH_10M   = 0x05, /* 10 MHz bandwidth */
  DMD_BANDWIDTH_17M   = 0x06  /* 1.712 MHz bandwidth */
} dmd_bandwidth_t;

/* Specifies the guard interval. For terrestrial only. */
typedef enum
{
  DMD_GUARD_INTERVAL_1_32    = 0x01, /* Guard interval 1/32   */
  DMD_GUARD_INTERVAL_1_16    = 0x02, /* Guard interval 1/16   */
  DMD_GUARD_INTERVAL_1_8     = 0x03, /* Guard interval 1/8    */
  DMD_GUARD_INTERVAL_1_4     = 0x04, /* Guard interval 1/4    */
  DMD_GUARD_INTERVAL_1_128   = 0x05, /* Guard interval 1/128  */
  DMD_GUARD_INTERVAL_19_128  = 0x06, /* Guard interval 19/128 */
  DMD_GUARD_INTERVAL_19_256  = 0x07  /* Guard interval 19/256 */
} dmd_guard_interval_t;

/* The hierarchy specifies whether the transmission is hierarchical and, if */
/* so, what the alpha value is. For terrestrial only. */
typedef enum
{
  DMD_HIERARCHY_NONE = 0x01,
  DMD_HIERARCHY_1    = 0x02,
  DMD_HIERARCHY_2    = 0x03,
  DMD_HIERARCHY_4    = 0x04
} dmd_hierarchy_t;

/* The hierarchy LPHP specifies which stream (low priority or high priority) */
/* is to be tuned to, in case the hierarchy is specified in dmt_hierarchy_t. */
/* For terrestrial only. */
typedef enum
{
  DMD_HIERARCHY_HP = 0x00,
  DMD_HIERARCHY_LP = 0x01
} dmd_hierarchy_hplp_t;

typedef enum
{
  DMD_PLP_COMMON,
  DMD_PLP_DATA1,
  DMD_PLP_DATA2
} dmd_plp_type_t;

/* Terrestrial DVB type */
typedef enum
{
  DMD_DVBTYPE_DVBT,
  DMD_DVBTYPE_DVBT2
} dmd_terrestrial_dvbtype_t;

/* LNB or antenna power constants */
typedef enum
{
  DMD_SOURCE_POWER_OFF = 0,  /* disable power supply from the tuner */
  DMD_SOURCE_POWER_ON        /* enable power supply from the tuner */
} dmd_source_power_t;

typedef enum
{
  DMD_SATCR_MODE_SCD1 = 0,
  DMD_SATCR_MODE_SCD2
} dmd_satcr_mode_t;

/* -----------------------------------------------------------------------------
  Structures definitions
*/

/* satellite demodulator capabilities. */
typedef struct
{
  bool_t dvbs2_supported;
} dmd_capability_satellite_t;

/* cable demodulator capabilities. */
typedef struct
{
  /* to be defined */
  uchar_t dummy;
} dmd_capability_cable_t;

/* terrestrial demodulator capabilities. */
typedef struct
{
  bool_t dvbt2_supported;
} dmd_capability_terrestrial_t;

/* IP demodulator capabilities. */
typedef struct
{
  /* to be defined */
  uchar_t dummy;
} dmd_capability_ip_t;

/* describes the capabilities of one demodulator */
typedef struct
{
  union 
  {
    dmd_capability_cable_t       cable;
    dmd_capability_satellite_t   satellite;
    dmd_capability_terrestrial_t terrestrial;
    dmd_capability_ip_t          ip;
  } capability;
} dmd_capability_t;

/* describes the information of one satellite band */
typedef struct
{
  uint_t                 band_start;   /* band start frequency in KHz */
  uint_t                 band_end;     /* band end frequency in KHz */
  uint_t                 lo;           /* local oscillator frequency in KHz for this band */
  dmd_downlink_t         downlink;     /* downlink frequency band (sat) */
} dmd_satellite_band_t;

/* To enable SATCR and provide user band frequencies to the HAL  */
typedef struct
{
  bool_t           enable;
  uint_t           userBandTable[DMD_MAX_SATCR_USER_BANDS];
  dmd_satcr_mode_t mode;
} dmd_satcr_config_t;

/* Signal quality threshold values */
typedef struct
{
  uint_t signal_low;     /* Signal quality must be >= to be in this threshold */
  uint_t signal_high;    /* Signal quality must be <= to be in this threshold */
} dmd_signal_threshold_t;

/* A list of signal quality thresholds */
typedef struct
{
  uint_t                  threshold_number;    /* Number of signal threshold elements */
  dmd_signal_threshold_t* threshold_list;      /* An array of signal threshold elements */
} dmd_threshold_list_t;

/* describes the specifics informations related to satellite demodulators */
typedef struct
{
  uint_t                  frequency;         /* frequency in KHz */
  uint_t                  symbol_rate;       /* symbol rate in KBAUD */
  dmd_modulation_system_t modulation_system; /* select modulation system */
  dmd_polarization_t      polarization;      /* select polarization mode(s) */
  dmd_modulation_t        modulation;        /* select modulation scheme(s) */
  dmd_fec_rate_t          fec_rate;          /* select FEC rate(s) */
  dmd_rolloff_t           roll_off;          /* select roll-off factor */
  dmd_lnb_tone_state_t    lnb_tone_state;    /* select LNB tone state
                                                (use the default constant 
                                                if the current LNB tone state
                                                must not be changed) */
  dmd_diseqc_port_t       diseqc_port;       /* select DiSEqC port */
  dmd_satellite_band_t    band;              /* select band parameters */
} dmd_satellite_desc_t;

/* describes the specifics informations related to cable demodulators */
typedef struct
{
  uint_t               frequency;         /* frequency in KHz */
  dmd_fec_rate_t       fec_rate;          /* select FEC rate(s) */
  dmd_fec_rate_outer_t fec_rate_outer;    /* select FEC outer */
  dmd_modulation_t     modulation;        /* select modulation scheme */
  uint_t               symbol_rate;       /* symbol rate in KBAUD */
} dmd_cable_desc_t;

/* describes the specifics informations related to terrestrial demodulators */
typedef struct
{
  uint_t                   frequency;         /* frequency in KHz */
  dmd_constellation_t      constellation;     /* select constellation(s) */
  dmd_hierarchy_t          hierarchy;         /* select hierarchy */
  dmd_hierarchy_hplp_t     hp_lp;             /* select hierarchy priority */
  dmd_fec_rate_t           HP_code_rate;      /* select FEC HP rate(s) */
  dmd_fec_rate_t           LP_code_rate;      /* select FEC LP rate(s) */
  dmd_guard_interval_t     guard_interval;    /* select guard interval */
  dmd_transmission_mode_t  transmission_mode; /* select FFT transmission mode */
  dmd_bandwidth_t          bandwidth;         /* select bandwidth */
} dmd_terrestrial_dvbt_desc_t;

typedef struct
{
  uint_t                   frequency;         /* frequency in KHz */
  uchar_t                  plp_id;            /* select PLP id */
  dmd_guard_interval_t     guard_interval;    /* select guard interval */
  dmd_transmission_mode_t  transmission_mode; /* select FFT transmission mode */
  ushort_t                 T2_system_id;      /* select T2 system id */
  dmd_bandwidth_t          bandwidth;         /* select bandwidth */
} dmd_terrestrial_dvbt2_desc_t;

typedef struct
{
  dmd_terrestrial_dvbtype_t dvb_type;           /* select terrestrial DVB type */
  union
  {
    dmd_terrestrial_dvbt_desc_t  dvbt;          /* DVB-T parameters */
    dmd_terrestrial_dvbt2_desc_t dvbt2;         /* DVB-T2 parameters */
  } desc;
} dmd_terrestrial_desc_t;

/* describes the specifics informations related to ip connection */
typedef struct
{
  dmd_ip_address_t address;    /* IP address in decimal format aaa.bbb.ccc.ddd */
  uint_t           port;       /* UDP port for first IP address */
  dmd_ip_address_t address2;   /* second optional IP address in decimal format aaa.bbb.ccc.ddd */
  uint_t           port2;      /* UDP port for second IP address */
} dmd_ip_desc_t;

/* specifies the device type and the stream information */
typedef struct
{
  dmd_device_type_t    device_type; /* Specifies if the tuner device is cable, satellite, terrestrial or IP. */
  union
  {
    dmd_satellite_desc_t   satellite;
    dmd_cable_desc_t       cable;
    dmd_terrestrial_desc_t terrestrial;
    dmd_ip_desc_t          ip;
  } delivery;                       /* information related to the stream */
} dmd_delivery_t;

/* Terrestrial scan criteria */
typedef struct
{
  uint_t start_frequency;    /* the frequency in KHz the scan must start with */
  uint_t end_frequency;      /* the frequency in KHz the scan must reach */
  uint_t step_frequency;     /* the step frequency in KHz the scan must increase */
  dmd_transmission_mode_t transmission_mode; /* the transmission mode the scan must search */
  dmd_bandwidth_t bandwidth; /* bandwidth of the signal */
  dmd_terrestrial_dvbtype_t dvb_type; /* the DVB type the scan must search (DVB-T or DVB-T2) */
} dmd_scan_terrestrial_t;

/* Used to store specific satellite signal data.
 */
typedef struct
{
  uint_t dummy;    /* the struct must not be empty to compile */
} dmd_satellite_signal_t;

/* Used to store specific cable signal data.
 */
typedef struct
{
  uint_t dummy;    /* the struct must not be empty to compile */
} dmd_cable_signal_t;

/* Used to store specific terrestrial signal data.
 */
typedef struct
{
  uint_t dummy;    /* the struct must not be empty to compile */
} dmd_terrestrial_dvbt_signal_t;

typedef struct
{
  uchar_t        plp_id;  /* PLP id */
  dmd_plp_type_t plp_type; /* PLP type */
} dmd_terrestrial_dvbt2_signal_plp_t;

typedef struct
{
  bool_t siso_miso;                            /* SISO/MISO flag (DKI_FALSE=SISO, DKI_TRUE=MISO) */
  ushort_t cell_id;                            /* current cell id */
  ushort_t network_id;                         /* current network id */
  uchar_t num_plp;                             /* number of PLPs */
  dmd_terrestrial_dvbt2_signal_plp_t plp[256]; /* index and type of each PLP */
} dmd_terrestrial_dvbt2_signal_t;

typedef struct
{
  union
  {
    dmd_terrestrial_dvbt_signal_t  dvbt;  /* additional DVB-T signal information */
    dmd_terrestrial_dvbt2_signal_t dvbt2; /* additional DVB-T2 signal information */
  } signal;
} dmd_terrestrial_signal_t;

/* the current signal information */
typedef struct
{
  uint_t         signal_strength; /* ratio of signal strength 
                                     (i.e. signal amplitude) */
  uint_t         signal_quality;  /* ratio of error bit rate */
  dmd_status_t   status;
  union /* This union holds additional signal informations 
           specific to a tuner device (cable, satellite, or terrestrial). */
  {
    dmd_satellite_signal_t   satellite;
    dmd_cable_signal_t       cable;
    dmd_terrestrial_signal_t terrestrial;
  } signal;
  dmd_delivery_t delivery_data;   /* actual locked channel parameters */
} dmd_signal_data_t;

/* structure used as main parameter in notify event callback */
typedef struct
{
  dmd_event_t event;
  dmd_id_t    id;
  const void *subscriberData;
  const void *demodData;
  void       *reqData;
} dmd_callback_param_t;

 
#ifdef __cplusplus
}
#endif /* __cplusplus */

 
#endif /* _EXPORTDMD_H_ */

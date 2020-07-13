/*
 * TunerServicesSearchMode.h
 *
 *  Created on: 2015-5-11
 *      Author: timothy.liao
 */

#ifndef TUNERSERVICESSEARCHMODE_H_
#define TUNERSERVICESSEARCHMODE_H_


enum TunerServicesSearchMode{
	E_SEARCH_NITSDT, //Fast search mode, NIT+SDTActual+SDTOther
	E_SEARCH_NITSDTBAT, //Fast search mode, NIT+SDTActual+SDTOther+BAT
	E_SEARCH_PATPMT, //Single Search, PAT+PMT+SDTActual, 
	E_SEARCH_PATPMT_NIT, // Network Search, 1st step: NIT Delivery Search; 2nd step: PATPMT Search
	E_SEARCH_PATPMT_NITBAT, // Network Search, 1st step: NIT+BAT Delivery Search; 2nd step: PATPMT Search
    E_SEARCH_PATPMTNIT_SINGLEDELIVERY, //Single Search
    E_SEARCH_PATPMT_NITANDNITOTHER, //Network Search, 1st step: NIT+NITOther Search; 2nd step: PATPMT Search
    E_SEARCH_PATPMT_NITBATNITOTHER, //Network Search, 1st step: NIT+NITOther+BAT Search; 2nd step: PATPMT Search
    E_SEARCH_NITSDTBATNITOTHER, //Fast search mode, NIT+SDTActual+SDTOther+BAT+NITOther
    E_SEARCH_NITSDTACTUALBAT, //Fast search mode, NIT+SDTActual+BAT
    E_SEARCH_BLINDSCAN, //blind scan for satellite

    //customized search
	E_SEARCH_M7, //M7 Search
	E_SEARCH_M7_UPDATE, //M7 Auto Service Update

    E_SEARCH_TIVUSAT, //TivuSat auto search mode

    E_SEARCH_MAX

};



#endif /* TUNERSERVICESSEARCHMODE_H_ */

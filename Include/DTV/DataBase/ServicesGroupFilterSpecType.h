/*
 * ServicesGroupFilterSpecType.h
 *
 *  Created on: 2015-5-12
 *      Author: Demo
 */

#ifndef SERVICESGROUPFILTERSPECTYPE_H_
#define SERVICESGROUPFILTERSPECTYPE_H_

enum ServicesGroupFilterSpecType
{
	eNetworkIDFilterSpec = 1,
	eOriIDFilterSpec,
	eTSIDFilterSpec,
	eServicesIDFilterSpec,
	eServiceTypeFilterSpec,
	eServiceNameFilterSpec,
	eBouquetIDFilterSpec,
	eAndServicesGroupFilterSpec,
	eOrServicesGroupFilterSpec,
	eNotServicesGroupFilterSpec,
    eSatelliteNameFilterSpec,
	eServiceNameWithSubStrFilterSpec,
	eServiceHDNameFilterSpec
};

#endif /* SERVICESGROUPFILTERSPECTYPE_H_ */

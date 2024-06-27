/*
 * device_factory.h
 *
 *  Created on: Nov 30, 2023
 *      Author: vlasi
 */

#ifndef INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_FACTORY_H_
#define INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_FACTORY_H_

#include "led.h"

class DeviceFactory {

public:

	DeviceFactory();
	Led* createLed(const int pin, const char *name);

};

#endif /* INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_FACTORY_H_ */

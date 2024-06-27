/*
 * device_factory.cpp
 *
 *  Created on: Nov 30, 2023
 *      Author: Vlasiuk RV
 */

#include "device_factory.h"

DeviceFactory::DeviceFactory() {

}

Led* DeviceFactory::createLed(const int pin, const char *name) {

	return new Led(pin, name);

}

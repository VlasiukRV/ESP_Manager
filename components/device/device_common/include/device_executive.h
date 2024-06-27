/*
 * device_executive.h
 *
 *  Created on: Nov 27, 2023
 *      Author: VlasiukRV
 */

#ifndef INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_EXECUTIVE_H_
#define INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_EXECUTIVE_H_

#include "device.h"

class ExecutorDevice: public Device {

public:

	~ExecutorDevice();
	ExecutorDevice(void);
	ExecutorDevice(const int pin, const char *name);

	int on();
	int off();
	int toggle();

};

#endif /* INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_EXECUTIVE_H_ */

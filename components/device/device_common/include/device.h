/*
 * sensor.h
 *
 *  Created on: Nov 16, 2023
 *      Author: VlasiukRV
 */

#ifndef INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_H_
#define INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_H_

//#include "../../../esp32_driver/include/cppgpio.h"
#include "cppgpio.h"

enum DeviceType {
	DEVICE_MODE_DISABLE = -1, /*!< Out of memory */
	SENSING_DEVICE = 1, /*!< Device type that receives a signal or stimulus (as heat or pressure or light or motion etc.) */
	EXECUTIVE_DEVICE = 2, /*< Device refers to the visual output device such as led, relay, etc */
};

enum DeviceState {
	DEVICE_OFF = 0, DEVICE_ON = 1,
};

class Device {

private:

public:

	Device(void);
	Device(GpioBase *gpio, const char *name);
	virtual ~Device();

	void set_pin(const int pin);
	int get_pin();

	void set_device_type(const DeviceType device_type);
	DeviceType get_device_type();

	void set_name(const char *name);
	const char* get_name();

	DeviceState get_device_state();

	virtual int on() = 0;
	virtual int off() = 0;

protected:

	GpioBase *gpio_ { nullptr };

	const char *_name { "" };
	DeviceType deviceType { DEVICE_MODE_DISABLE };
	DeviceState deviceState { DEVICE_OFF };

};

#endif /* INCLUDE_SIMPLEOBJECTLIB_SENSORS_DEVICE_H_ */

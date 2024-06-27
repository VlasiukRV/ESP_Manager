/*
 * led.h
 *
 *  Created on: Nov 14, 2023
 *      Author: Vlasiuk
 */

#ifndef INCLUDE_SIMPLEOBJECTLIB_SENSORS_LED_H_
#define INCLUDE_SIMPLEOBJECTLIB_SENSORS_LED_H_

#include "device_executive.h"
#include "threadable.h"

class Led: public ExecutorDevice, public Threadable {

public:

	~Led();
	Led(void);
	Led(const int pin, const char *name);

	int blink_on();
	int on();
	int off();

private:

	void runBlink();

};

#endif /* INCLUDE_SIMPLEOBJECTLIB_SENSORS_LED_H_ */

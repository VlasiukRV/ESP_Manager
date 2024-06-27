/*
 * led.cpp
 *
 *  Created on: Nov 14, 2023
 *      Author: vlasi
 */

#include "led.h"

Led::~Led() {

}

Led::Led() :
		ExecutorDevice() {

}

Led::Led(const int pin, const char *name) :
		ExecutorDevice(pin, name) {

}

int Led::blink_on() {

	taskParam = new TaskParams();

	taskParam->taskName = "Led_Blink";
	taskParam->taskStackSize = 1024;
	taskParam->method = [this]() {
		this->runBlink();
	};

	Threadable::run_task();

	return 1;
}

int Led::on() {

	ExecutorDevice::on();

	return 1;
}

int Led::off() {

	ExecutorDevice::off();

	Threadable::stop_task();

	return 1;
}

void Led::runBlink() {

	while (true) {

		vTaskDelay(pdMS_TO_TICKS(500));
		ExecutorDevice::toggle();

	}

}

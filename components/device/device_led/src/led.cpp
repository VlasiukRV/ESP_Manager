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

	task_param = new TaskParams();

	task_param->task_name = "Led_Blink";
	task_param->task_stack_size = 1024;
	task_param->method = [this]() {
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

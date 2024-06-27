/*
 * device_executive.cpp
 *
 *  Created on: Nov 27, 2023
 *      Author: VlasiukRV
 */
#include "device_executive.h"

ExecutorDevice::~ExecutorDevice() {

}

ExecutorDevice::ExecutorDevice() :
		Device() {

}

ExecutorDevice::ExecutorDevice(const int pin, const char *name) {

	gpio_num_t gpio_pin = (gpio_num_t) pin;
	this->gpio_ = new GpioOutput(gpio_pin);
	this->_name = name;

}

int ExecutorDevice::on() {

	static_cast<GpioOutput*>(gpio_)->on();
	this->_device_state = DEVICE_ON;

	return 1;

}

int ExecutorDevice::off() {

	static_cast<GpioOutput*>(gpio_)->off();
	this->_device_state = DEVICE_OFF;

	return 1;
}

int ExecutorDevice::toggle() {

	static_cast<GpioOutput*>(gpio_)->toggle();
	this->_device_state =
			this->_device_state == DEVICE_ON ? DEVICE_OFF : DEVICE_ON;

	return 1;
}

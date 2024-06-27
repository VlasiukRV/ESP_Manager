/*
 * sensor.cpp
 *
 *  Created on: Nov 16, 2023
 *      Author: VlasiukRV
 */

#include "device.h"

Device::Device() {

}

Device::Device(GpioBase *gpio, const char *name) {

	this->gpio_ = gpio;
	this->_name = name;

}

Device::~Device() {
	delete this->gpio_;
	this->gpio_ = nullptr;
}

void Device::set_pin(const int pin) {

}

int Device::get_pin() {

	return (int) this->gpio_->get_pin();

}

void Device::set_device_type(const DeviceType device_type) {

	this->_device_type = device_type;

}

DeviceType Device::get_device_type() {

	return this->_device_type;

}

DeviceState Device::get_device_state() {

	return this->_device_state;

}

void Device::set_name(const char *name) {
	this->_name = name;
}

const char* Device::get_name() {

	return this->_name;

}

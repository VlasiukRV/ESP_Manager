/*
 * threadable.h
 *
 *  Created on: Jun 22, 2024
 *      Author: vlasi
 */

#ifndef COMPONENTS_UTIL_THREADABLE_THREADABLE_H_
#define COMPONENTS_UTIL_THREADABLE_THREADABLE_H_

#include <functional>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Threadable;

struct TaskParams {
	std::function<void()> method;
	const char *task_name;
	uint32_t task_stack_size = 1024;
};

class Threadable {
public:
	Threadable();
	~Threadable();

	void run_task();
	void stop_task();

	TaskParams *task_param = nullptr;

protected:
	TaskHandle_t task_handle = nullptr;

};

#endif /* COMPONENTS_UTIL_THREADABLE_THREADABLE_H_ */

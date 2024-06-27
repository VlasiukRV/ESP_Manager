/*
 * threadable.cpp
 *
 *  Created on: Jun 22, 2024
 *      Author: vlasi
 */

#include "threadable.h"

Threadable::Threadable() {
	task_handle = nullptr;
	task_param = nullptr;
}

Threadable::~Threadable() {

	if (task_handle != nullptr) {
		vTaskDelete(task_handle);
	}

	if (task_param != nullptr) {
		delete task_param;
	}
}

void Threadable::run_task() {

	if (task_handle != nullptr) {

		vTaskResume(task_handle);

	} else {

		xTaskCreatePinnedToCore([](void *pvParameters) {
			TaskParams *taskParams = static_cast<TaskParams*>(pvParameters);
			taskParams->method();
		}, //Function to implement the task
				task_param->task_name, //Name of the task
				task_param->task_stack_size, //Stack size in words
				task_param, //Task input parameter
				tskIDLE_PRIORITY + 1, //Priority of the task
				&task_handle, //Task handle.
				APP_CPU_NUM); //Core where the task should run

		if (task_handle == nullptr) {
			ESP_LOGI("", "*** [Error] Failed to create task %s!\n",
					task_param->task_name);
		} else {
			ESP_LOGI("", "*** Tasks created successfully %s (%p)!\n",
					task_param->task_name, task_handle);
		}

	}

}

void Threadable::stop_task() {

	if (task_handle != nullptr) {

		vTaskSuspend(task_handle);
		ESP_LOGI("", "*** Task %s (%p) is suspend!\n", task_param->task_name,
				task_handle);

	}

}

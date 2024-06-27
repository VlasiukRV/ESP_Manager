/*
 * threadable.cpp
 *
 *  Created on: Jun 22, 2024
 *      Author: vlasi
 */

#include "threadable.h"

Threadable::Threadable() {
	taskHandle = nullptr;
	taskParam = nullptr;
}

Threadable::~Threadable() {

	if (taskHandle != nullptr) {
		vTaskDelete(taskHandle);
	}

	if (taskParam != nullptr) {
		delete taskParam;
	}
}

void Threadable::run_task() {

	if (taskHandle != nullptr) {

		vTaskResume(taskHandle);

	} else {

		xTaskCreatePinnedToCore([](void *pvParameters) {
			TaskParams *taskParams = static_cast<TaskParams*>(pvParameters);
			taskParams->method();
		}, //Function to implement the task
				taskParam->taskName, //Name of the task
				taskParam->taskStackSize, //Stack size in words
				taskParam, //Task input parameter
				tskIDLE_PRIORITY + 1, //Priority of the task
				&taskHandle, //Task handle.
				APP_CPU_NUM); //Core where the task should run

		if (taskHandle == nullptr) {
			ESP_LOGI("", "*** [Error] Failed to create task %s!\n",
					taskParam->taskName);
		} else {
			ESP_LOGI("", "*** Tasks created successfully %s (%p)!\n",
					taskParam->taskName, taskHandle);
		}

	}

}

void Threadable::stop_task() {

	if (taskHandle != nullptr) {

		vTaskSuspend(taskHandle);
		ESP_LOGI("", "*** Task %s (%p) is suspend!\n", taskParam->taskName,
				taskHandle);

	}

}

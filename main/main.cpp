/*
 * main.cpp
 *
 *  Created on: Nov 14, 2023
 *      Author: vlasiuk
 */

#include "worker_main.h"

extern "C" void app_main(void) {

	//vTaskDelay(pdMS_TO_TICKS(5000));

	Worker_Main worker_main = Worker_Main();
	worker_main.print_chip_information();

	worker_main.show_healse();

	//esp_event_loop_create_default();

	worker_main.init();
	worker_main.setup();
	worker_main.show_healse();

	while (true) {

		worker_main.run_tact_of_work();

		vTaskDelay(pdMS_TO_TICKS(5000));
		worker_main.show_healse();

		ESP_LOGI("", "***");

	};

}


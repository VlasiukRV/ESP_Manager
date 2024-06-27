#pragma once

//#include <iostream>
//#include <cstring>
#include "device_factory.h"
#include "state_machine.h"
#include "linkedList.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_event.h"

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
//#include "esp_flash.h"

//using namespace CPPGPIO;
//using namespace SOL;

// Main class used for testing only
class Worker_Main final {
public:
	Worker_Main();

	void init(void);
	void init_traficLight(void);
	void setup(void);
	void run_tact_of_work(void);

	void show_healse();
	void print_chip_information();

	KaTime started_at;

	esp_util::ArrayList<StepTimeStateMachine<Led>> table;
	TimeStateMachine<Led> time_stete_machine;
	DeviceFactory dev_factory;

	Led *led1 { nullptr };
	Led *led2 { nullptr };
	Led *led3 { nullptr };

	esp_util::LinkedList<Led*> list;
	//LinkedList<GpioOutput> list;

	// LED pin on my NodeMCU
	//GpioOutput cppLed { GPIO_NUM_2, true };
	// Repurpose the BOOT button to work as an input
	//GpioInput cppButton { GPIO_NUM_0 };
	// A second input to demonstrate Event_ID different event handlers
	//GpioInput cppButton2 { GPIO_NUM_12 };

	// Event Handler for cppButton
	static void button_event_handler(void *handler_args, esp_event_base_t base,
			int32_t id, void *event_data);
	// Event Handler for cppButton2
	static void button2_event_handler(void *handler_args, esp_event_base_t base,
			int32_t id, void *event_data);

	const char *TAG { "" };

private:

	int tact_of_work_count { 0 };

};
// Main Class

#include "worker_main.h"

void toggleLed(Led *tempLed) {
	if (tempLed != nullptr) {
		tempLed->toggle();
	}
}

Worker_Main::Worker_Main() {
	//char foo[100];
	//strncpy(foo, "test", sizeof(foo));

	TAG = "ESP_Manager";
	list = esp_util::LinkedList<Led*>();

	dev_factory = DeviceFactory();

	time_stete_machine = TimeStateMachine<Led>();

	started_at = kaMillis();

	//list = LinkedList<GpioOutput>();
}

void Worker_Main::init(void) {

//	led1 = dev_factory.createLed(25, "led1");
//	led2 = dev_factory.createLed(26, "led2");

	init_traficLight();

//	gpio_num_t gpio_pin = (gpio_num_t) 25;
//	list.push(GpioOutput(gpio_pin));

//	cppButton.enableInterrupt(GPIO_INTR_NEGEDGE);
//	cppButton.setEventHandler(&button_event_handler);
//
//	cppButton2.enablePullup();
//	cppButton2.enableInterrupt(GPIO_INTR_NEGEDGE);
//	cppButton2.setEventHandler(&button2_event_handler);
}

void Worker_Main::init_traficLight(void) {

	//traffic_light.setup(dev_factory);

	Led *led_red = new Led(25, "led_red");
	Led *led_yellow = new Led(26, "led_yellow");
	Led *led_green = new Led(27, "led_green");

	led_red->on();
	led_yellow->on();
	led_green->on();

	StepTimeStateMachine<Led> st1 = StepTimeStateMachine<Led>(led_red,
			&Led::off, 10, 1, 1);
	StepTimeStateMachine<Led> st2 = StepTimeStateMachine<Led>(led_yellow,
			&Led::off, 10, 2, 1);
	StepTimeStateMachine<Led> st3 = StepTimeStateMachine<Led>(led_green,
			&Led::off, 10, 3, 1);

	StepTimeStateMachine<Led> st4 = StepTimeStateMachine<Led>(led_red, &Led::on,
			50000000, 4, 1);
	StepTimeStateMachine<Led> st5 = StepTimeStateMachine<Led>(led_red,
			&Led::off, 10, 5, 1);

	StepTimeStateMachine<Led> st6 = StepTimeStateMachine<Led>(led_yellow,
			&Led::on, 10000000, 6, 1);
	StepTimeStateMachine<Led> st7 = StepTimeStateMachine<Led>(led_yellow,
			&Led::off, 10, 7, 1);

	StepTimeStateMachine<Led> st8 = StepTimeStateMachine<Led>(led_green,
			&Led::on, 40000000, 8, 1);
	StepTimeStateMachine<Led> st9 = StepTimeStateMachine<Led>(led_green,
			&Led::off, 10, 9, 1);

	StepTimeStateMachine<Led> st10 = StepTimeStateMachine<Led>(led_green,
			&Led::blink_on, 10000000, 10, 1);
	StepTimeStateMachine<Led> st11 = StepTimeStateMachine<Led>(led_green,
			&Led::off, 10, 3, 1);

	table.add(st1);
	table.add(st2);
	table.add(st3);
	table.add(st4);
	table.add(st5);
	table.add(st6);
	table.add(st7);
	table.add(st8);
	table.add(st9);
	table.add(st10);
	table.add(st11);

	table.trim_to_size();

	time_stete_machine.setTable(&table);
	time_stete_machine.nextState = 0;

}

void Worker_Main::setup(void) {

	time_stete_machine.start();

	//led1->blink_on();

//	list.process_list([](Led *led) {
//
//		//ESP_LOGI(TAG, "*** --- - %s ON ", led->get_name());
//		led->on();
//
//	});

}

void Worker_Main::run_tact_of_work(void) {

//	const auto &currentStep = time_stete_machine.table[1];
//	(currentStep.object->*currentStep.action)();

//	const auto &currentStep = time_stete_machine.table[4];
//	(currentStep.object->*currentStep.action)();

	//if (time_stete_machine.is_runing()) {
	//time_stete_machine.loop();
	//}

//	if (tact_of_work_count > 150) {
//		led1->blinkOff();
//	}

//	everyMillis(1000,
//			{ led1->toggle(); ESP_LOGI(TAG, "*** Run led1 - every Mills"); });

//	everyMillis(2000,
//			{ led2->toggle(); ESP_LOGI(TAG, "*** Run led2 - every Mills"); });

//	if (led1 == nullptr) {
//
//		led1 = dev_factory.createLed(25, "led25");
//		led2 = dev_factory.createLed(26, "led26");
//
//
//	} else {
//
//		delete led1;
//		led1 = nullptr;
//		delete led2;
//		led2 = nullptr;
//
//	}

//	if (list.size() != 0) {
//
//		Led *led_tmp = list.getHeadElement();
//		led_tmp->toggle();
//		ESP_LOGI(TAG, "*** --- DELETE - %s pin %i ", led_tmp->get_name(),
//				led_tmp->get_pin());
//		list.pull();
//
//	} else {
//
//		list.push(dev_factory.createLed(25, "led1"));
//		list.push(dev_factory.createLed(26, "led2"));
//
//		esp_util::Iterator<Led*> *list_iterator = list.create_iterator();
//
//		int count = 0;
//		for (list_iterator->begin(); list_iterator->has_more();
//				list_iterator->get_next()) {
//
//			Led *_led = list_iterator->current();
//
//			ESP_LOGI(TAG, "*** --- %i - %s (%i) pin %i TOGGLE ", list.size(),
//					_led->get_name(), (int ) _led->get_device_type(),
//					_led->get_pin());
//
//			_led->toggle();
//
//			count++;
//		}
//
//		delete list_iterator;
//
//	}

//	led1->toggle();
//	led2->toggle();

//if (this->led1 == nullptr) {
//		this->led1 = dev_factory.createLed(26, "led26");
//		this->led1->toggle();
//}

	//time_stete_machine.loop();

	ESP_LOGI("SM", "started_at - %lld", time_stete_machine.started_at);
	ESP_LOGI("SM", "timeout - %lld", time_stete_machine.timeout);
	ESP_LOGI("SM", "nextState - %i", time_stete_machine.nextState);
//	ESP_LOGI("SM", "table[4].stateOk =  %i", table[4].stateOk);
//	ESP_LOGI("SM", "table.size() =  %i", table.size());

	//traffic_light.show_healse();

	tact_of_work_count++;
	//list.push(dev_factory.createLed(25, "led25"));
	//cppLed.setLevel(cppButton.read());

}

void Worker_Main::button_event_handler(void *handler_args,
		esp_event_base_t base, int32_t id, void *event_data) {
	//std::cout << "Button triggered interrupt with ID: " << id << '\n';
}

void Worker_Main::button2_event_handler(void *handler_args,
		esp_event_base_t base, int32_t id, void *event_data) {
	//std::cout << "Button triggered interrupt with ID: " << id << '\n';
}

void Worker_Main::show_healse() {

	KaTime skippedTime = kaMillis() - started_at;

	ESP_LOGI(TAG, "");
	ESP_LOGI(TAG, "*** Run - %d times", tact_of_work_count);

	ESP_LOGI(TAG, "free_heap - %d", esp_get_free_heap_size());
	ESP_LOGI(TAG, "free_internal_heap - %d", esp_get_free_internal_heap_size());
	ESP_LOGI(TAG, "minimum_free_heap - %d", esp_get_minimum_free_heap_size());
	ESP_LOGI(TAG, "skipped time - %lld", skippedTime);

}

void Worker_Main::print_chip_information() {

	/* Print chip information */
	esp_chip_info_t chip_info;
	esp_chip_info(&chip_info);
	printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
	CONFIG_IDF_TARGET, chip_info.cores,
			(chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
			(chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

	unsigned major_rev = chip_info.full_revision / 100;
	unsigned minor_rev = chip_info.full_revision % 100;
	printf("silicon revision v%d.%d, ", major_rev, minor_rev);

	uint32_t size_flash_chip = 0;
	// esp_flash_get_physical_size(NULL, &size_flash_chip);

	printf("%dMB %s flash\n", size_flash_chip / (1024 * 1024),
			(chip_info.features & CHIP_FEATURE_EMB_FLASH) ?
					"embedded" : "external");

	printf("Minimum free heap size: %d bytes\n",
			esp_get_minimum_free_heap_size());

}


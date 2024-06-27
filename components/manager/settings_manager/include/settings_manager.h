/*
 * settings_manager.h
 *
 *  Created on: May 21, 2024
 *      Author: vlasi
 */

#ifndef COMPONENTS_MANAGER_SETTINGS_MANAGER_INCLUDE_SETTINGS_MANAGER_H_
#define COMPONENTS_MANAGER_SETTINGS_MANAGER_INCLUDE_SETTINGS_MANAGER_H_

#include "esp_spiffs.h"
#include "esp_log.h"
#include "cJSON.h"

class SettingsManager {
public:
	SettingsManager() {
		// Ініціалізація SPIFFS
		esp_vfs_spiffs_conf_t conf = { .base_path = "/spiffs",
				.partition_label = NULL, .max_files = 5,
				.format_if_mount_failed = true };
		esp_err_t ret = esp_vfs_spiffs_register(&conf);
		if (ret != ESP_OK) {
			ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)",
					esp_err_to_name(ret));
			return;
		}
	}

	void saveSettings(const char *filename, cJSON *json) {
		// Відкриття файлу для запису
		FILE *file = fopen(filename, "w");
		if (file == NULL) {
			ESP_LOGE(TAG, "Failed to open file for writing");
			return;
		}

		// Запис JSON у файл
		char *json_string = cJSON_Print(json);
		fprintf(file, "%s", json_string);
		fclose(file);
		free(json_string);
	}

	cJSON* loadSettings(const char *filename) {
		// Відкриття файлу для читання
		FILE *file = fopen(filename, "r");
		if (file == NULL) {
			ESP_LOGE(TAG, "Failed to open file for reading");
			return NULL;
		}

		// Читання JSON з файлу
		fseek(file, 0, SEEK_END);
		long length = ftell(file);
		fseek(file, 0, SEEK_SET);
		char *buffer = (char*) malloc(length + 1);
		fread(buffer, 1, length, file);
		fclose(file);
		buffer[length] = '\0';

		// Парсинг JSON
		cJSON *json = cJSON_Parse(buffer);

		free(buffer);

		return json;
	}
};

#endif /* COMPONENTS_MANAGER_SETTINGS_MANAGER_INCLUDE_SETTINGS_MANAGER_H_ */

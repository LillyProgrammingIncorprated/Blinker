#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

#define GPIO19_PIN_SEL 0x80000 
static const char* TAG = "Blinker";

void app_main(void) {
    gpio_config_t gpio_conf = {};
    gpio_conf.mode = GPIO_MODE_OUTPUT;
   	gpio_conf.pull_up_en = 0;
    gpio_conf.pull_down_en = 0;
    gpio_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_conf.pin_bit_mask = GPIO19_PIN_SEL;
   	ESP_ERROR_CHECK(gpio_config(&gpio_conf));

	esp_err_t err = 0;
	printf("\n");
	while (1) {
		err = gpio_set_level(GPIO_NUM_19, 0);
		if (err != ESP_OK)
			ESP_LOGE(TAG, "Error Setting GPIO19 HIGH (Error Code: %d)", err);
		else
			ESP_LOGI(TAG, "GPIO19 set HIGH");
		vTaskDelay(1000 / portTICK_PERIOD_MS);

		err = gpio_set_level(GPIO_NUM_19, 0);
		if (err != ESP_OK)
			ESP_LOGE(TAG, "Error Setting GPIO19 HIGH (Error Code: %d)", err);
		else
			ESP_LOGI(TAG, "GPIO19 set HIGH");
	}
}

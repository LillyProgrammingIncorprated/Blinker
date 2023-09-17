#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
// set the log verbosity to max 
#define GPIO19_PIN_SEL 0x80000
// GPIO pin selection takes in a unsigned 64 bit integer
// and the index of the bits that are on determine the pins selecter
// for example 0x1 would just be 63 0s and a sinle 1 at the end
// that would select GPIO1
// 0x80000 is 0000000000000000000001000000000000000000 in binary
// as you can see 2^18 bit is high, i.e. the 19th bit

static const char* TAG = "Blinker";
// The tag for the ESP logging functionality

void app_main(void) {
	gpio_config_t gpio_conf = {};
	// define an empty gpio_config_t struct
	gpio_conf.mode = GPIO_MODE_OUTPUT;
	// select output mode 
	gpio_conf.pull_up_en = 0;
	// don't enable the pull-up resistor
	gpio_conf.pull_down_en = 0;
	// don't enable the pull-down resistor
	gpio_conf.intr_type = GPIO_INTR_DISABLE;
	// disable interrupts 
	gpio_conf.pin_bit_mask = GPIO19_PIN_SEL;
	// select GPIO19
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
	// ESP_ERR_CHECK will print the error and return if there is an error
	
	esp_err_t err = 0; // just an error type variable 
					   // to check the returns of the functions
	printf("\n");
	while (1) {
		err = gpio_set_level(GPIO_NUM_19, 1); // set GPIO19 high
		if (err != ESP_OK)
			ESP_LOGE(TAG, "Error Setting GPIO19 HIGH (Error Code: %d)", err);
		else
			ESP_LOGI(TAG, "GPIO19 set HIGH");
		vTaskDelay(1000 / portTICK_PERIOD_MS); // delay for 1 second

		err = gpio_set_level(GPIO_NUM_19, 0); // set GPIO19 low
		if (err != ESP_OK)
			ESP_LOGE(TAG, "Error Setting GPIO19 LOW (Error Code: %d)", err);
		else
			ESP_LOGI(TAG, "GPIO19 set LOW");
		vTaskDelay(1000 / portTICK_PERIOD_MS); // delay for another second
	}
}

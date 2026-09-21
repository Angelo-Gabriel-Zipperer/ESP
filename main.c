#include "esp_bit_defs.h"
#include "freertos/projdefs.h"
#include "hal/gpio_types.h"
#include "soc/gpio_num.h"
#include <driver/gpio.h>
#include <esp_log.h>
#include <esp_sleep.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_A 32
#define LED_B 13

gpio_config_t ledconfig = {		//conf. dos pinos
	.pin_bit_mask=BIT64(LED_A) | BIT64(LED_B),
	.mode=GPIO_MODE_OUTPUT,
	.pull_up_en=GPIO_PULLUP_DISABLE,
	.pull_down_en=GPIO_PULLDOWN_ENABLE,
	.intr_type=GPIO_INTR_DISABLE,
};

void led_task(void *args)	//função de acender e apagar o led
{
	gpio_num_t *pin = (gpio_num_t *)args;
	 
    while (true) {
		gpio_set_level(*pin,1);
		vTaskDelay(pdMS_TO_TICKS(400));
		gpio_set_level(*pin,0);
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

void app_main(void){
	gpio_config(&ledconfig);
	const gpio_num_t led_a_value = LED_A;
	xTaskCreate(&led_task, "led_1", 1024, (void *)&led_a_value, 1, NULL);
	vTaskDelay(pdMS_TO_TICKS(200));
	const gpio_num_t led_b_value = LED_B;
	xTaskCreate(&led_task, "led_2", 1024, (void *)&led_b_value, 1, NULL);
	vTaskDelete(NULL);
}

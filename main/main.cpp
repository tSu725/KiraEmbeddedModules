#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "tca8418.h"
#include "myi2c.h"

static const char *TAG = "MAIN";

extern "C" void app_main(void) {

    ESP_ERROR_CHECK(myi2c_bus_init());
    ESP_LOGI(TAG, "The I2C master bus has been successfully created.");

    tca8418_device_t keyboard;
    esp_err_t ret = tca8418_init(bus_handle, &keyboard);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "TCA8418 is not responding");
        return;
    }
    // You need to implement the pressing/pressing status later.
    while (1) {
        uint8_t pressed_key_code = 0;
        if (tca8418_read_pressed_key(&keyboard, &pressed_key_code)) {
            ESP_LOGI(TAG, "button %d was is pressed", pressed_key_code);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }


}
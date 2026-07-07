#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "driver/i2c_master.h"

typedef struct {
    i2c_master_dev_handle_t i2c_dev;
} tca8418_device_t;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Initialization keyboard TCA8418
 * @param bus_handle handler for an already created I2C bus
 * @param out_device Pointer to the device structure that the function will fill in
 * @param esp_err_t ESP_OK on success
*/
    esp_err_t tca8418_init(i2c_master_bus_handle_t bus_handle, tca8418_device_t *out_device);
/**
 * @brief Check and read pressed key (Non-Blocking function)
 * @param device the pointer to initialized device
 * @param out_key_code 
 * @return true if any key pressed, false if non events
 */
    bool tca8418_read_pressed_key(tca8418_device_t *out_device, uint8_t* out_key_code);
#ifdef __cplusplus
}
#endif
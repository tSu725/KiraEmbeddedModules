#pragma once

#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif
extern i2c_master_bus_handle_t bus_handle;
/**
 * @brief Инициализация глобальной мастер-шины I2C
 * @return esp_err_t ESP_OK при успешном старте
 */
esp_err_t myi2c_bus_init(void);
#ifdef __cplusplus
}
#endif

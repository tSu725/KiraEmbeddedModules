#include "myi2c.h"
#include "esp_log.h"

static const char *TAG = "MYI2C";

static const gpio_num_t SCL_PIN = GPIO_NUM_9;
static const gpio_num_t SDA_PIN = GPIO_NUM_8;

i2c_master_bus_handle_t bus_handle = NULL;
static const i2c_master_bus_config_t i2c_mst_config = {
    .i2c_port = -1,               
    .sda_io_num = SDA_PIN,            
    .scl_io_num = SCL_PIN,             
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,          
    .intr_priority = 0,               
    .trans_queue_depth = 0,          
    .flags = {
        .enable_internal_pullup = true
    }
};

esp_err_t myi2c_bus_init(void) {
    ESP_LOGI(TAG, "Initialization of the shared I2C bus...");
    esp_err_t ret = i2c_new_master_bus(&i2c_mst_config, &bus_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error creating the I2C master bus: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "Master I2C bus has been created");
    }
    return ret;
}

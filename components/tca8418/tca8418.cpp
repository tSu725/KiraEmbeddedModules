#include "tca8418.h"
#include "esp_log.h"

static const char* TAG = "TCA8418";
static const uint8_t cfg_ke_en[] = {0x01, 0x01};

// keyboard device on i2c bus
i2c_device_config_t i2c_dvc_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = 0x34, // addr TCA8418
    .scl_speed_hz = 400000,
    .scl_wait_us = 0,
    .flags = {
        .disable_ack_check = false
    }
};
esp_err_t tca8418_init(i2c_master_bus_handle_t bus_handle, tca8418_device_t* out_device){
    if (out_device == NULL) return ESP_ERR_INVALID_ARG;
    esp_err_t ret = i2c_master_bus_add_device(bus_handle, &i2c_dvc_cfg, &out_device->i2c_dev);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Couldn't add an I2C device: %s", esp_err_to_name(ret));
        return ret;
    }
    ESP_LOGI("MAIN", "The device (0x34) has been successfully registered.");
    uint8_t init_kp1[] = {0x1D, 0xFF}; // from datasheet 
    uint8_t init_kp2[] = {0x1E, 0xFF};
    uint8_t init_kp3[] = {0x1F, 0xFF};
    ret = i2c_master_transmit(out_device->i2c_dev, init_kp1, sizeof(init_kp1), -1);
    if (ret != ESP_OK) { return ret; };
    ret = i2c_master_transmit(out_device->i2c_dev, init_kp2, sizeof(init_kp2), -1);
    if (ret != ESP_OK) { return ret; };
    ret = i2c_master_transmit(out_device->i2c_dev, init_kp3, sizeof(init_kp3), -1);
    if (ret != ESP_OK) { return ret; };
    ret = i2c_master_transmit(out_device->i2c_dev, cfg_ke_en, sizeof(cfg_ke_en), -1);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error writing the configuration register: %s", esp_err_to_name(ret));
        return ret;
    }
    return ESP_OK;
}


bool tca8418_read_pressed_key(tca8418_device_t *out_device, uint8_t* out_key_code) {
    if (out_device == NULL || out_key_code == NULL) {
        return false;
    }
    uint8_t reg_key_lck_ec = 0x03;
    uint8_t reg_key_event_a = 0x04;
    uint8_t reg_int_stat = 0x02;    
    uint8_t event_count = 0;
    uint8_t raw_event = 0;

    esp_err_t ret = i2c_master_transmit_receive(out_device->i2c_dev, &reg_key_lck_ec, 1, &event_count, 1, -1);
    if (ret != ESP_OK) {
        ESP_LOGE("KEYB", "TCA8418 is not responding, code: %s", esp_err_to_name(ret));
        return false; 
    }
    // You need to implement the pressing/pressing status later.
    uint8_t num_events = event_count & 0x0F; 
    if (num_events > 0) {
        ret = i2c_master_transmit_receive(out_device->i2c_dev, &reg_key_event_a, 1, &raw_event, 1, -1);
        if (ret == ESP_OK && raw_event != 0) {
            bool is_pressed = (raw_event & 0x80) != 0;
            if (is_pressed) {
                *out_key_code = raw_event & 0x7F; 
                uint8_t clear_int[] = {reg_int_stat, 0x01};
                i2c_master_transmit(out_device->i2c_dev, clear_int, sizeof(clear_int), -1);
                return true;
            }
        }
    }
    return false;
}




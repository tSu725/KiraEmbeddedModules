# KiraEmbeddedModules

The repository contains a modular firmware/mini-OS implementation for the **M5Stack Cardputer Adv** platform (based on ESP32-S3) using the **ESP-IDF** framework.

## Project structure and components

The project is built according to the ESP-IDF modular scheme. All low-level logic is hidden inside isolated components in the `components/` folder:

* **`main/`** is the application entry point (`app_main') that coordinates the operation of the modules.
* **`components/myi2c/`** is the initialization component of the common I2C master bus. Creates a global bus handle that is accessible to other hardware modules.
* **`components/tca8418/`** is the TCA8418 matrix keyboard controller driver. It works with the hardware FIFO of the chip, filters button release events and provides the operating system with clean pressing codes.


## Assembly and firmware

The development tool **ESP-IDF** (v5.x) is required for compilation.

```bash
# Clearing the cache and configuring the project
idf.py fullclean
idf.py reconfigure

# Firmware compilation
idf.py build

# Writing to the controller and starting
the port monitor idf.py -p /dev/cu.usbmodemXXXX flash monitor
``

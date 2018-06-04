## SHA256 C++ component for ESP-IDF

This is a barely necessary wrapper around mbedTLS sha256 functions, that uses
RAII.

**Note:** this code isn't tested at the moment, it may or may not work correctly

### Installation

#### ESP-IDF build system

Clone this repository into your `components` directory inside the project:

    cd components
    git clone https://github.com/infincia/sha256_espidf.git


#### PlatformIO

Add this repository as a library in your `platformio.ini` file in the root of 
your project:

    [env:development]
    platform = espressif32
    board = esp32dev
    framework = espidf
    lib_deps =
      https://github.com/infincia/sha256_espidf.git#v0.1.0

### Full example of usage

This is a bare minimum `main.cpp` file you can refer to when using this library. 

    #include <esp_err.h>
    #include <esp_log.h>
    static const char *TAG = "[MyProject]";

    #include <sha256_espidf.h>

    uint8_t byte1 = 124;
    uint8_t byte2 = 80;
    uint8_t byte3 = 92;

    extern "C" {
    void app_main();
    }

    int app_main() {
        SHA256 hash;

        hash.update(&byte1, 1);
        hash.update(&byte2, 1);
        hash.update(&byte3, 1);


        uint8_t result[32];

        hash.finish(&result);

        // do something with result

        return 0;
    }

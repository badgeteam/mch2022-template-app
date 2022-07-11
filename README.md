# MCH2022 template app

This repository contains a template app for the MCH2022 badge.
It is intended to be used as the basis for developing your own native ESP32
apps. See [Getting Started](https://badge.team/docs/badges/mch2022/software-development/esp_idf_getting_started/)

## License

The source code contained in the main folder of this example is public domain / CC0 licensed, use it as you please.

Source code included as submodules is licensed separately, please check the
following table for details.

| Submodule                   | License                           | Author                                                 |
|-----------------------------|-----------------------------------|--------------------------------------------------------|
| esp-idf                     | Apache License 2.0                | Espressif Systems (Shanghai) CO LTD                    |
| components/appfs            | THE BEER-WARE LICENSE Revision 42 | Jeroen Domburg <jeroen@spritesmods.com>                |
| components/bus-i2c          | MIT                               | Nicolai Electronics                                    |
| components/i2c-bno055       | MIT                               | Nicolai Electronics                                    |
| components/mch2022-rp2040   | MIT                               | Renze Nicolai                                          |
| components/pax-graphics     | MIT                               | Julian Scheffers                                       |
| components/pax-keyboard     | MIT                               | Julian Scheffers                                       |
| components/sdcard           | MIT                               | Nicolai Electronics                                    |
| components/spi-ice40        | MIT                               | Nicolai Electronics                                    |
| components/spi-ili9341      | MIT                               | Nicolai Electronics                                    |
| components/ws2812           | Unlicense / Public domain         | None                                                   |

## How to make
```sh
git clone --recursive https://github.com/badgeteam/mch2022-template-app
cd mch2022-template-app
make prepare
make
```

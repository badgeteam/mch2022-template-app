
#pragma once

#include "hardware.h"
#include "pax_gfx.h"
#include "pax_codecs.h"
#include "ili9341.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "wifi_connect.h"
#include "wifi_connection.h"
#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"

void disp_flush();
void exit_to_launcher();

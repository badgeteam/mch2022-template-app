
// This file contains a simple hello world app which you can base you own apps on.

#include "main.h"
#include "hardware.h"
#include "pax_gfx.h"
#include "pax_codecs.h"
#include "ili9341.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"

static pax_buf_t pax_buffer;
xQueueHandle buttonQueue;

static const char *TAG = "mch2022-demo-app";

void disp_flush() {
    ili9341_write(get_ili9341(), pax_buffer.buf);
}

void app_main() {
    // Init HW.
    bsp_init();
    bsp_rp2040_init();
    buttonQueue = get_rp2040()->queue;
    
    // Init GFX.
    pax_buf_init(&pax_buffer, NULL, 320, 240, PAX_BUF_16_565RGB);
    
    // Show some hello world.
    pax_background(&pax_buffer, 0xffff00ff);
    disp_flush();
    
    // Just wait.
    while (1) vTaskDelay(10000);
}


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

static pax_buf_t buf;
xQueueHandle buttonQueue;

static const char *TAG = "mch2022-demo-app";

void disp_flush() {
    ili9341_write(get_ili9341(), buf.buf);
}

void app_main() {
    // Init HW.
    bsp_init();
    bsp_rp2040_init();
    buttonQueue = get_rp2040()->queue;
    
    // Init GFX.
    pax_buf_init(&buf, NULL, 320, 240, PAX_BUF_16_565RGB);
    
    while (1) {
        // Pick a random background color.
        int hue = esp_random() & 255;
        pax_col_t col = pax_col_hsv(hue, 255 /*saturation*/, 255 /*brighness*/);
        
        // Show some random color hello world.
        pax_background(&buf, col);
        char             *text = "Hello, World!";
        const pax_font_t *font = pax_get_font("saira condensed");
        pax_vec1_t        dims = pax_text_size(font, font->default_size, text);
        pax_draw_text(
            &buf, 0xff000000, font, font->default_size,
            (buf.width  - dims.x) / 2.0,
            (buf.height - dims.y) / 2.0,
            text
        );
        disp_flush();
        
        // Await any button press and do another cycle.
        rp2040_input_message_t message;
        xQueueReceive(buttonQueue, &message, portMAX_DELAY);
    }
}

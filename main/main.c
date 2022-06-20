
// This file contains a simple hello world app which you can base you own apps on.

#include "main.h"

static pax_buf_t buf;
xQueueHandle buttonQueue;

static const char *TAG = "mch2022-demo-app";

void disp_flush() {
    ili9341_write(get_ili9341(), buf.buf);
}

void exit_to_launcher() {
    REG_WRITE(RTC_CNTL_STORE0_REG, 0);
    esp_restart();
}

void app_main() {
    // Init HW.
    bsp_init();
    bsp_rp2040_init();
    buttonQueue = get_rp2040()->queue;
    
    // Init GFX.
    pax_buf_init(&buf, NULL, 320, 240, PAX_BUF_16_565RGB);
    
    // Init NVS.
    nvs_flash_init();
    
    // Init (but not connect to) WiFi.
    wifi_init();
    
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
        
        if (message.input == RP2040_INPUT_BUTTON_HOME && message.state) {
            // If home is pressed, exit to launcher.
            exit_to_launcher();
        }
    }
}

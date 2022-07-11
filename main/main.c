/*
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "main.h"

static pax_buf_t buf;
xQueueHandle buttonQueue;

static const char *TAG = "mch2022-demo-app";

// Updates the screen with the last drawing.
void disp_flush() {
    ili9341_write(get_ili9341(), buf.buf);
}

// Exits the app, returning to the launcher.
void exit_to_launcher() {
    REG_WRITE(RTC_CNTL_STORE0_REG, 0);
    esp_restart();
}

void app_main() {
    // Init the screen, the I2C and the SPI busses.
    bsp_init();
    // Init the RP2040 (responsible for buttons among other important things).
    bsp_rp2040_init();
    // This queue is used to await button presses.
    buttonQueue = get_rp2040()->queue;
    
    // Init graphics for the screen.
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
        // Draw the background with aforementioned random color.
        pax_background(&buf, col);
        // This text is shown on screen.
        char             *text = "Hello, World!";
        // Pick the font to draw in (this is the only one that looks nice this big).
        const pax_font_t *font = pax_font_saira_condensed;
        // Determine how large the text is so it can be centered.
        pax_vec1_t        dims = pax_text_size(font, font->default_size, text);
        // Use info to draw the centered text.
        pax_draw_text(
            // Buffer to draw to.
            &buf, 0xff000000,
            // Font and size to use.
            font, font->default_size,
            // Position (top left corner) of the app.
            (buf.width  - dims.x) / 2.0,
            (buf.height - dims.y) / 2.0,
            // The text to be shown.
            text
        );
        // Draws the entire graphics buffer to the screen.
        disp_flush();
        
        // Await any button press and do another cycle.
        // Structure used to receive data.
        rp2040_input_message_t message;
        // Await forever (because of portMAX_DELAY), a button press.
        xQueueReceive(buttonQueue, &message, portMAX_DELAY);
        
        // Is the home button currently pressed?
        if (message.input == RP2040_INPUT_BUTTON_HOME && message.state) {
            // If home is pressed, exit to launcher.
            exit_to_launcher();
        }
    }
}

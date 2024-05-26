#include "drivers/video.h"
#include "drivers/video/GraphicsModeDriver.h"
#include "drivers/video/VideoInit.h"
#include "drivers/video/VideoUtil.h"

uint8_t is_text_mode() {
    return _is_text_mode();
}

void print(char* string) {
    _print(string);
}

void println(char* string) {
    _println(string);
}

void clear_screen() {
    _clear_screen();
}
void screen_colour(uint8_t fg, uint8_t bg) {
    _screen_colour(fg, bg);
}

uint8_t set_graphics_mode(uint16_t width, uint16_t height, uint8_t chain4, uint8_t force) {
    uint8_t result;
    if (is_text_mode()) {
        result = _set_graphics_mode(width, height, chain4);
    } else {
        if (force) {
            result = _set_graphics_mode(width, height, chain4);
        }
    }
    return result;
}

void draw_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {
    _draw_pixel(x, y, r, g, b, brightness);
}
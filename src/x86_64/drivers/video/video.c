#include "drivers/video.h"
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
void screen_color(uint8_t fg, uint8_t bg) {
    _screen_colour(fg, bg);
}

uint8_t set_graphics_mode(uint32_t width, uint32_t height, uint8_t chain4, uint8_t force) {
    if (is_text_mode()) {
        uint8_t result = _set_graphics_mode(width, height, chain4);
    } else {
        if (force) {
            uint8_t result = _set_graphics_mode(width, height, chain4);
        }
    }
    return result;
}
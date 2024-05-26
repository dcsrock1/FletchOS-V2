#pragma once

#include "drivers/video/GraphicsModeDriver.h"
#include "util/stdint.h"

enum {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GRAY = 7,
    COLOR_DARK_GRAY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_PINK = 13,
    COLOR_YELLOW = 14,
    COLOR_WHITE = 15,
};

uint8_t is_text_mode();

uint8_t set_graphics_mode(uint16_t width, uint16_t height, uint8_t chain4, uint8_t force);

void draw_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);

void print(char* string);
void println(char* string);

void clear_screen();
void screen_colour(uint8_t fg, uint8_t bg);



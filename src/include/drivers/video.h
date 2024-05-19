#pragma once

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

uint8_t set_graphics_mode(int width, int height,int chain4, uint8_t force);

void print(char* string);
void println(char* string);

void clear_screen();
void screen_colour();



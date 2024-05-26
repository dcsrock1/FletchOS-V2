#pragma once

#include <util/stdint.h>
#include <util/stddef.h>


void _draw_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);
void clear_screen_graphics_mode();


void clear_row_graphics_mode(size_t row);
void print_char_graphics_mode(char character);
void print_graphics_mode(char* string);
void set_colour_graphics_mode(uint8_t fg, uint8_t bg);
#pragma once

#include <util/stdint.h>
#include <util/stddef.h>

void clear_screen_txt_mode();
void clear_row_txt_mode(size_t row);
void print_char_txt_mode(char character);
void print_txt_mode(char* string);
void set_colour_txt_mode(uint8_t fg, uint8_t bg);
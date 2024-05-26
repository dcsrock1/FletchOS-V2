#pragma once

#define VGA_SEQ_INDEX    0x3C4
#define VGA_SEQ_DATA     0x3C5
#define VGA_GC_INDEX     0x3CE
#define VGA_GC_DATA      0x3CF

#include <util/stdint.h>

uint8_t _is_text_mode();

void _print(char* string);
void _println(char* string);

void _clear_screen();
void _screen_colour(uint8_t fg, uint8_t bg);

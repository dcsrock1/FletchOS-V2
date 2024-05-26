#include "drivers/video/VideoUtil.h"
#include "drivers/video/TextModeDriver.h"
#include "drivers/video/GraphicsModeDriver.h"
#include "util/io.h"
#include "util/stdint.h"

uint8_t _is_text_mode() {
    uint8_t seq4, gc6;
    outb(VGA_SEQ_INDEX, 0x04);
    seq4 = inb(VGA_SEQ_INDEX + 1);
    outb(VGA_GC_INDEX, 0x06);
    gc6 = inb(VGA_GC_INDEX + 1);
    if ((seq4 & 0x08) == 0 && (gc6 & 0x01) == 0) {
        return 1; 
    }
    return 0;
}

void _print(char* string) {
    if (_is_text_mode()) {
        print_txt_mode(string);
    } else {
        //print_graphics_mode(string);
    }
}

void _println(char* string) {
    if (_is_text_mode()) {
        print_txt_mode(string);
        _print("\n");
    } else {
        //_print("\n");
        //print_graphics_mode(string);
    }
}

void _clear_screen() {
    if (_is_text_mode()) {
        clear_screen_txt_mode();
    } else {
        clear_screen_graphics_mode();
    }
}
void _screen_colour(uint8_t fg, uint8_t bg) {
    if (_is_text_mode()) {
        set_colour_txt_mode(fg, bg);
    } else {
        //set_colour_graphics_mode();
    }
}
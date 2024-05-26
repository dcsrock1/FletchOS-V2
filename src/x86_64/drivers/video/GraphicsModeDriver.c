#include <drivers/video/GraphicsModeDriver.h>
#include <drivers/video/VideoUtil.h>
#include <util/io.h>


void vga_set_plane(uint8_t p) {
   p &= 3;
   uint8_t pmask = 1 << p;
   outb(VGA_GC_INDEX, 4);
   outb(VGA_GC_DATA, p);
   outb(VGA_SEQ_INDEX, 2);
   outb(VGA_SEQ_DATA, pmask);
}

void _draw_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {
    volatile uint8_t* loc = (uint8_t*) 0xA0000 + 400 * y + x;
    vga_set_plane(0);
    *loc = brightness;
    vga_set_plane(1);
    *loc = r;
    vga_set_plane(2);
    *loc = g;
    vga_set_plane(3);
    *loc = b;
}

void clear_screen_graphics_mode() {
    for (int i = 0; i < 240000; i++) {
        uint16_t y = i / 400;
        uint16_t x = i - (y * 400);
        _draw_pixel(x, y, 0, 0, 0, 255);
    }
    
}
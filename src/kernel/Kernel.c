#include <drivers/video.h>
#include <util/string.h>
#include <drivers/memory.h>
#include <drivers/pic.h>
#include <drivers/idt.h>
#include <drivers/memory/paging.h>

void kernel_entry() {
    setup_paging();
}

void kernel_main() {
    clear_screen();
    screen_colour(COLOR_WHITE,COLOR_BLACK);
    println("Welcome to 64 bit mode");
    init_memory();
    pic_disable();
    PIC_remap(0x20, 0xA0);
    init_IDT();
}

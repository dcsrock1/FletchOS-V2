#include "drivers/video.h"

void kernel_main() {
    clear_screen();
    screen_color(COLOR_WHITE, COLOR_BLACK);
    println("Welcome to 64 bit mode");
}
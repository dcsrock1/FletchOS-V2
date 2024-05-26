#include <drivers/ISR/keyboard.h>
#include <drivers/pic.h>
#include <drivers/video.h>

void keyboard_driver() {
    PIC_sendEOI(1);
    println("PRESSED");
    return;
}
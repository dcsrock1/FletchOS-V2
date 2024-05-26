#include <drivers/ISR/exceptions.h>
#include <drivers/video.h>

void NMI() {
    println("NMI Triggered");
}

void brkINT() {
    println("Break Point Triggered");
}

void double_fault() {
    println("Double Fault Triggered");
}

void TSSF() {
    println("TSS Fault Triggered");
}

void SNF() {
    println("Segment Not Found");
}

void SSF() {
    println("Stack Segment Fault");
}

void GPF() {
    println("General Protection Fault");
}

void PF() {
    println("Page Fault");
}
#include "drivers/video/TextModeDriver.h"
#include "drivers/video.h"

const static size_t COLS = 80;
const static size_t ROWS = 25;

struct Char { 
    uint8_t character;
    uint8_t colour;
};

struct Char* buffer = (struct Char*) 0xB8000;
size_t col = 0;
size_t row = 0;
uint8_t colour = COLOR_WHITE | COLOR_BLACK << 4;

void clear_row_txt_mode(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        colour: colour,
    };
    for (size_t col = 0; col < COLS; col++) {
        buffer[col + COLS * row] = empty;
    }
}

void clear_screen_txt_mode() {
    for (size_t i = 0; i < ROWS; i++) {
        clear_row_txt_mode(i);
    }
}

void print_newline() {
    col = 0;
    if (row < ROWS - 1) {
        row++;
        return;
    }
    for (size_t row = 1; row < ROWS; row++) {
        for (size_t col = 0; col < COLS; col++) {
            struct Char character = buffer[col + COLS * row];
            buffer[col + COLS * (row - 1)] = character;
        }
    }

    clear_row_txt_mode(COLS - 1);
}
void print_char_txt_mode(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col > COLS) {
        print_newline();
    }

    buffer[col + COLS * row] = (struct Char) {
        character: (uint8_t) character,
        colour: colour,
    };
    col++;
}

void print_txt_mode(char* str) {
    for (size_t i = 0; 1; i++) {
        for (size_t i = 0; 1; i++) {
            char character = (uint8_t) str[i];
            if (character == '\0') {
                return;
            }
            print_char_txt_mode(character);
        }
    }
}

void set_colour_txt_mode(uint8_t fg, uint8_t bg) {
    colour = fg + (bg << 4);
}
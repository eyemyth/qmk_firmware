#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"


/*
 * Matt3o's WhiteFox
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PTD0, PTD1, PTD4, PTD5, PTD6, PTD7, PTC1, PTC2 }
 *     row: { PTB2, PTB3, PTB18, PTB19, PTC0, PTC8, PTC9, PTC10, PTC11 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;


void matrix_init(void)
{
//debug_matrix = true;
    /* Column(sense) */
    palSetPadMode(TEENSY_PIN1_IOPORT, TEENSY_PIN1, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN2_IOPORT, TEENSY_PIN2, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN3_IOPORT, TEENSY_PIN3, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN4_IOPORT, TEENSY_PIN4, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN5_IOPORT, TEENSY_PIN5, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN6_IOPORT, TEENSY_PIN6, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN7_IOPORT, TEENSY_PIN7, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN20_IOPORT, TEENSY_PIN20, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN21_IOPORT, TEENSY_PIN21, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN22_IOPORT, TEENSY_PIN22, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN24_IOPORT, TEENSY_PIN24, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN25_IOPORT, TEENSY_PIN25, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN26_IOPORT, TEENSY_PIN26, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN31_IOPORT, TEENSY_PIN31, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN32_IOPORT, TEENSY_PIN32, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(TEENSY_PIN33_IOPORT, TEENSY_PIN33, PAL_MODE_INPUT_PULLUP);

    /* Row(strobe) */
    palSetPadMode(TEENSY_PIN8_IOPORT, TEENSY_PIN8,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(TEENSY_PIN9_IOPORT, TEENSY_PIN9,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(TEENSY_PIN10_IOPORT, TEENSY_PIN10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(TEENSY_PIN11_IOPORT, TEENSY_PIN11, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(TEENSY_PIN12_IOPORT, TEENSY_PIN12, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(TEENSY_PIN15_IOPORT, TEENSY_PIN15, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(TEENSY_PIN16_IOPORT, TEENSY_PIN16, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(TEENSY_PIN17_IOPORT, TEENSY_PIN17, PAL_MODE_OUTPUT_PUSHPULL);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        // strobe row
        switch (row) {
            case 0: palSetPad(TEENSY_PIN8_IOPORT,  TEENSY_PIN8);    break;
            case 1: palSetPad(TEENSY_PIN9_IOPORT,  TEENSY_PIN9);    break;
            case 2: palSetPad(TEENSY_PIN10_IOPORT, TEENSY_PIN10);   break;
            case 3: palSetPad(TEENSY_PIN11_IOPORT, TEENSY_PIN11);   break;
            case 4: palSetPad(TEENSY_PIN12_IOPORT, TEENSY_PIN12);   break;
            case 5: palSetPad(TEENSY_PIN15_IOPORT, TEENSY_PIN15);   break;
            case 6: palSetPad(TEENSY_PIN16_IOPORT, TEENSY_PIN16);   break;
            case 7: palSetPad(TEENSY_PIN17_IOPORT, TEENSY_PIN17);   break;
        }

        wait_us(20); // need wait to settle pin state

        // read col data
        data = ((palReadPad(TEENSY_PIN1_IOPORT, TEENSY_PIN1)==PAL_HIGH) ? 0 : (1<<0))
         | ((palReadPad(TEENSY_PIN2_IOPORT, TEENSY_PIN2)==PAL_HIGH) ? 0 : (1<<1))
         | ((palReadPad(TEENSY_PIN3_IOPORT, TEENSY_PIN3)==PAL_HIGH) ? 0 : (1<<2))
         | ((palReadPad(TEENSY_PIN4_IOPORT, TEENSY_PIN4)==PAL_HIGH) ? 0 : (1<<3))
         | ((palReadPad(TEENSY_PIN5_IOPORT, TEENSY_PIN5)==PAL_HIGH) ? 0 : (1<<4))
         | ((palReadPad(TEENSY_PIN6_IOPORT, TEENSY_PIN6)==PAL_HIGH) ? 0 : (1<<5))
         | ((palReadPad(TEENSY_PIN7_IOPORT, TEENSY_PIN7)==PAL_HIGH) ? 0 : (1<<6))
         | ((palReadPad(TEENSY_PIN20_IOPORT, TEENSY_PIN20)==PAL_HIGH) ? 0 : (1<<7))
         | ((palReadPad(TEENSY_PIN21_IOPORT, TEENSY_PIN21)==PAL_HIGH) ? 0 : (1<<8))
         | ((palReadPad(TEENSY_PIN22_IOPORT, TEENSY_PIN22)==PAL_HIGH) ? 0 : (1<<9))
         | ((palReadPad(TEENSY_PIN24_IOPORT, TEENSY_PIN24)==PAL_HIGH) ? 0 : (1<<10))
         | ((palReadPad(TEENSY_PIN25_IOPORT, TEENSY_PIN25)==PAL_HIGH) ? 0 : (1<<11))
         | ((palReadPad(TEENSY_PIN26_IOPORT, TEENSY_PIN26)==PAL_HIGH) ? 0 : (1<<12))
         | ((palReadPad(TEENSY_PIN31_IOPORT, TEENSY_PIN31)==PAL_HIGH) ? 0 : (1<<13))
         | ((palReadPad(TEENSY_PIN32_IOPORT, TEENSY_PIN32)==PAL_HIGH) ? 0 : (1<<14))
         | ((palReadPad(TEENSY_PIN33_IOPORT, TEENSY_PIN33)==PAL_HIGH) ? 0 : (1<<15));

        // un-strobe row
        switch (row) {
            case 0: palClearPad(TEENSY_PIN8_IOPORT,  TEENSY_PIN8);    break;
            case 1: palClearPad(TEENSY_PIN9_IOPORT,  TEENSY_PIN9);    break;
            case 2: palClearPad(TEENSY_PIN10_IOPORT, TEENSY_PIN10);   break;
            case 3: palClearPad(TEENSY_PIN11_IOPORT, TEENSY_PIN11);   break;
            case 4: palClearPad(TEENSY_PIN12_IOPORT, TEENSY_PIN12);   break;
            case 5: palClearPad(TEENSY_PIN15_IOPORT, TEENSY_PIN15);   break;
            case 6: palClearPad(TEENSY_PIN16_IOPORT, TEENSY_PIN16);   break;
            case 7: palClearPad(TEENSY_PIN17_IOPORT, TEENSY_PIN17);   break;
        }

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }
    matrix_scan_quantum();
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    xprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                xprintf("1");
            else
                xprintf("0");
        }
        xprintf("\n");
    }
}

/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "i2c_stm32.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

__attribute__ ((weak))
void matrix_init_user(void) {
}

void matrix_init_kb(void) {
  i2c_init();
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_scan_kb(void) {
    matrix_scan_user();
}


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

/* Maple Mini */
#ifdef BOARD_MAPLEMINI_STM32_F103
#define LED_ON()    do { palSetPad(GPIOB, 1) ;} while (0)
#define LED_OFF()   do { palClearPad(GPIOB, 1); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOB, 1); } while (0)
#endif

void matrix_init(void) {
    debug_enable = true;
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        wait_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            wait_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    matrix_scan_quantum();

    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

/* Column pin configuration
 */
static void  init_cols(void)
{
  palSetGroupMode(MATRIX_COL_PORT, MATRIX_COL_MASK, col_pins[0], PAL_MODE_INPUT_PULLUP);
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
    return ~(palReadGroup(MATRIX_COL_PORT, MATRIX_COL_MASK, col_pins[0]));
}

/* Row pin configuration
 */
static void unselect_rows(void)
{
    // palSetPadMode(GPIOA, GPIOA_PIN10, PAL_MODE_INPUT); // hi-Z
    palSetGroupMode(MATRIX_ROW_PORT, MATRIX_ROW_MASK, row_pins[0], PAL_MODE_INPUT);
}

static void select_row(uint8_t row)
{
  palSetPadMode(MATRIX_ROW_PORT, row_pins[row], PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(MATRIX_ROW_PORT, row_pins[row]);
}

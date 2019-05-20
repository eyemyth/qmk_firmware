#include <stdbool.h>
#include "ps2_io.h"
#include "quantum.h"

/*
 * Clock
 */
void clock_init(void) {
  setPinInput(PS2_CLOCK_PIN);
}

void clock_lo(void) {
  setPinOutput(PS2_CLOCK_PIN);
  writePinLow(PS2_CLOCK_PIN);
}
void clock_hi(void) {
  setPinOutput(PS2_CLOCK_PIN);
  writePinHigh(PS2_CLOCK_PIN);
}

bool clock_in(void) {
  setPinInput(PS2_CLOCK_PIN);
  return readPin(PS2_CLOCK_PIN);
}

/*
 * Data
 */
void data_init(void) {
  setPinInput(PS2_DATA_PIN);
}

void data_lo(void) {
  setPinOutput(PS2_DATA_PIN);
  writePinLow(PS2_DATA_PIN);
}

void data_hi(void) {
  setPinOutput(PS2_DATA_PIN);
  writePinHigh(PS2_DATA_PIN);
}

bool data_in(void) {
  setPinInput(PS2_DATA_PIN);
  return readPin(PS2_DATA_PIN);
}

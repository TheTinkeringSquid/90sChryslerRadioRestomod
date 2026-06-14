// buttons.cpp — SKELETON.
#include "buttons.h"
#include "pins.h"
// #include <Arduino.h>

void Buttons::begin() {
  // TODO: pinMode(INPUT_PULLUP) for direct buttons:
  //   SEEK_UP/DOWN, AMFM, SET.
  // TODO: init I/O expander over I2C for the rest; add ESD/series R in HW.
}

void Buttons::poll(uint32_t now_ms, UiStateMachine& sm) {
  (void)now_ms; (void)sm;
  // TODO: read raw states (direct GPIO + expander), debounce, detect edges,
  // measure hold time, then sm.dispatch(...) the matching UiEvent
  // (e.g. AMFM short vs AMFM_LONG_PRESS at kLongPressMs).
}

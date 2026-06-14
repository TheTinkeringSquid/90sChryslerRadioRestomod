// buttons.h — button scanning + debounce + short/long press -> UiEvent.
// Handles direct-GPIO buttons and (if OQ-4 says matrixed) an I/O-expander block.
#pragma once
#include <stdint.h>
#include "ui_state_machine.h"

class Buttons {
 public:
  void begin();
  // Scan inputs, debounce, classify short/long, and dispatch UiEvents to `sm`.
  void poll(uint32_t now_ms, UiStateMachine& sm);

 private:
  // TODO: per-button debounce state + press-time for long-press detection.
  // TODO: I/O-expander read (I2C_ADDR_IOEXP) for PRESET_1..5, H, M, EJT, FFWD, RWD.
  static constexpr uint16_t kDebounceMs   = 25;
  static constexpr uint16_t kLongPressMs  = 700;
};

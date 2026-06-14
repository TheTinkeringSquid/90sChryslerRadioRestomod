// controls.h — analog control reading (volume/balance/fader/bass/treble[/tune]).
// Reads pots/sliders via ESP32 ADC1 (and/or an external I2C ADC, see pin-map),
// filters, and emits *_CHANGE UiEvents when a control moves past a threshold.
#pragma once
#include <stdint.h>
#include "ui_state_machine.h"

struct ControlValues {       // normalized 0..255 (post-filter)
  uint8_t volume = 0;
  uint8_t balance = 128;     // 128 = center
  uint8_t fader = 128;       // 128 = center
  uint8_t bass = 128;
  uint8_t treble = 128;
  uint8_t tune = 0;          // only if tune is a pot (OQ-7)
};

class Controls {
 public:
  void begin();
  void poll(uint32_t now_ms, UiStateMachine& sm);  // dispatch *_CHANGE on movement
  const ControlValues& values() const { return v_; }

 private:
  ControlValues v_;
  // TODO: hysteresis/EMA per channel to reject ADC jitter (esp. with BT RF on).
  // NOTE: ADC2 unusable with BT active -> keep analog controls on ADC1 / ext ADC.
  static constexpr uint8_t kChangeThreshold = 2;  // LSB of normalized value
};

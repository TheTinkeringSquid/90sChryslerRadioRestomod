// settings.h — persistent settings + presets in NVS/flash.
// Stores presets (5 x 2 banks), time zone, DST, 12/24h, last source, tone/levels,
// and BT pairing state. See docs/ui-state-machine.md "Persistence".
#pragma once
#include <stdint.h>

struct Preset {
  uint8_t  band;        // 0 = AM, 1 = FM
  uint32_t freq_khz;    // stored station
  bool     valid;
};

struct PersistentSettings {
  Preset  presets[2][5];      // [bank][slot]
  int8_t  tz_offset = 0;      // hours
  bool    dst = false;
  bool    fmt24 = false;
  uint8_t last_source = 0;    // maps to UiState source
  uint8_t volume = 0;
  uint8_t balance = 128, fader = 128, bass = 128, treble = 128;
};

class Settings {
 public:
  bool begin();               // open NVS namespace; load() or defaults
  bool load();
  bool save();                // persist current `data`
  PersistentSettings data;    // working copy

 private:
  // TODO: ESP32 Preferences/NVS handle; namespace + key scheme; write throttling
  // (avoid wearing flash on every knob tick — debounce saves).
};

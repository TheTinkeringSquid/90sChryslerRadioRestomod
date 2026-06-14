// display.h — display abstraction (original VFD glass OR green-LED replacement).
// UI talks to this interface; the concrete driver is selected after Phase 0
// (OQ-1/OQ-2). See docs/display-options.md.
#pragma once
#include <stdint.h>

enum class DisplayIcon : uint8_t { NR, SET, BANK1, BANK2, TAPE, FFWD, RWD };

class Display {
 public:
  bool begin();                          // init chosen driver (VFD or LED)
  void clear();

  void showFrequency(uint32_t khz, bool fm);   // "AM 1010" / "FM 101.1"
  void showClock(uint8_t hh, uint8_t mm, bool fmt24);
  void showText(const char* s);          // "BT" / "BLUE" / status

  void setIcon(DisplayIcon icon, bool on);
  void setBrightness(uint8_t level);     // from dimmer input

 private:
  // TODO: pImpl or virtual driver: VfdDriver (MAX6921/PT631x/HT16512 + HV/filament)
  // vs LedDriver (HT16K33/MAX7219/TLC5940). Segment/icon map from RE notes.
};

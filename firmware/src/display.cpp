// display.cpp — SKELETON.
#include "display.h"

bool Display::begin() {
  // TODO: instantiate VFD or LED driver based on build flag / runtime config.
  return true;
}

void Display::clear()                                  { /* TODO */ }
void Display::showFrequency(uint32_t khz, bool fm)     { (void)khz; (void)fm; /* TODO */ }
void Display::showClock(uint8_t hh, uint8_t mm, bool f){ (void)hh; (void)mm; (void)f; /* TODO */ }
void Display::showText(const char* s)                  { (void)s; /* TODO */ }
void Display::setIcon(DisplayIcon icon, bool on)       { (void)icon; (void)on; /* TODO */ }
void Display::setBrightness(uint8_t level)             { (void)level; /* TODO */ }

// audio.cpp — SKELETON.
#include "audio.h"
#include "pins.h"
// #include <Arduino.h>

bool Audio::begin() {
  // TODO: pinMode(PIN_AMP_MUTE/STBY, OUTPUT); muteAmp(true); ampStandby(true);
  // TODO: init codec over I2C/I2S; init audio processor; set flat defaults.
  return true;  // TODO: return false on codec/AP init failure -> ERROR_MODE
}

bool Audio::selectSource(AudioSource s) {
  // TODO: soft-mute -> route mux/processor input -> settle -> unmute.
  source_ = s;
  return true;
}

void Audio::setVolume(uint8_t v) { (void)v; /* TODO: ramped volume in codec/AP */ }
void Audio::setBalance(uint8_t b){ (void)b; /* TODO */ }
void Audio::setFader(uint8_t f)  { (void)f; /* TODO */ }
void Audio::setBass(uint8_t b)   { (void)b; /* TODO */ }
void Audio::setTreble(uint8_t t) { (void)t; /* TODO */ }

void Audio::muteAmp(bool mute)        { (void)mute;    /* TODO: digitalWrite */ }
void Audio::ampStandby(bool standby)  { (void)standby; /* TODO: digitalWrite */ }
void Audio::enableAmpAfterDelay()     { /* TODO: delay then unmute/active */ }

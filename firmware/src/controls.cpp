// controls.cpp — SKELETON.
#include "controls.h"
#include "pins.h"
// #include <Arduino.h>

void Controls::begin() {
  // TODO: analogReadResolution(12); configure ADC1 channels
  //   (VOL/BAL/FADER/BASS/TREBLE[/TUNE]) and/or external I2C ADC.
  // TODO: prime filters with an initial read so we don't fire a change at boot.
}

void Controls::poll(uint32_t now_ms, UiStateMachine& sm) {
  (void)now_ms;
  // TODO: read each channel, normalize to 0..255, EMA-filter, and if the change
  // exceeds kChangeThreshold, update v_ and dispatch the matching event, e.g.:
  //   sm.dispatch(UiEvent::VOL_CHANGE);
}

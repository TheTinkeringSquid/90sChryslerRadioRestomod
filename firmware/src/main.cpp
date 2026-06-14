// main.cpp — application entry. Wires subsystems together and runs the loop.
// SKELETON: structure is real; subsystem bodies are TODO in their modules.
//
// Target: ESP32 with Bluetooth Classic (WROOM-32 / WROVER). NOT ESP32-S3.

// #include <Arduino.h>
#include "pins.h"
#include "settings.h"
#include "audio.h"
#include "controls.h"
#include "buttons.h"
#include "tuner_si4735.h"
#include "bluetooth_audio.h"
#include "clock_wwvb.h"
#include "display.h"
#include "cassette.h"
#include "ui_state_machine.h"

static Settings        g_settings;
static Audio           g_audio;
static Controls        g_controls;
static Buttons         g_buttons;
static TunerSi4735     g_tuner;
static BluetoothAudio  g_bt;
static ClockWwvb       g_clock;
static Display         g_display;
static Cassette        g_cassette;
static UiStateMachine  g_ui;

// Real Arduino entry points (commented so the skeleton doesn't require the
// toolchain to be present just to read it). Uncomment when building.
/*
void setup() {
  Serial.begin(115200);

  g_settings.begin();
  g_display.begin();

  // Bring up audio first (amp stays muted), then sources. ERROR_MODE on failure.
  bool ok = g_audio.begin();
  ok &= g_tuner.begin();
  ok &= g_bt.begin("B2500 Radio");
  g_clock.begin();
  g_cassette.begin();

  g_controls.begin();
  g_buttons.begin();

  g_ui.begin();                 // settles to last source from settings
  if (ok) g_audio.enableAmpAfterDelay();  // anti-pop: enable amp after init
}

void loop() {
  const uint32_t now = millis();

  g_buttons.poll(now, g_ui);    // -> dispatch button UiEvents
  g_controls.poll(now, g_ui);   // -> dispatch *_CHANGE UiEvents
  g_cassette.poll(now);         // -> tape present/eject edges
  g_clock.poll(now);            // -> WWVB decode / RTC
  g_ui.tick(now);               // timers, blink, timeouts

  // TODO: BT/AVRCP/HFP callbacks feed g_ui.dispatch(...) (BT_CONNECTED, etc.)
}
*/

// Placeholder so the translation unit is non-empty under any build config.
int firmware_skeleton_marker = 0;

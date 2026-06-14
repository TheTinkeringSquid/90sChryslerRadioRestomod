# Project Summary

## The vehicle and the radio

- **Vehicle:** 1996 Dodge B2500 Ram Van, Elkhart Conversion Vans high-top,
  3.9L Magnum V6, 3-speed auto, blue interior, short wheelbase.
- **Radio:** Factory Chrysler/Dodge/Jeep AM/FM cassette head unit, RAS-style,
  **P/N P04858531**. Two rear connector groups: one power/illumination/control,
  one speaker.
- **Bench-test result:** Radio is **confirmed dead**. The project is therefore a
  *replacement main electronics board*, not a Bluetooth add-on to a working unit.

## The goal

Replace the dead internals with custom ESP32-based electronics while keeping the
radio indistinguishable from stock on the outside. Reuse the factory faceplate,
knobs, buttons, sliders, display window, and cassette controls. Add modern
features that a 1996 factory deck never had, hidden entirely inside the chassis.

## Feature set

**Retain (factory):** AM/FM, volume + power knob, tune, balance, fader, seek
up/down, bass/treble sliders, AM/FM mode button, SET, presets 1–5 (two banks),
H/M clock buttons, EJT/FFWD/RWD cassette controls, the green segmented display
with its NR / SET / 1 / 2 / tape / FFWD / RWD icons.

**Add (new, invisible):**
- Bluetooth A2DP audio as a third source on the AM/FM button (`AM → FM → BT`).
- Hands-free calling (HFP) with an external microphone.
- WWVB 60 kHz radio-controlled clock with RTC fallback.
- Repurposed clock buttons: **H = time-zone / hours offset**, **M = 12/24-hour
  toggle** (clock auto-syncs, so manual hour/minute setting is no longer primary).

## Architecture in one paragraph

An **ESP32 with Bluetooth Classic** (WROOM-32 / WROVER — *not* an S3, which is
BLE-only) runs the UI state machine and talks I²C to a **Si4735** tuner and an
**I²S audio codec** (WM8960 / ES8388 for DAC **and** mic ADC). Three stereo
sources — tuner, Bluetooth, cassette — are selected by an audio mux / audio
processor that also applies digitally-read volume / tone / balance / fader, then
feed a **4-channel automotive BTL amplifier** (TDA7388 / TDA7850-class) wired to
the factory speaker harness. A **WWVB** module and optional **DS3231** drive the
clock. Power comes from automotive-hardened 12 V with buck-derived 5 V and 3.3 V
rails.

## Guiding constraints

No touchscreen. Factory controls and look preserved. Bluetooth lives on the
existing AM/FM button. One custom PCB where practical. Survives a real vehicle
electrical environment. See [factory-functions.md](factory-functions.md) for
per-control behavior and [open-questions.md](open-questions.md) for the unknowns
that gate the design.

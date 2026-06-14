# Firmware Tests

PlatformIO unit tests (`pio test`). Empty for now — add host-runnable (`native`)
tests for the pure-logic modules that don't need ESP32 hardware:

- **UI state machine** — feed `UiEvent`s, assert resulting `UiState` and the
  `AM → FM → BT → AM` cycling.
- **WWVB decoder** — feed canned bit frames, assert decoded time / sync-fail
  handling on noisy input.
- **Settings** — serialize/deserialize round-trip of presets and preferences.

Hardware-dependent modules (audio, tuner, BT, display, cassette) are validated on
the bench per [../../docs/bringup-test-plan.md](../../docs/bringup-test-plan.md),
not here.

> To run host tests, add a `[env:native]` section to `platformio.ini` and place
> tests under `test/test_<name>/`.

# Firmware

PlatformIO / Arduino-framework firmware for the ESP32 controller. **This is a
scaffold** — module interfaces are defined; bodies are marked `TODO`. It mirrors
the design docs, especially [../docs/ui-state-machine.md](../docs/ui-state-machine.md)
and [../docs/pin-map.md](../docs/pin-map.md).

> ⚠️ Use an ESP32 with **Bluetooth Classic** (WROOM-32 / WROVER). The S3 is
> BLE-only and cannot do A2DP/HFP this project needs (OQ-19).

## Build

```bash
pio run                 # build (esp32dev)
pio run -t upload       # flash
pio device monitor      # serial @ 115200
```

`setup()` / `loop()` in [src/main.cpp](src/main.cpp) are intentionally commented
so the scaffold reads without requiring the toolchain installed. Uncomment them
(and the `lib_deps` in [platformio.ini](platformio.ini)) as modules are
implemented.

## Module map

| File | Responsibility |
|---|---|
| `main.cpp` | wires subsystems, runs the loop |
| `pins.h` | ⚠️ placeholder pin assignments (sync with docs/pin-map.md) |
| `ui_state_machine.{h,cpp}` | states, events, mode cycling, behavior |
| `buttons.{h,cpp}` | scan + debounce + short/long press → events |
| `controls.{h,cpp}` | ADC vol/bal/fader/bass/treble[/tune] → `*_CHANGE` |
| `audio.{h,cpp}` | source routing, vol/tone/bal/fade, amp mute/standby |
| `tuner_si4735.{h,cpp}` | AM/FM tuner abstraction |
| `bluetooth_audio.{h,cpp}` | A2DP + AVRCP + HFP abstraction |
| `clock_wwvb.{h,cpp}` | WWVB decode + DS3231 fallback + TZ/format |
| `display.{h,cpp}` | VFD-or-LED display abstraction |
| `cassette.{h,cpp}` | tape sense (L1) + transport control (L2) |
| `settings.{h,cpp}` | NVS persistence: presets, TZ, format, levels |

## Implementation order (suggested, tracks the phases)
1. `settings`, `display`, `controls`, `buttons` — local I/O on the bench.
2. `tuner_si4735` — AM/FM (Phase 1 POC).
3. `audio` — routing + anti-pop.
4. `bluetooth_audio` — A2DP, then AVRCP, then HFP (gated).
5. `clock_wwvb` — RTC first, WWVB decode second.
6. `cassette` — Level 1, then Level 2.

## TODO conventions
- `TODO` = implement.  `⚠`/`OQ-n` = blocked on a teardown unknown
  ([../docs/open-questions.md](../docs/open-questions.md)).
- Don't hardcode pins that are still placeholders; resolve the four conflicts in
  `docs/pin-map.md` first.

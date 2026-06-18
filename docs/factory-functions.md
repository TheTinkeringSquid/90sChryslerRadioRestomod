# Factory Faceplate Functions → Restomod Behavior

Every control identified from the radio photos/discussion, the factory behavior,
and the intended restomod behavior. Behaviors marked **(TBD)** depend on Phase 0
teardown or a later UI decision.

## Knobs

### Volume / Power knob (combined)
- **Factory:** click on/off + rotate for volume.
- **Restomod:** keep click-on/off as radio power; keep rotary volume.
- **Implementation:** switch portion → `RADIO_ON` / ACC-detect / standby logic;
  pot read by ESP32 ADC, volume applied digitally in codec/audio processor.
  Prefer reusing the original pot mechanically. (TBD: pot value/taper/condition.)

### Tune knob
- **Factory:** manual AM/FM station tuning.
- **Restomod:** keep manual tuning. If pot → ADC or convert to step behavior; if
  encoder → quadrature on GPIO interrupts. (TBD: pot vs encoder — see RE notes.)

### Balance knob (behind volume) — L/R
### Fader knob (behind tune) — front/rear
- **Factory:** analog balance / fade.
- **Restomod:** keep both; read as ADC and apply channel gains in the audio
  processor (preferred), or keep in analog path if original design supports it.

## Buttons

### Seek up / Seek down
- **Factory:** seek up/down through the band to next station.
- **Restomod:** keep seek for AM/FM. In BT mode, optionally track next/prev or
  inactive.

### AM/FM (mode) button — **repurposed**
- **Factory:** selects AM or FM.
- **Restomod:** cycles `AM → FM → BT → AM` (short press). **Must remain the mode
  button — no new visible control.**
- Long press in BT mode → enter Bluetooth pairing.
- Display shows AM freq / FM freq / `BT` (or `BLUE`) per mode.

### SET button
- **Factory:** long press sets favorites for presets 1–5; short press toggles
  display between clock and station; lights `SET` icon while setting; two preset
  banks shown by lower-right `1`/`2`.
- **Restomod:** retain preset-setting workflow; retain short-press clock/source
  toggle; preserve two banks if practical. Avoid stealing SET for Bluetooth
  unless a long-press/combo keeps factory-style usage intact.

### Preset buttons 1–5
- **Factory:** store/recall presets across two banks; display shows `1`/`2`.
- **Restomod:** keep 5 buttons + 2 banks. AM/FM store band+frequency (+ optional
  signal settings). BT: presets optional/ignored or mapped to BT actions only in
  BT mode. Factory feel prioritized.

### H button — **repurposed**
- **Factory:** adjust hour when setting clock.
- **Restomod:** clock is radio-controlled, so H becomes **time-zone / hours
  offset** ("Home zone"). Long press → enter TZ setting; short press in that mode
  → cycle offset.

### M button — **repurposed**
- **Factory:** adjust minutes when setting clock.
- **Restomod:** **12/24-hour (Military time) toggle.** Keeps the printed `M`
  meaningful.

### EJT button
- **Factory:** eject tape. **Restomod:** **required** — eject is part of full
  transport control (cassette is a required source).

### FFWD / RWD buttons
- **Factory:** fast-forward / rewind cassette.
- **Restomod:** **required** cassette transport (FFWD/RWD driven by the ESP32). In
  BT mode they may also map to next/prev track. Cassette behavior takes priority
  when a tape is loaded.

## Display (green segmented)

- **Factory:** shows time or station; SET short press toggles content.
- **Icons:** `NR`, `SET`, `1`, `2`, tape, FFWD arrow, RWD arrow.
- **Restomod:** retain green appearance — reuse original glass if feasible, else
  green LED 7-seg + discrete icon LEDs behind the original window.

| Icon | Factory meaning | Restomod use |
|---|---|---|
| `NR` | Likely cassette Dolby/noise reduction (exact behavior unknown) | Optional NR/tape indicator, or cautiously repurposed |
| `SET` | Active while setting preset/clock | Settings/preset/clock-adjust mode |
| `1` / `2` | Active preset bank | Active preset bank |
| Tape | Cassette present/active | Tape inserted or cassette mode |
| FFWD / RWD | Transport active | Active tape transport state |

See [display-options.md](display-options.md) for the VFD-vs-LED decision and
[ui-state-machine.md](ui-state-machine.md) for how modes drive the display.

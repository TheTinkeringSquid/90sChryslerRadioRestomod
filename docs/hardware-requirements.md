# Hardware Requirements

Block-by-block specification for the replacement main board. Final parts must be
verified for availability, automotive suitability, and KiCad library support.

## System block diagram

```text
Vehicle 12V
   |-- Fuse / reverse-polarity protection / TVS / EMI filter
   |-- 12V_AMP (filtered) ----------> 4-channel speaker amplifier
   |-- 5V buck ---------------------> codec, display (opt), tuner (opt)
   |-- 3.3V regulator --------------> ESP32, logic, tuner control, button logic

Factory faceplate controls
   |-- buttons / matrix / ADC --> ESP32 GPIO / ADC / I/O or ADC expander

Audio sources                       Display
  1. Si4735 AM/FM   L/R \             ESP32 -> VFD driver OR LED driver
  2. BT via I2S codec L/R >-- mux/   Clock
  3. Cassette        L/R /   audio    WWVB module -> ESP32 ; optional RTC -> ESP32
        |                proc         Microphone
        v             (vol/tone/      Mic -> codec ADC -> ESP32 BT HFP
   4-ch automotive amp  bal/fade)
        v
   Factory speaker connector (BTL, do NOT ground speaker negatives)
```

## 1. Main controller
- **ESP32 with Bluetooth Classic** (A2DP + HFP). Candidate: ESP32-WROOM-32 or
  ESP32-WROVER. **Do not use ESP32-S3** (BLE only — no Classic A2DP/HFP).
- Responsibilities: UI state machine, tuner control, BT control, audio source
  switching, display, WWVB/clock, presets + settings storage (NVS/flash),
  button/knob scanning.

## 2. Audio codec / DAC / ADC
- Need DAC (BT music out) **and** ADC + mic bias (hands-free in).
- Preferred: **WM8960** or **ES8388** (I²S, stereo DAC+ADC, mic bias).
- Phase-1 music-only fallback: **PCM5102A** I²S DAC (no mic ADC).

## 3. AM/FM tuner
- **Si4735** (or similar). I²C control, analog L/R out, antenna from factory jack.
- Behaviors: manual tune, seek up/down, presets (5 × 2 banks), band+freq display.
- Antenna: factory Motorola-style input preferred (TH jack footprint, or
  U.FL/coax + adapter). Observe RF layout best practices, short controlled trace.

## 4. Audio source switching
- Select among tuner / BT / cassette. Options: low-distortion analog switches
  (TS3A-series, MAX4544/MAX4xxx) or a dedicated I²C audio processor with input
  select. Requirements: low noise, stereo, automotive temp, mute/soft switching
  to avoid pops.

## 5. Tone / volume / balance / fader
- **Chosen approach (dead-radio replacement): ADC-read controls + digital/audio-
  processor control.** Cleaner multi-source integration, consistent levels,
  storable settings.
- Possible devices: TDA7313 / TDA7439-style audio processor, or modern I²C
  automotive audio processor, or a capable codec/DSP.
- Analog-in-path (Option B) rejected as primary: unknown pot impedance/taper/
  condition and harder multi-source mixing. See [audio-architecture.md](audio-architecture.md).

## 6. Speaker amplifier
- 4-channel BTL, automotive 12 V, mute/standby, thermal management.
- Candidates: **TDA7388**, **TDA7850**, similar 4-ch automotive amp.
- Class AB = period-correct, runs hot; Class D = efficient but EMI risk near
  AM/FM/WWVB. Chassis may serve as heatsink if mechanically coupled.
- Outputs FL± FR± RL± RR± — **BTL/floating, never tie negatives to ground.**

## 7. Cassette integration
- Phase in. Min (Level 1): bring stereo cassette line-level audio in + tape-in
  sense. Full (Level 2): ESP32 controls motor/FFWD/RWD/eject + sensors.
- Provide generic cassette connector (see [cassette-integration.md](cassette-integration.md)).

## 8. Display driver
- **Preferred:** original VFD glass → HV boost (~25–40 V), filament supply
  (~2–4 V), VFD driver (MAX6921 / PT631x / HT16512-class — pick after pin map).
- **Fallback:** green LED 7-seg + discrete icon LEDs via HT16K33 / MAX7219 /
  TLC5940 / shift registers. Expose SPI/I²C/GPIO to a modular display connector
  so the project can proceed before the VFD is decoded. See
  [display-options.md](display-options.md).

## 9. WWVB receiver
- Header: VCC (3.3 V/5 V selectable), GND, DATA, ENABLE. Keep away from buck
  regulators / amp / ESP32 RF / speaker wiring. Input filtering + ESD. Consider
  shielded cable to a better antenna location.

## 10. Microphone
- 3-pin electret: MIC_BIAS, MIC_IN, MIC_GND/shield. Optional digital MEMS header
  (3.3 V, GND, I²S/PCM). Clean analog layout. Mic best mounted external
  (visor/A-pillar), not inside the metal chassis.

## 11. Power & robustness
- Input fuse, reverse-polarity protection, automotive TVS, LC/PI filtering, bulk
  caps, separate filtered analog/RF rails. Rails: `12V_IN`, `12V_AMP`, `5V_SYS`,
  `3V3_LOGIC`. ESP32 controls amp mute/standby; delay amp enable after codec init
  (anti-pop); mute before shutdown. See [power-protection.md](power-protection.md).

## 12. PCB
- Preferred **4-layer** (top signal / GND plane / power+GND / bottom signal) for
  RF + audio + power cleanliness. 2-layer possible but worse for AM/FM RF, BT RF,
  WWVB 60 kHz sensitivity, audio noise, amp currents.
- Placement: buck away from tuner/audio/WWVB/mic; amp near rear connector +
  chassis heatsink; ESP32 antenna area clear of copper; tuner near antenna;
  codec/mux near audio path; display driver near display connector.
- Mechanical (board outline, mounting holes, connector/shaft positions, display
  window, tape clearance, chassis ground points) — **UNKNOWN until teardown.**

## Connector inventory
See [pin-map.md](pin-map.md) and section "Connectors" below. All vehicle-side,
faceplate, display, and cassette pinouts are **placeholders pending teardown.**

| Connector | Purpose | Pinout source |
|---|---|---|
| Power/illumination | BATT/ACC/GND/ILLUM/DIMMER/AMP_REMOTE/spare | RE notes (TBD) |
| Speaker | FL± FR± RL± RR± (BTL) | RE notes (TBD) |
| Front panel | ADC controls + buttons (+matrix?) + 3V3/5V/GND | RE notes (TBD) |
| Display | 30–40 pin VFD/LED daughterboard | RE notes (TBD) |
| Cassette | audio in + transport/sense + motor | RE notes (TBD) |
| Microphone | MIC_BIAS/MIC_IN/shield | design choice |
| Antenna | Motorola/U.FL | design choice |
| Programming/debug | 3V3/GND/TX/RX/EN/BOOT + test pads | design choice |

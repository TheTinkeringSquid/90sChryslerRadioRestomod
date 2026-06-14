# ESP32 Pin Map — ⚠️ PLACEHOLDER

**Every assignment here is provisional.** It exists so firmware can compile and
so the schematic has a starting point. Final pins depend on Phase 0 teardown
(button matrix vs individual, encoder vs ADC, expander needs) and ESP32 module
strapping/ADC2 constraints. This table is the human-readable mirror of
[../firmware/src/pins.h](../firmware/src/pins.h) — **keep them in sync.**

## ESP32 hardware constraints to respect
- **ADC2 pins are unusable while Wi-Fi/BT radio is active.** With Bluetooth
  Classic always on, **all analog controls must use ADC1** (GPIO32–39).
- GPIO34–39 are **input-only** (no pull-ups) — fine for ADC, not for outputs.
- Strapping pins (0, 2, 5, 12, 15) — avoid driving at boot; GPIO6–11 are flash.
- There are ~6 usable ADC1 channels but **7 analog controls** (vol, bal, fader,
  bass, treble, + maybe tune). → likely need an **external ADC or I/O expander**,
  or an analog mux, or matrixed buttons to free pins. (OQ-4/OQ-5/OQ-7.)

## Analog controls (ADC1 only)
| Net | Provisional GPIO | Notes |
|---|---|---|
| `VOL_ADC` | 36 (input-only) | from volume pot |
| `BAL_ADC` | 39 (input-only) | balance |
| `FADER_ADC` | 34 (input-only) | fader |
| `BASS_ADC` | 35 (input-only) | bass slider |
| `TREBLE_ADC` | 32 | treble slider |
| `TUNE_ADC` | 33 | **if** tune is a pot (OQ-7); else use TUNE_A/B encoder |

> Already 6 ADC1 pins for 6 controls — **no ADC1 headroom left.** If the tune
> knob is a pot AND we keep all sliders on the ESP32, an **external ADC (I²C)** is
> required. Recommended: move bass/treble/balance/fader to an I²C ADC and keep
> volume + tune local. Decide after OQ-5/OQ-7.

## Digital controls / buttons
*(If buttons are matrixed (OQ-4), replace these with row/col pins + scan.)*
| Net | Provisional GPIO | Notes |
|---|---|---|
| `TUNE_A` | 25 | encoder A (if encoder) |
| `TUNE_B` | 26 | encoder B (if encoder) |
| `BTN_SEEK_UP` | 27 | |
| `BTN_SEEK_DOWN` | 14 | |
| `BTN_AMFM` | 13 | mode cycle / pairing (long) |
| `BTN_SET` | 23 | |
| `BTN_PRESET_1..5` | via expander | likely matrix/expander |
| `BTN_H` | via expander | TZ/hours offset |
| `BTN_M` | via expander | 12/24 toggle |
| `BTN_EJT` | via expander | cassette |
| `BTN_FFWD` | via expander | cassette / BT next |
| `BTN_RWD` | via expander | cassette / BT prev |

## Buses
| Bus | Pins | Devices |
|---|---|---|
| I²C0 | SDA=21, SCL=22 | Si4735, audio processor, DS3231, I/O expander, ext ADC |
| I²S | BCLK=5*, LRCK=25**, DOUT=19, DIN=18, MCLK=0* | codec (WM8960/ES8388) |

\* GPIO0/5 are strapping pins — verify against module; relocate if boot issues.
\** LRCK collides with TUNE_A above — **placeholder conflict, resolve in schematic.**

## Control / status lines
| Net | Provisional GPIO | Dir | Notes |
|---|---|---|---|
| `AMP_MUTE` | 4 | out | amp mute (active state TBD) |
| `AMP_STBY` | 16 | out | amp standby |
| `WWVB_DATA` | 17 | in | demodulated time signal |
| `WWVB_EN` | 2* | out | receiver enable (strapping — verify) |
| `DIMMER_SENSE` | 35? | in | conflicts w/ BASS — needs its own ADC ch |
| `RADIO_ON` | 15* | in | from volume-knob power switch |

## ⚠️ Known placeholder conflicts to resolve at schematic time
1. ADC1 oversubscribed (6 controls + dimmer sense + maybe tune pot) → add I²C ADC.
2. `TUNE_A`(25) vs I²S `LRCK`(25) collision.
3. Several pins are strapping/boot-sensitive (0, 2, 5, 15) — verify or relocate.
4. Preset/H/M/EJT/FFWD/RWD assume an I/O expander; confirm after OQ-4.

Resolve all four before committing the schematic. Until then, treat pin numbers
as labels, not commitments.

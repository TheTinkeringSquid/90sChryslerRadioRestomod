# Reverse-Engineering Notes (Phase 0 Capture)

**Status: EMPTY — to be filled during teardown.** Do not fabricate values. Every
`TODO` here gates a hardware/firmware decision elsewhere. Photograph and label
everything *before* removing boards.

> **Follow [teardown-protocol.md](teardown-protocol.md)** — it is the
> step-by-step field guide that tells you exactly how to capture each value
> below (e.g. VFD-vs-LCD test, button-matrix probing, pot taper, encoder check,
> cassette motor V/I). This file is where the results land. Section numbers here
> match the protocol's stages.

## 0. Identification
- Part number: **P04858531** (RAS-style AM/FM cassette)
- Serial: **T 53 AH 151 6 P1453**
- Application (per online listings): OEM Chrysler/Dodge/Jeep AM/FM cassette used
  c. **1994–2001** (Ram, Caravan/Voyager, etc.). Mitsubishi-built family.
- Bench test: **dead** (confirmed)
- Bench pigtail for reference: **Metra 71-1817** (reverse harness — plugs into OEM
  radio). NOT 70-1817 (that's the vehicle-side aftermarket adapter).

## 1. Original PCB
- [ ] Photo: top side → `../mechanical/chassis-photos/`
- [ ] Photo: bottom side
- [ ] Microcontroller P/N: `TODO`
- [ ] Amplifier IC P/N: `TODO`
- [ ] Tuner section P/N: `TODO`
- [ ] Cassette preamp IC P/N: `TODO`
- [ ] Voltage regulator P/N(s): `TODO`
- [ ] Display driver IC P/N: `TODO`
- [ ] Board outline (mm) + mounting hole positions: `TODO`

## 2. Display
- [ ] Type: VFD / LCD / other → `TODO` (likely VFD)
- [ ] Glass pinout (filament / grids / segments / icons): `TODO`
- [ ] Filament voltage: `TODO`
- [ ] Anode/grid voltage: `TODO`
- [ ] Segment/grid truth table: `TODO`
- [ ] Connection type: ribbon / pins / soldered → `TODO`
- [ ] Display window inner dimensions (mm): `TODO`

## 3. Faceplate controls
- [ ] Connection: ribbon / pins / soldered → `TODO`
- [ ] Buttons: individual / matrix / resistor-ladder → `TODO`
- [ ] If matrix: row/col map → `TODO`
- Pots/sliders — measure R, taper, condition:
  - [ ] Volume (+ power switch): `TODO`
  - [ ] Tune (pot **or** encoder?): `TODO`
  - [ ] Balance: `TODO`
  - [ ] Fader: `TODO`
  - [ ] Bass slider: `TODO`
  - [ ] Treble slider: `TODO`

## 4. Cassette mechanism
- [ ] Separable from logic board? `TODO`
- [ ] Reusable preamp board? `TODO`
- [ ] Tape head output level: `TODO`
- [ ] Motor voltage / current: `TODO`
- [ ] Tape-present switch present? `TODO`
- [ ] End-of-tape detection? `TODO`
- [ ] FFWD/RWD mechanism (motor/solenoid): `TODO`
- [ ] Eject behavior: `TODO`

## 5. Rear harness connectors

### 5a. Vehicle-side wire chart (from online sources — REFERENCE, verify on van)
Consolidated from the12volt + Dodge forums for the **1995–97 Dodge Ram** factory
radio connector (same-era Chrysler unit; the B-van harness should match but
**colors may differ — confirm with a meter on the actual van in Phase 6**).
This is *function → wire color*, NOT radio-side pin numbers (those come from §1
teardown). It's enough to build a bench pigtail with the Metra 71-1817.

| Function | Wire color | Notes / conflicts |
|---|---|---|
| Constant 12V (BATT) | **Red** (some sources: Pink) | fused, hot at all times |
| Switched 12V (ACC/IGN) | **Red/White** | hot in accessory/run |
| Ground | chassis / mounting strap | chart lists "n/a" as a wire |
| Illumination | (often combined w/ dimmer) | chart lists "n/a" separately |
| Dimmer | **Orange/White** (some: Orange) | panel-lamp dimming |
| Antenna trigger / power-antenna / amp-on | **Yellow** | the "blue AMP/ANT" note in the handoff = Infinity/power-antenna option; verify |
| Left Front (+) | **Dark Green** | door 6×9 |
| Left Front (−) | **Brown/Red** | BTL — not grounded |
| Right Front (+) | **Purple** | |
| Right Front (−) | **Dark Blue/Red** | BTL |
| Left Rear (+) | **Brown/Yellow** | side-panel 5¼ |
| Left Rear (−) | **Brown/Light Blue** | BTL |
| Right Rear (+) | **Dark Blue/White** | |
| Right Rear (−) | **Dark Blue/Orange** | BTL |

Antenna is at the **right-front** of the radio. All four speaker outputs are
**BTL/floating** (negatives are NOT ground) — matches the design requirement.

### 5b. Radio-side connector pinout (by physical pin) — from teardown
- Power/illumination connector: map pin number → function via continuity (§Stage H
  of teardown protocol): `TODO`
- Speaker connector: map pin number → FL±/FR±/RL±/RR±: `TODO`
- Antenna jack type: likely **Motorola-style** (standard for this era) — confirm: `TODO`

> No public factory schematic / service manual exists for P04858531 (proprietary
> Mitsubishi-built Chrysler unit; service was United Radio's domain). Internal
> nets must be reverse-engineered per the teardown protocol.

## 6. Mechanical / chassis
- [ ] Internal volume after removing original electronics: `TODO`
- [ ] Chassis usable as amp heatsink? `TODO`
- [ ] Chassis grounding points: `TODO`
- [ ] Shaft locations (for knob alignment): `TODO`
- [ ] Tape mechanism clearance: `TODO`
- → record dimensioned values in [../mechanical/measurements.md](../mechanical/measurements.md)

## Deliverables
- Photo archive (`../mechanical/chassis-photos/`, `../mechanical/faceplate-photos/`)
- Pinout notes (this file)
- Mechanical sketch + measurements
- Initial RE notes feeding [pin-map.md](pin-map.md) and the schematic

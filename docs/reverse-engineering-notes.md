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
- Power/illumination connector pinout: `TODO`
  - Look for: BATT_12V, ACC_12V, GND, ILLUM, DIMMER, AMP_REMOTE
  - Era note: orange/white = illumination/dimmer; blue = AMP/ANT (Infinity/power
    antenna) — **verify on the actual van.**
- Speaker connector pinout (FL± FR± RL± RR±): `TODO`
- Antenna jack type (Motorola?): `TODO`

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

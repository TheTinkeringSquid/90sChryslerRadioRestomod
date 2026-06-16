# Reverse-Engineering Notes (Phase 0 Capture)

**Status: IN PROGRESS — first teardown photos received 2026-06-16.** Findings
below are tagged **[PHOTO]** when confirmed from the disassembly images
(`../mechanical/chassis-photos/`, `../mechanical/faceplate-photos/`) and `TODO`
when they still need a meter/measurement or a sharper macro shot. Do not
fabricate values.

> **Follow [teardown-protocol.md](teardown-protocol.md)** — it is the
> step-by-step field guide that tells you exactly how to capture each value
> below (e.g. VFD-vs-LCD test, button-matrix probing, pot taper, encoder check,
> cassette motor V/I). This file is where the results land. Section numbers here
> match the protocol's stages.
>
> **What's still needed → [next-capture-punchlist.md](next-capture-punchlist.md)**
> (round-2 to-do; Priority 1 = legible IC part numbers).

## 0. Identification
- Part number: **P04858531** (RAS-style AM/FM cassette)
- Serial: **T 53 AH 151 6 P1453**
- Application (per online listings): OEM Chrysler/Dodge/Jeep AM/FM cassette used
  c. **1994–2001** (Ram, Caravan/Voyager, etc.). Mitsubishi-built family.
- Bench test: **dead** (confirmed)
- Bench pigtail for reference: **Metra 71-1817** (reverse harness — plugs into OEM
  radio). NOT 70-1817 (that's the vehicle-side aftermarket adapter).

## 1. Original PCB
- [x] **[PHOTO]** Top side → `chassis-photos/main-pcb-top.jpg`, closeup
  `chassis-photos/main-pcb-closeup-u4-st.jpg`. Board is a single main logic/RF
  board with the rear pin header along the bottom edge; "WAVE SOLDER DIRECTION"
  silk. Refdes seen: U4 (**ST**-branded DIP — STMicro µC or EEPROM), L2 (white
  box inductor), P2 + J2 connectors, Q19, C68/C73/C74/C77/C107.
- [ ] Photo: bottom/solder side of MAIN board (not yet captured)
- [ ] Microcontroller P/N: `TODO` — **need sharp macro** (large SOIC on main board)
- [ ] Amplifier IC P/N: `TODO` — chassis-mounted power IC, see
  `chassis-photos/chassis-heatsink-amp-label.jpg`; **need sharp macro** (likely
  TDA-class 4-ch BTL)
- [ ] Tuner section P/N: `TODO` — **need sharp macro**
- [ ] Cassette preamp IC P/N(s): `TODO` — two DIP ICs on the preamp board
  (`chassis-photos/cassette-preamp-and-motor.jpg`); likely playback preamp +
  Dolby-B NR (explains the `NR` display icon). **Need sharp macro.**
- [ ] Voltage regulator P/N(s): `TODO`
- [ ] Display driver IC P/N: `TODO` — on faceplate board near VFD; **need macro**
- [ ] Board outline (mm) + mounting hole positions: `TODO` (measure)

> **Biggest remaining gap = legible IC markings.** The current photos are too
> blurry/dim to read part numbers. Sharp, well-lit macro shots of each IC top
> would let the exact tuner / amp / µC / preamp / display-driver chips be
> identified (and datasheets pulled) — that drives several design choices.

## 2. Display
- [x] **[PHOTO] Type: VFD — CONFIRMED.** Green vacuum-fluorescent glass on the
  faceplate board (`faceplate-photos/faceplate-front-vfd-buttons.jpg`). Lit
  layout reads: `AM`/`FM` annunciators (left), the numeric field `1 8.8.` with a
  colon (frequency *and* clock), and `NR` / `SET` / `1` / `2` icons (right).
  Tape + FFWD/RWD arrow icons per factory set. Resolves **OQ-1**.
- [x] **[PHOTO]** Connection: VFD is **soldered to the faceplate PCB** via a
  single inline pin row along its bottom edge (not a separate connector).
- [ ] Glass pinout (filament / grids / segments / icons): `TODO` — map pins from
  the inline row; filament pins = the low-ohm outer pair.
- [ ] Filament voltage: `TODO` (measure; typical 2–4 V AC for this size)
- [ ] Anode/grid voltage: `TODO` (typical 25–40 V)
- [ ] Segment/grid truth table: `TODO` (powered probe, later task)
- [ ] Display window inner dimensions (mm): `TODO` (measure for LED-fallback fit)

> Design impact: a VFD means the new board needs a **boost rail (~25–40 V) + a
> low-voltage filament supply + a VFD driver** (e.g. MAX6921 / HT16515-class) if
> we reuse the glass — or a green-LED module behind the window as the fallback.
> Decision deferred until the pin map + segment count are known.

## 3. Faceplate controls
- [x] **[PHOTO]** Connection: **ribbon cable** — a ~14-conductor gray flex ribbon
  joins the faceplate board to the main board (`faceplate-front-vfd-buttons.jpg`,
  `faceplate-board-solder-side.jpg`). A second small white sub-board carries two
  of the rotary pots and is tied in by a short wire harness
  (`control-pots-board-1.jpg`). Resolves **OQ-3**.
- [ ] Buttons: individual / matrix / resistor-ladder → `TODO` (probe) —
  **[PHOTO]** discrete tactile switches **S201–S207+** are on the faceplate
  board; with only ~14 ribbon lines feeding buttons + VFD + pots, they are
  **almost certainly matrix-scanned** — confirm the row/col map with a meter.
- [ ] If matrix: row/col map → `TODO`
- **[PHOTO]** Illumination = discrete lamps/LEDs **LP201–LP208** distributed
  across the faceplate (clear light-pipes over the knobs). Drive a dimmable
  equivalent from the new board (ties to the DIMMER input).
- Pots/sliders — **[PHOTO]** present as rotary pots **A201/A202/A203** (gold
  shafts, on the faceplate + the small sub-board) and **slider pots** (the
  slotted black bodies near R209). Still need values/tapers:
  - [ ] Volume (+ power switch): `TODO` (measure R + test click-switch terminals)
  - [ ] Tune (pot **or** encoder?): `TODO` — none of the visible controls is
    obviously an encoder; tuning may be a pot or handled by seek buttons. Verify.
  - [ ] Balance: `TODO`
  - [ ] Fader: `TODO`
  - [ ] Bass slider: `TODO`
  - [ ] Treble slider: `TODO`
  - Markings on the pot bodies (e.g. `A201`, value codes) → **need macro** to read.

## 4. Cassette mechanism
- [x] **[PHOTO]** Separable from logic board? **Yes** — self-contained
  metal-framed transport with its own preamp PCB; connects to the main board by a
  flat ribbon + the motor leads (`cassette-mechanism-overview.jpg`). Resolves
  **OQ-8**.
- [x] **[PHOTO]** Reusable preamp board? **Yes (likely)** — dedicated preamp PCB
  on the transport with two DIP ICs and the head wiring
  (`cassette-preamp-and-motor.jpg`); silk includes an `EIA232D`/`P620…` marking.
  Trace its line-level L/R output for `CAS_L_IN/CAS_R_IN`. Partially resolves
  **OQ-9** (reuse feasible; exact preamp IC P/N still `TODO`).
- [ ] Tape head output level: `TODO` (scope at preamp output)
- [x] **[PHOTO]** Motor voltage: **DC 13.2 V** (motor label `MMH-5N3LKP DC13.2V`).
  Running **current** still `TODO` (current-limited ramp). Resolves voltage half
  of **OQ-10** — note 13.2 V = run straight off the protected 12 V rail.
- [ ] Tape-present switch present? `TODO` (leaf switches visible on frame — map)
- [ ] End-of-tape detection? `TODO`
- [ ] FFWD/RWD mechanism (motor/solenoid): `TODO` — visible gear train + a wound
  coil/solenoid near the right of the transport; identify actuation.
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
- [ ] Internal volume after removing original electronics: `TODO` (measure)
- [x] **[PHOTO]** Chassis usable as amp heatsink? **Yes** — the original power amp
  IC is bolted to a vented sheet-metal bracket that is part of the chassis
  (`chassis-heatsink-amp-label.jpg`). Reuse the same thermal path for the new amp.
  Resolves **OQ-13**. Chassis label seen: `0474544x / 1890 DFC 3X5 562 / …608`.
- [ ] Chassis grounding points: `TODO`
- [ ] Shaft locations (for knob alignment): `TODO` (measure → measurements.md)
- [ ] Tape mechanism clearance: `TODO`
- → record dimensioned values in [../mechanical/measurements.md](../mechanical/measurements.md)

## Deliverables
- Photo archive (`../mechanical/chassis-photos/`, `../mechanical/faceplate-photos/`)
- Pinout notes (this file)
- Mechanical sketch + measurements
- Initial RE notes feeding [pin-map.md](pin-map.md) and the schematic

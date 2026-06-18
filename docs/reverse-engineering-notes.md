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
- [x] **[PHOTO/VIDEO]** Top side → `main-pcb-top.jpg`,
  `mainboard-front-ic-u11-u12.jpg`, `mainboard-front-ic-u4-u7.jpg`.
- [x] **[VIDEO 2026-06-17]** Bottom/solder side → `mainboard-back-solder.jpg`
  (SMD passives + wave-solder joints; refdes R2/R5/R8/R10/R49/R72/C105/C109,
  U3/U9). Good for net tracing later.

### Main-board ICs (read from the 2026-06-17 videos)
> **Key result: the signal-path ICs are CUSTOM CHRYSLER/ACUSTAR MASKS, not
> standard catalog parts.** They carry Chrysler `0474xxxx` numbers over
> Motorola/ST house markings, so they are **not identifiable or reusable** as
> off-the-shelf devices. This firmly justifies the "replace all electronics"
> approach — the original tuner/µC/DSP cannot be repurposed.

| Ref | Markings | Notes |
|---|---|---|
| U12 | **Motorola `04745268`** / `HDN9617` | large DIP (~40-pin) — likely the microcontroller / system control |
| U11 | **Motorola `04745269 B`** / `XAB9617` | DIP-20 — custom (audio/tuner control?) |
| U7  | **Motorola `SC417964CP` / `04745177 07` / `ACUSTAR 96`** / `1D25AHLTH9616` | DIP under a `04517064 TOYO` metal RF shield → signal/IF processor |
| U4  | **ST**-branded DIP-28 (mask code only) | peripheral / EEPROM (custom) |
| —   | shielded **tuner can** (silver module, top edge by antenna) | RF front end |
| —   | chassis/tag: `TEMIC`, `04745443` | manufacturer + chassis P/N |

- [x] **Amplifier IC: not capturable** — it is a power IC **clamped against the
  chassis wall at the rear edge** (the long metal heatsink bar); its face/markings
  point at the chassis, so they can't be photographed without unbolting it. It is
  a standard 4-ch automotive BTL amp class; exact P/N unread. Irrelevant to the
  redesign (we choose our own, e.g. TDA7388). Heatsink path confirmed (see §6).
- [ ] Voltage regulator P/N(s): `TODO` (not yet isolated)
- [x] **Display driver: none on faceplate** (see §2) — VFD is driven from the
  main board over the ribbon; the driver is likely U11/U12 or a dedicated main-
  board device (custom mask). New design supplies its own VFD driver regardless.
- [ ] Board outline (mm) + mounting hole positions: `TODO` (measure)

> Conclusion: chip-level RE is **done to the extent it's useful**. The customs
> can't be sourced; the redesign uses modern equivalents (Si4735 tuner, ESP32,
> WM8960/ES8388 codec, TDA-class amp, our own VFD driver). The remaining gaps
> that actually gate the new board are the **interfaces** (connector pin
> numbering, button matrix, pot values) and **mechanical** dims — not these ICs.

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
- [x] **[VIDEO 2026-06-16]** **No dedicated VFD driver IC on the faceplate.** A
  full pan of the faceplate solder side shows only small passives, two
  transistors (Q201/Q202), tiny U201/U202, and the ribbon connector P201 — no
  large driver SOIC. ⇒ the VFD is **driven from the main board over the ~14-pin
  ribbon** (dedicated driver or direct µC VFD-drive on the main board). Look for
  the driver when imaging the main board.

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
- **[VIDEO 2026-06-16]** Faceplate board no. **04745184**. Ref-des inventory for
  the matrix map: buttons **S201–S207**, lamps **LP201–LP208**, pots
  **A201–A203**, sliders near **R209**, transistors **Q201/Q202**, small
  **U201/U202**, ribbon connector **P201** (~14-pin). Button/lamp lines all leave
  via P201, reinforcing the matrix-scan hypothesis (OQ-4).

## 4. Cassette mechanism
- [x] **[PHOTO]** Separable from logic board? **Yes** — self-contained
  metal-framed transport with its own preamp PCB; connects to the main board by a
  flat ribbon + the motor leads (`cassette-mechanism-overview.jpg`). Resolves
  **OQ-8**.
- [x] **[VIDEO 2026-06-17]** Reusable preamp board? **Yes** — dedicated preamp PCB
  **`04832548`** (silk `P6-30 / 9620 / 1WA30 / 4293170 / ASSEMBLED IN MEXICO`),
  see `cassette-preamp-toshiba-04832548.jpg`. Unlike the main board, these are
  **standard catalog ICs** (reusable / sourceable):
  - **Toshiba `TA770xP`** (≈TA7705P/TA7668 family, date code `9547`) — cassette
    playback preamp.
  - Second DIP with Hitachi-style mark `HA12134`-ish — likely the **Dolby-B noise
    reduction** IC (explains the `NR` display icon). *Confirm P/N with a macro.*
  - Trace the line-level L/R output for `CAS_L_IN/CAS_R_IN`. Resolves **OQ-9**.
- [ ] Tape head output level: `TODO` (scope at preamp output)
- [x] **[PHOTO/VIDEO]** Motor voltage: **DC 13.2 V** (capstan motor label
  `MMI-6N3LKP DC13.2V 12APD6S1`). Running **current** still `TODO` (current-
  limited ramp). Resolves voltage half of **OQ-10** — 13.2 V = run straight off
  the protected 12 V rail via a motor driver.
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

### 5c. Metra/EIA aftermarket color code (from the harness-bag label)
`metra-eia-harness-label.jpg` is the **Metra adapter bag label** — i.e. the
standard **aftermarket** colors the **Metra 71-1817 pigtail presents on its
flying leads**. Use this for bench wiring the new board to the Metra pigtail.
**Three different color systems exist — don't confuse them:** (1) these
Metra/EIA leads, (2) the Chrysler *vehicle-side* dash colors in §5a, and (3) the
radio's own *physical pin numbering* in §5b (still TODO).

| Function | Metra/EIA lead color |
|---|---|
| 12V Ignition / ACC | Red |
| 12V Battery / Memory | Yellow |
| Ground | Black |
| Power Antenna | Blue |
| Amp Turn-on | Blue/White |
| Amp Ground | Black/White |
| Illumination | Orange |
| Dimmer | Orange/White |
| Phone Mute | Brown |
| Right Front +/− | Gray / Gray-Black |
| Left Front +/− | White / White-Black |
| Right Rear +/− | Violet / Violet-Black |
| Left Rear +/− | Green / Green-Black |

(Generic Metra label — `Phone Mute`/`Amp Turn-on` leads may have no counterpart on
this radio; confirm against the actual connector in §5b.)

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

# Phase 0 — Teardown, Measurement & Pinout-Probing Protocol

A single-pass field procedure to capture **every** datum the design is currently
blocked on. Work through it in order. Each step says **what to do**, **what to
record**, **where it goes** (which repo file), and **which open question (OQ) it
closes**. If you finish this with all boxes checked, the design is unblocked.

> **Golden rules**
> 1. **Photograph before you remove anything.** Every connector mated, every
>    board in place, both sides. You cannot re-photograph an assembled radio
>    after it's in pieces.
> 2. **Label as you disconnect.** Masking-tape flag on every connector/wire with
>    a name that matches the photo.
> 3. **Bag screws by stage.** Zip bag per stage, labeled.
> 4. **Measure twice, write it down once.** Numbers go in the repo, not memory.
> 5. **Don't cut or desolder anything in this pass.** This is non-destructive
>    capture. Reuse decisions come later.

---

## 0. Tools & supplies

**Essential**
- Digital multimeter (continuity/beeper, resistance, DC volts, diode mode)
- Digital calipers (mm) + a steel rule
- Camera/phone with macro; good light
- Masking tape + fine marker; small zip bags
- Precision screwdrivers (Phillips #0/#1, small flat), plastic spudger/pry tools
- Anti-static mat or strap (the original µC/codec may be reused/probed)
- Bench DC power supply **with adjustable current limit** (for the cassette motor)
- Graph paper or calipers + sketchpad for the mechanical datum drawing

**Very helpful (borrow if you can)**
- Oscilloscope — confirms encoder A/B, tape-head/pre-amp signals, display drive
- LCR meter or component tester — fast pot value/taper, cap/inductor ID
- USB microscope — reading tiny IC part numbers
- Helping-hands / PCB holder

**Optional**
- Thermal camera (find the original amp/regulator hotspots by analogy)

---

## Stage A — External documentation (before opening)

1. Photograph the **face** straight-on, filling the frame (used to scale the
   faceplate). Include a rule in one shot.
2. Photograph **both rear connectors** and the **antenna jack**; note jack style
   (Motorola/DIN ~ 2.5 mm pin?). → **OQ-17**
3. Record the label/PN again (expect **P04858531**) and any date codes.
4. Measure overall sleeve/chassis **W × H × D** (mm).

**Record:** PN/date codes + overall dims → `mechanical/measurements.md` (Chassis);
antenna jack style → `docs/reverse-engineering-notes.md` §5.

---

## Stage B — Open the chassis & separate sub-assemblies

1. Remove case screws (bag them, "Stage B"). Note screw locations on a photo.
2. Slide/lift the top and bottom covers. Photograph the **first internal view of
   each side before touching anything**.
3. Identify the major sub-assemblies and how they interconnect:
   - Main logic/PCB
   - Front-panel/faceplate board (controls + display)
   - Cassette mechanism (+ any separate tape preamp board)
4. Photograph **every inter-board connector mated**, then label each end before
   unmating. Note connector type (ribbon / pin header / FFC / soldered wires).

**Record:** interconnect map + connector types →
`docs/reverse-engineering-notes.md` §1 and §3 (faceplate connection → **OQ-3**).

---

## Stage C — Identify & record ICs (do not desolder)

For each board, photograph both sides at macro, then read and record part
numbers (USB scope helps) for:

| Function | Where to look | Closes |
|---|---|---|
| Microcontroller | Largest IC near faceplate connector | RE §1 |
| Audio amplifier | Big IC on a heatsink/chassis tab, near speaker connector | RE §1 |
| Tuner section | Near antenna input; can-shielded module | RE §1 |
| Cassette preamp | Near tape-head wires (small analog IC) | RE §1, **OQ-9** |
| Voltage regulator(s) | Near power connector | RE §1 |
| Display driver | Near the display connector/glass | RE §1, **OQ-1** hint |

**Record:** all part numbers → `docs/reverse-engineering-notes.md` §1.
(Look each up later; the display driver PN often reveals VFD vs LCD immediately.)

---

## Stage D — Mechanical measurements

Define **one datum corner** of the main PCB (e.g. front-left). Reference all X,Y
to it (X = right, Y = back), in mm.

1. **Main PCB outline:** W × D, thickness, and any non-rectangular cutouts.
2. **Mounting holes:** X,Y of each + hole Ø. (Drives the new board's mounting.)
3. **Shaft centers:** volume, tune, balance, fader — X,Y + shaft Ø + panel-to-
   board depth. (Knobs must line up with the faceplate.)
4. **Slider positions/travel:** bass, treble — start/end X,Y.
5. **Display window:** inner W × H, and standoff depth from board to glass.
6. **Cassette envelope:** W × H × D and clearance to the main board.
7. **Rear connector positions** + keying orientation; **antenna jack** position.
8. **Max component height / keep-outs** on each side.

**Record:** every value → `mechanical/measurements.md`. Add a dimensioned sketch
(photo of paper sketch is fine) → `mechanical/`. → **OQ-12** (internal volume),
and this is the source of the KiCad `Edge.Cuts` outline.

---

## Stage E — Display: type + pinout  → OQ-1, OQ-2

### E1. Determine VFD vs LCD
- **Visual:** A **VFD** has a glass vacuum tube look, visible fine **filament
  wires** strung horizontally across the digits, a getter spot (mirror/black
  patch) in a corner, and glows green when driven. An **LCD** is flat, has no
  filament, no getter, and is dark/grey unpowered.
- **Electrical (filament test):** On a VFD, the two **filament/heater pins** show
  a **low resistance** (typically a few ohms to a few tens of ohms) between them
  and to nothing else. Probe pin-pairs in resistance mode; a lone low-ohm pair at
  the outer pins ⇒ filament ⇒ **VFD**. No such pair + many high-impedance pins ⇒
  likely LCD.

**Record:** VFD or LCD (with the evidence) → `docs/reverse-engineering-notes.md`
§2, and resolve **OQ-1** in `docs/open-questions.md`.

### E2. Map the pinout (do this regardless of type)
1. Count the connector pins; number them against a photo.
2. Identify the **filament** pair (E1) → mark as filament.
3. With the display board still attached to its driver, use continuity from the
   **display driver IC pins** to the glass pins to group **grids/digits** vs
   **segments/icons**. (Driver outputs fan out to these.)
4. If feasible later (powered bench test, separate task), build the
   **segment/grid truth table** by driving one line at a time at low voltage.
   *Do not* apply high voltage blindly now — just map connectivity in this pass.

**Record:** pin numbering, filament pins, grid vs segment grouping →
`docs/reverse-engineering-notes.md` §2; resolves **OQ-2**. Photograph the glass
lit (if it ever powers) for the icon map (NR/SET/1/2/tape/FFWD/RWD).

---

## Stage F — Faceplate controls  → OQ-3..OQ-7

### F1. Connection type → OQ-3
Already noted in Stage B (ribbon/pins/FFC/soldered). Confirm and record.

### F2. Buttons: matrix vs individual vs resistor-ladder → OQ-4
With the faceplate board isolated (or at its connector), in **continuity** mode:
- Press each button and find which pin-pair it closes.
- **Individual:** each button shorts a **unique** pin to one **common** pin
  (N buttons ⇒ ~N+1 lines).
- **Matrix:** buttons share lines; a button closes a **row×column** intersection
  (M+N lines for M·N buttons). Map the full row/col table.
- **Resistor ladder:** all buttons feed **one** sense pin; in **resistance**
  mode, each button gives a **different** resistance to common. Record each
  button's resistance value.

**Record:** the button scheme + full map/table →
`docs/reverse-engineering-notes.md` §3; resolves **OQ-4**. This determines
whether firmware needs an I/O expander and which `pins.h` block applies.

### F3. Pots & sliders: value + taper → OQ-5, OQ-6
For **volume, balance, fader, bass, treble** (and tune if it's a pot):
1. Identify the 3 terminals (two ends + wiper) by continuity.
2. **Total resistance:** measure end-to-end (e.g. 10 kΩ, 50 kΩ, 100 kΩ).
3. **Taper:** set the control to 0 %, 25 %, 50 %, 75 %, 100 % of travel and
   record wiper-to-one-end resistance at each. Roughly linear steps ⇒ **linear
   (B)** taper; bunched-then-steep ⇒ **audio/log (A)** taper.
4. Note whether the **volume pot has an integrated power switch** (extra 2
   terminals that open/close on the click detent) — test in continuity. → feeds
   `RADIO_ON` design.

**Record:** per-control total R + taper + (volume) switch behavior →
`docs/reverse-engineering-notes.md` §3 (fill the table); resolves **OQ-5/OQ-6**.

> Tip: a 5-point taper table per control is enough. An LCR/component tester makes
> this a 30-second job each.

### F4. Tune control: encoder or pot? → OQ-7
- **Pot:** 3 terminals, **smooth continuous** resistance change as you rotate,
  no detents.
- **Rotary encoder:** has **detents** (clicks) and produces **switching** — in
  continuity mode, the A and B outputs **toggle open/closed** against a common as
  you turn (often out of phase). Usually 3 pins (A, C, B), sometimes +2 for a
  push switch. A scope on A/B shows quadrature.

**Record:** encoder or pot (+ pin identities) →
`docs/reverse-engineering-notes.md` §3; resolves **OQ-7**. Determines
`TUNE_A/TUNE_B` (encoder) vs `TUNE_ADC` (pot) in `pins.h` and removes the
TUNE/I²S pin conflict accordingly.

---

## Stage G — Cassette mechanism  → OQ-8..OQ-11

1. **Separability → OQ-8:** Can the tape transport + its preamp be removed and
   kept as a unit, independent of the dead logic board? Note fasteners and any
   shared board. Record yes/no.
2. **Preamp reuse → OQ-9:** Is there a small board on the tape-head wires with a
   preamp IC (from Stage C)? Identify its **output** pins (line-level L/R) by
   tracing from the IC. If reusable, this is your `CAS_L_IN/CAS_R_IN`.
3. **Motor voltage/current → OQ-10:** Identify the two motor leads. With the
   bench supply **current-limited to ~200 mA**, raise voltage slowly from 0 until
   the motor spins at normal speed. Record that **voltage** and the **running
   current**. (Don't exceed ~9 V if unsure.)
4. **Switches → OQ-11:** In continuity mode while inserting/removing a tape and
   running to tape-end, find a **tape-present** switch and any **end-of-tape**
   sensor (mechanical switch or photo-interrupter). Record pins + behavior.
5. Note FFWD/RWD actuation (separate motor direction, solenoid, or mechanical).

**Record:** all of the above → `docs/reverse-engineering-notes.md` §4. These set
the cassette connector and whether Level 1 (audio only) or Level 2 (transport
control) is realistic.

---

## Stage H — Rear harness connectors  → OQ-16

Use a **Metra 71-1817 reverse harness** if you have it (plugs into the OEM radio
and breaks out to labeled/colored wires) to make this easier — but verify, don't
assume colors.

**Power/illumination connector** — identify each pin by continuity to known
points and by era convention (verify on the van later):
- **GND:** continuity to chassis metal.
- **BATT_12V (constant):** goes to bulk cap / regulator input, present with key
  off in the vehicle.
- **ACC_12V (switched):** the switched supply pin.
- **ILLUM / DIMMER:** typically **orange/white** in this Chrysler era; traces to
  the display backlight/dimming, not the main supply.
- **AMP_REMOTE / blue AMP-ANT lead:** present if Infinity amp / power antenna.

**Speaker connector** — find the four BTL pairs by continuity from the amp IC
outputs: FL± FR± RL± RR±. Confirm **negatives are NOT tied to ground** (they
won't show continuity to chassis on a BTL amp).

**Record:** both connector pinouts (pin number → net, with wire color) →
`docs/reverse-engineering-notes.md` §5; resolves **OQ-16**. Drives the rear-
connector footprints. (Final vehicle-side color verification = Phase 6.)

---

## Stage I — Fit / thermal / placement assessments

- **OQ-12 internal volume:** from Stage D — usable W×H×D after the old
  electronics come out. Record the largest single board that fits.
- **OQ-13 chassis as heatsink:** Is there a metal tab/wall the original amp bolted
  to? Note contact area + whether the new amp can mechanically couple there.
- **OQ-14 mic placement:** Decide external (visor/A-pillar) vs internal; the metal
  chassis kills internal mic audio. Record the intended routing.
- **OQ-15 WWVB reception:** Note candidate spots for the ferrite antenna away from
  the buck/amp; plan a shielded lead to a better location if the dash is noisy.

**Record:** → `docs/reverse-engineering-notes.md` §6 + `mechanical/measurements.md`;
resolves **OQ-12** now, and frames **OQ-13/14/15** for the design.

---

## Completion checklist (sign-off)

Tick when the data is **in the repo**, not just observed:

- [ ] Photo archive (both sides of every board, every mated connector) →
      `mechanical/chassis-photos/`, `mechanical/faceplate-photos/`
- [ ] All IC part numbers recorded (RE §1)
- [ ] Mechanical: outline, mounting holes, shafts, sliders, display window,
      cassette envelope, connector positions + datum sketch (`measurements.md`) →
      **OQ-12**
- [ ] Display type decided with evidence → **OQ-1**
- [ ] Display pinout mapped (filament/grid/segment) → **OQ-2**
- [ ] Faceplate connection type → **OQ-3**
- [ ] Button scheme mapped (matrix/individual/ladder) → **OQ-4**
- [ ] Pot/slider values + tapers + volume switch → **OQ-5, OQ-6**
- [ ] Tune = encoder or pot, with pins → **OQ-7**
- [ ] Cassette separable? preamp reusable? motor V/I? switches? →
      **OQ-8, OQ-9, OQ-10, OQ-11**
- [ ] Power/illumination + speaker pinouts → **OQ-16**
- [ ] Antenna jack style → **OQ-17**
- [ ] Heatsink / mic / WWVB placement notes → **OQ-13, OQ-14, OQ-15**

When every box is ticked, update `docs/open-questions.md` (mark items RESOLVED
with the answer + date) and `docs/pin-map.md` (replace placeholders, resolve the
four flagged conflicts). At that point the design is unblocked and we proceed to
the full electrical design → KiCad layout → DRC → gerbers.

---

## What happens after this pass

1. You fill the repo files above from your measurements (or hand me the photos +
   numbers and I'll transcribe them).
2. I turn the resolved data into the complete electrical design (every block,
   specific parts, values, ref-des, pin-level netlist).
3. KiCad schematic → board outline from `measurements.md` → placement → routing →
   ERC/DRC → gerber + drill + BOM + pick-and-place = the package a fab needs.

OQ-18 (final audio processor) and OQ-19 (exact ESP32 module) are **design
decisions**, not teardown items — I'll resolve those during step 2.

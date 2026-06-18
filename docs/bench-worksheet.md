# Bench Data Worksheet (Round 2 — interfaces & mechanical)

Fill in every `____`. Most of this is unpowered multimeter + calipers work. Type
the results back to me (or commit this file with blanks filled) and I'll fold
them into the RE notes / pin map and start the electrical design. The detailed
"how" for each measurement lives in [teardown-protocol.md](teardown-protocol.md);
this sheet is the condensed capture form.

> Refdes already known from the photos: buttons **S201–S207**, pots **A201–A203**,
> sliders near **R209**, lamps **LP201–LP208**, faceplate ribbon **P201** (~14-pin),
> VFD soldered to the faceplate via an inline pin row.

---

## Equipment you need

### Essential (can't answer without these)
- **Digital multimeter** with **continuity beeper**, **resistance (Ω)**, and
  **DC volts**. (diode mode is a bonus.) → does Stations A–F.
- **Digital calipers** (mm) + a small steel rule. → Station G.
- **Bench DC power supply with an adjustable current limit** (e.g. 0–30 V / 0–3 A).
  → Station E motor-current only. *No supply?* See the fallback in Station E.
- **A sacrificial cassette tape** (to trip tape-present / run the transport).
- **Masking/painter's tape + fine marker** (label connector pins as you go).
- **Phone camera** (for the datum sketch + any "huh?" moments).

### Helpful (faster / more accurate, not required)
- **Component tester / LCR meter** (the ~$15–25 "LCR-T4 / TC1" type). Reads a
  pot's value in one touch and makes the taper sweep trivial. Biggest time-saver
  here.
- **Fine-tip probes or IC-hook clips** — the ribbon and connector pins are dense;
  needle probes prevent slips/shorts.
- **Helping-hands / PCB holder** — frees both hands for probing while pressing
  buttons.

### Optional (only if you already own them)
- **Oscilloscope** — the *only* thing that strictly needs one is confirming a
  rotary encoder's A/B quadrature or reading the tape-head/preamp signal level.
  Station C gives a meter-only method that avoids needing a scope.

---

## Station A — Pots & sliders (DMM in Ω)
For each control: measure **end-to-end** resistance (outer pin to outer pin),
then set the control to each position and read **wiper→one-end** resistance.
Roughly even steps = **linear (B)** taper; bunched then steep = **audio/log (A)**.

| Control | Refdes | End-to-end | 0% | 25% | 50% | 75% | 100% | Taper (A/B) |
|---|---|---|---|---|---|---|---|---|
| Volume | A2__ | ____ kΩ | ____ | ____ | ____ | ____ | ____ | ____ |
| Balance | A2__ | ____ kΩ | ____ | ____ | ____ | ____ | ____ | ____ |
| Fader | A2__ | ____ kΩ | ____ | ____ | ____ | ____ | ____ | ____ |
| Bass (slider) | R209? | ____ kΩ | ____ | ____ | ____ | ____ | ____ | ____ |
| Treble (slider) | ____ | ____ kΩ | ____ | ____ | ____ | ____ | ____ | ____ |

**Volume power switch:** does the volume knob have a separate 2-terminal **click
on/off switch** (continuity that opens/closes at the detent)?  Yes / No: ____
If yes, note its terminals: ____

---

## Station B — Buttons: matrix map (DMM continuity)
Press each button; find which **two pins** (on P201 ribbon or the button pads)
it connects. If buttons share lines → it's a **matrix**: record the row×col for
each. If each button uses a unique pin + one common → **individual**.

Scheme (circle one): **matrix** / **individual** / **resistor-ladder**: ____

| Button | Function | Pin A | Pin B (or row/col) |
|---|---|---|---|
| S201 | ____ | ____ | ____ |
| S202 | ____ | ____ | ____ |
| S203 | ____ | ____ | ____ |
| S204 | ____ | ____ | ____ |
| S205 | ____ | ____ | ____ |
| S206 | ____ | ____ | ____ |
| S207 | ____ | ____ | ____ |

(Map the printed faceplate buttons — SEEK ▲/▼, AM/FM, SET, presets 1–5, H, M,
EJT, FFWD, RWD — to whichever S-numbers they turn out to be.)
Number of ribbon conductors on P201: ____

---

## Station C — Tune control: pot or encoder? (DMM)
- **Pot:** 3 terminals, resistance changes **smoothly/continuously** as you
  rotate, no clicks. → it's a pot. Total R: ____ kΩ.
- **Encoder:** has **detents (clicks)**; in continuity mode two output pins
  **toggle open/closed** against a common as you rotate (no steady resistance).
  → it's an encoder. # of pins: ____ (and push-switch? Yes/No: ____)

Verdict: **pot** / **encoder**: ____

---

## Station D — VFD (DMM in Ω, unpowered)
- Total number of pins on the VFD inline row: ____
- **Filament pair:** find the two pins with a **low resistance** between them
  (a few Ω to a few tens of Ω) and no/high resistance to the rest. Pin #s: ____
  Measured filament resistance: ____ Ω
- (Full segment/grid truth table is a later powered step — not needed now.)

---

## Station E — Cassette transport
**Motor running current (needs current-limited supply):**
1. Identify the two motor leads (from the capstan motor, `MMI-6N3LKP`).
2. Set the supply to **current-limit ~0.5 A**, raise voltage from 0 until the
   motor spins at normal speed (should be near 13.2 V).
3. Record: voltage at normal speed ____ V, steady running current ____ mA.
*No bench supply?* Put the DMM (10 A range) **in series** with a 12 V source and
a tape playing, read the current: ____ mA (note source voltage ____ V).

**Switches (DMM continuity):**
- Tape-present switch — does inserting a cassette close/open a contact? Pins +
  behavior: ____
- End-of-tape — any switch/photo-interrupter that changes at tape end? ____
- FFWD/RWD — separate motor/direction, solenoid, or purely mechanical? ____

---

## Station F — Rear connectors: radio-side pin numbering (DMM continuity)
Number the connector pins against a photo (left→right, top row first). Map each
**physical pin** to its function. Cross-reference §5a (vehicle colors) / §5c
(Metra colors) but the goal here is the **radio's own pin order**.

**Power / illumination connector** (___ pins):
| Pin # | Function (BATT / ACC / GND / ILLUM / DIMMER / AMP-ON / ANT / spare) |
|---|---|
| 1 | ____ |
| 2 | ____ |
| 3 | ____ |
| 4 | ____ |
| 5 | ____ |
| 6 | ____ |
| 7 | ____ |

Tips: **GND** = continuity to chassis metal. **Speaker −** pins do *not* show
continuity to chassis (BTL). Trace **speaker** pins from the amp's output area.

**Speaker connector** (___ pins):
| Pin # | Speaker (FL+/FL−/FR+/FR−/RL+/RL−/RR+/RR−) |
|---|---|
| 1 | ____ |
| 2 | ____ |
| 3 | ____ |
| 4 | ____ |
| 5 | ____ |
| 6 | ____ |
| 7 | ____ |
| 8 | ____ |

**Antenna jack** style (Motorola / other): ____

---

## Station G — Mechanical (calipers, mm) → also copy into measurements.md
Pick **one datum corner** of the main PCB (say front-left). All X,Y from there
(X = toward right, Y = toward back).

- Main PCB: width ____ × depth ____ , thickness ____
- Mounting holes (X, Y, Ø), one per line:
  - ____ , ____ , Ø ____
  - ____ , ____ , Ø ____
  - ____ , ____ , Ø ____
  - ____ , ____ , Ø ____
- Knob shaft centers (X, Y, shaft Ø, panel→board depth):
  - Volume: ____
  - Tune: ____
  - Balance: ____
  - Fader: ____
- Slider travel (start X,Y → end X,Y): Bass ____  Treble ____
- Display window inner: width ____ × height ____ ; board→glass standoff ____
- Cassette envelope: W ____ × H ____ × D ____ ; clearance to main board ____
- Rear connector positions/orientation: ____
- Antenna jack position: ____
- Max component height per side / keep-outs: ____
- 📷 Attach a dimensioned datum sketch photo.

---

## When this is filled
Stations A–F close OQ-2/4/6/7/10/11 and the §5b pin numbering; Station G gives
the board outline + mounting + shaft alignment. With those in hand the design is
fully unblocked → complete electrical design → KiCad schematic → layout → DRC →
gerbers/BOM/CPL.

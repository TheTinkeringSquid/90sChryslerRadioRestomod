# Open Questions

Tracked unknowns. Keep open until teardown/bench data resolves them. Each is
referenced from the relevant design doc and/or firmware. Status: `OPEN` /
`RESOLVED` (with date + answer).

| ID | Question | Gates | Status |
|---|---|---|---|
| OQ-1 | Is the factory display definitely a VFD? | display driver, HV supply | **RESOLVED** — VFD confirmed [PHOTO] |
| OQ-2 | What is the display pinout (filament/grid/segment/icon)? | VFD driver, truth table | OPEN (VFD soldered via inline pin row; map pins) |
| OQ-3 | Faceplate connection: ribbon / pins / soldered? | front-panel connector | **RESOLVED** — ~14-pin ribbon cable [PHOTO] |
| OQ-4 | Buttons: matrixed / individual / resistor-ladder? | GPIO count, I/O expander | PARTIAL — discrete tactiles S201–S207+, likely matrix-scanned; map [PHOTO] |
| OQ-5 | Are bass/treble/balance/fader true analog pots/sliders? | ADC vs other | **RESOLVED** — rotary pots + slider pots [PHOTO] |
| OQ-6 | Their resistance values and tapers? | ADC scaling, dividers | OPEN (measure) |
| OQ-7 | Is the tune knob an encoder or analog control? | quadrature GPIO vs ADC | OPEN (no obvious encoder in photos; verify) |
| OQ-8 | Can the cassette mechanism be separated from the original logic board? | cassette feasibility | **RESOLVED** — yes, self-contained transport [PHOTO] |
| OQ-9 | Is there a reusable cassette preamp board? | tape audio path | **RESOLVED** — board 04832548, Toshiba TA770xP + Hitachi NR; trace output [VIDEO] |
| OQ-10 | Cassette motor voltage/current? | motor driver sizing | PARTIAL — **13.2 V** [PHOTO]; current TBD |
| OQ-11 | Tape-present and end-of-tape switches present? | transport logic | OPEN (leaf switches visible; map) |
| OQ-12 | Internal volume after removing original electronics? | board outline, partitioning | OPEN (measure) |
| OQ-13 | Can the chassis be used as amplifier heatsink? | thermal, amp class | **RESOLVED** — yes, amp bolts to vented chassis bracket [PHOTO] |
| OQ-14 | Where should the microphone mount for usable HFP audio? | mic connector/routing | OPEN |
| OQ-15 | Will WWVB receive reliably inside the dash/chassis? | external antenna decision | OPEN |
| OQ-16 | Power/illumination + speaker connector pinouts? | rear harness footprints | PARTIAL — vehicle-side wire functions/colors found (RE §5a); radio-side pin numbering still needs teardown (§5b) |
| OQ-17 | Antenna jack type (Motorola/other)? | antenna footprint | PARTIAL — likely Motorola-style, antenna at right-front; confirm at teardown |
| OQ-18 | Final audio processor: discrete switches+codec DSP vs dedicated AP IC? | BOM, schematic | OPEN |
| OQ-19 | Exact ESP32 module confirmed to support Classic A2DP+HFP for this stack? | controller selection | OPEN |
| OQ-20 | Final factory-style behavior when tape inserted while in AM/FM/BT? | UI state machine | OPEN |

## Resolution log
*(append `OQ-N — RESOLVED YYYY-MM-DD: answer` as items close)*

- OQ-16 — PARTIAL 2026-06-14: vehicle-side radio harness wire functions/colors
  captured (1995–97 Ram, same-era connector) in RE §5a from the12volt + forums.
  Radio-side pin numbering still pending teardown. Verify colors on the van.
- OQ-17 — PARTIAL 2026-06-14: antenna at right-front, likely Motorola-style jack
  (era-standard). Confirm physically at teardown.
- Note 2026-06-14: searched for a factory internal schematic / service manual for
  P04858531 — **none publicly available** (proprietary Mitsubishi-built Chrysler
  unit; United Radio service domain). Internal nets must be reverse-engineered.
- 2026-06-16: first teardown photos received (10 imgs in `../mechanical/`).
  - OQ-1 — RESOLVED: display is a **VFD** (green glass, AM/FM + 3-digit field +
    NR/SET/1/2 icons).
  - OQ-3 — RESOLVED: faceplate ↔ main connection is a **~14-pin ribbon cable**.
  - OQ-5 — RESOLVED: tone/balance/fader/volume are **rotary + slider pots**.
  - OQ-8 — RESOLVED: cassette transport is a **separable self-contained unit**.
  - OQ-13 — RESOLVED: **chassis serves as the amp heatsink** (vented bracket).
  - OQ-10 — PARTIAL: cassette motor is **DC 13.2 V** (current still TBD).
  - OQ-9 — PARTIAL: a **dedicated 2-IC cassette preamp board** exists (reusable).
  - OQ-4 — PARTIAL: discrete tactile buttons S201–S207+, likely matrix; map TBD.
  - Still blocked on **legible IC part numbers** (µC, amp, tuner, preamp, display
    driver) — current photos too blurry; need sharp macro shots.
- 2026-06-17: two main-board videos (front+back) + cassette-deck + Metra harness
  label processed (frames archived under `../mechanical/chassis-photos/`).
  - **IC RE effectively complete.** Main-board signal ICs are **custom
    Chrysler/ACUSTAR masks** (Motorola `04745268`/`04745269`/`SC417964CP-04745177`,
    an ST DIP) — **not sourceable**, confirming replace-all. Amp IC is clamped
    face-to-chassis (unreadable, irrelevant to redesign).
  - OQ-9 — RESOLVED: cassette preamp board `04832548` uses **standard** parts
    (Toshiba TA770xP playback + Hitachi HA12134-type Dolby-B NR) → reusable.
  - Motor refined to `MMI-6N3LKP DC 13.2 V`.
  - Added Metra/EIA aftermarket color code (RE §5c) from the harness-bag label
    (distinct from the vehicle-side colors and the radio pin numbering).
  - Remaining gates are now **interfaces + mechanical**, not ICs: radio-side
    connector pin numbering (§5b), button-matrix map (OQ-4), pot values/tapers
    (OQ-6), tune pot-vs-encoder (OQ-7), VFD pinout (OQ-2), motor current/tape
    switches (OQ-10/11), and the board outline + measurements.

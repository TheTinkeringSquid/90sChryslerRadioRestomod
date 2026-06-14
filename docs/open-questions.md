# Open Questions

Tracked unknowns. Keep open until teardown/bench data resolves them. Each is
referenced from the relevant design doc and/or firmware. Status: `OPEN` /
`RESOLVED` (with date + answer).

| ID | Question | Gates | Status |
|---|---|---|---|
| OQ-1 | Is the factory display definitely a VFD? | display driver, HV supply | OPEN |
| OQ-2 | What is the display pinout (filament/grid/segment/icon)? | VFD driver, truth table | OPEN |
| OQ-3 | Faceplate connection: ribbon / pins / soldered? | front-panel connector | OPEN |
| OQ-4 | Buttons: matrixed / individual / resistor-ladder? | GPIO count, I/O expander | OPEN |
| OQ-5 | Are bass/treble/balance/fader true analog pots/sliders? | ADC vs other | OPEN |
| OQ-6 | Their resistance values and tapers? | ADC scaling, dividers | OPEN |
| OQ-7 | Is the tune knob an encoder or analog control? | quadrature GPIO vs ADC | OPEN |
| OQ-8 | Can the cassette mechanism be separated from the original logic board? | cassette feasibility | OPEN |
| OQ-9 | Is there a reusable cassette preamp board? | tape audio path | OPEN |
| OQ-10 | Cassette motor voltage/current? | motor driver sizing | OPEN |
| OQ-11 | Tape-present and end-of-tape switches present? | transport logic | OPEN |
| OQ-12 | Internal volume after removing original electronics? | board outline, partitioning | OPEN |
| OQ-13 | Can the chassis be used as amplifier heatsink? | thermal, amp class | OPEN |
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

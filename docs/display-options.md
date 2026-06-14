# Display Options

The factory display is green and segmented. Goal: retain that exact appearance
behind the original window. Two paths; the PCB must support **both** until Phase 0
decides, via a modular display daughterboard connector.

## Path A — Reuse original VFD glass (preferred)

Likely a **VFD** (green segmented, era-appropriate) rather than a simple LCD.

**Requires reverse-engineering:**
- Filament pins (heater) — likely ~2–4 V AC/DC.
- Grid/digit pins.
- Segment/icon pins.
- Full segment/grid truth table.

**Drive hardware:**
- HV boost converter for the anode/grid rail (~25–40 V, adjustable).
- Filament supply.
- VFD driver IC — candidates: **MAX6921** (HV shift-register), **PT631x** /
  **HT16512**-style controller/driver. Exact part chosen *after* pin mapping.

## Path B — Green LED replacement (fallback)

Build a green display behind the original window.

- Green LED 7-segment digit modules.
- Discrete green LEDs for icons: NR, SET, 1, 2, Tape, FFWD, RWD.
- LED driver: **HT16K33**, **MAX7219**, **TLC5940**, or shift registers + current
  limiting.

## PCB strategy (applies to both)

- Expose **SPI / I²C / GPIO** to a display connector (30–40 pin generic).
- Keep the display driver **modular** (daughterboard or flex connector) so the
  rest of the project can proceed before the original VFD is decoded, and so the
  unknown mechanical fit / glass pinout doesn't block the main board.

## Icons to reproduce

| Icon | Meaning | Driven by |
|---|---|---|
| `NR` | Noise reduction / tape indicator (orig. behavior unknown) | dedicated seg/LED |
| `SET` | Settings/preset/clock-adjust active | dedicated seg/LED |
| `1` / `2` | Active preset bank | dedicated seg/LED |
| Tape | Cassette present/active | dedicated seg/LED |
| FFWD / RWD | Transport active | dedicated seg/LED |

## Decision gate
The VFD-vs-LED decision is **OQ-1 / OQ-2** in
[open-questions.md](open-questions.md) and Phase 3 in the README roadmap.
Capture display measurements + pin probing in
[reverse-engineering-notes.md](reverse-engineering-notes.md).

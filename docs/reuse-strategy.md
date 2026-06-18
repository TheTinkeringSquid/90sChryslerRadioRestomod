# Board Reuse Strategy (decision record)

**Decided 2026-06-17.** Defines which original boards we keep vs replace, the
rationale, the conditions reuse imposes on the new main board, and the resulting
board boundaries / connectors. This sets the board-level architecture for the
schematic phase.

## Principle
> **Reuse what carries OEM mechanical/aesthetic value or is standard-and-working;
> replace only what is dead and unsourceable.**

## Per-board decision

| Original board | Decision | Rationale |
|---|---|---|
| **Main logic/RF board** | **Replace (new custom PCB)** | Dead; signal ICs are custom Chrysler/ACUSTAR masks (Motorola `04745268`/`04745269`/`SC417964CP-04745177`, ST DIP) — no datasheets, not sourceable, can't be interfaced or repaired. Also architecturally incapable of the new features (BT/WWVB/modern tuner+codec). No reuse path. |
| **Faceplate / display board** (`04745184`) | **Reuse** | OEM mechanical fixture + essentially passive. See below. |
| **Pot sub-board** (small white board, 2 rotary pots) | **Reuse** | Part of the faceplate control assembly; passive. |
| **Cassette preamp board** (`04832548`) | **Reuse** | Standard catalog parts, already working & mated to the tape head. See below. |

## Why reuse the faceplate / display board
1. **It is the OEM mechanical fixture.** It physically locates the VFD, all
   buttons, pots, sliders, lamps, and knob shafts in exact alignment with the
   bezel and display window. Reuse inherits that alignment for free; redesigning
   it means re-deriving every shaft/button/slider/VFD position in CAD — large
   effort, real misalignment risk, **zero functional gain**.
2. **It is essentially passive.** Teardown video confirmed **no driver IC** on
   it — only the VFD, switches, pots, lamps, and two small transistors (Q201/Q202)
   + small U201/U202, all routed over the ~14-pin **P201** ribbon. The new main
   board drives/reads it over that ribbon (we supply the VFD driver, scan the
   button matrix, read pots via ADC).
3. **Guarantees the VFD fits its window** — lowest-risk way to keep the factory
   green display.

## Why reuse the cassette preamp board (`04832548`)
- Built from **standard, sourceable ICs**: Toshiba **TA770xP** playback preamp +
  Hitachi **Dolby-B NR** (the latter is exactly what lights the factory `NR`
  icon). Already wired to the tape head; outputs line-level.
- Redesigning it = reinventing a solved analog circuit and discarding free NR.
- New board brings in its **line-level L/R output + power**, selects it in the
  source mux.

## Why replace the main board
Dead + custom-masked unsourceable ICs + needs entirely new functionality. This
is the core premise of the project. (See [reverse-engineering-notes.md](reverse-engineering-notes.md) §1.)

## Conditions reuse imposes on the NEW main board
Reuse is the low-effort path but it constrains the new design:

1. **Mate the faceplate `P201` ribbon** — new board needs the matching ribbon
   header. Pinout (button matrix, pot pins, VFD filament/grid/segment, lamp
   lines) must be mapped first → [bench-worksheet.md](bench-worksheet.md)
   Stations A–D, OQ-2/4/6/7.
2. **Drive the VFD from the new board** — supply VFD driver + HV boost (~25–40 V)
   + filament (~2–4 V). Understand the faceplate's Q201/Q202 + U201/U202 role
   (likely lamp/filament drive or scan buffers) and either feed or bypass them.
3. **Cassette preamp connector** — header for its line-level L/R + power + ground.
4. **Connector placement** — ribbon header and preamp/transport connectors must
   be positioned on the new board to physically reach the reused boards (depends
   on the mechanical measurements, [measurements.md](../mechanical/measurements.md)).

## Fallbacks
- **VFD undrivable in practice** → green-LED-behind-window replacement (OQ-1/2).
- **Awkward ribbon pinout** → small **faceplate adapter daughterboard** between
  the original ribbon and the new main board (still avoids redesigning the
  faceplate itself).
- **Transport physically unusable** → source a same-family replacement deck;
  cassette remains a required source ([cassette-integration.md](cassette-integration.md)).

## Resulting board set
- **NEW main board** (custom) — power, ESP32, Si4735 tuner, codec, source mux/AP,
  4-ch amp, VFD driver + supplies, cassette motor/transport drivers, WWVB, mic,
  all connectors.
- **REUSED:** faceplate/display board (+ pot sub-board) via P201 ribbon; cassette
  preamp board via a line-level/power header.
- **POSSIBLE small adapter** (only if ribbon pinout demands it).

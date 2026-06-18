# Cassette Integration

**Cassette is a REQUIRED audio source** — one of the four final sources (AM, FM,
**Cassette**, BT). The tape deck must play, and the EJT / FFWD / RWD buttons must
function. This is no longer an "if practical" stretch goal: the PCB must be
designed for **full transport control** (Level 2 below) from the start. Firmware
may still be brought up in stages, but the hardware ships Level-2-capable.

> Enabling data: the transport is a **separable** self-contained unit (OQ-8 ✅)
> with a **reusable preamp board `04832548`** (Toshiba TA770xP playback + Hitachi
> Dolby-B NR — OQ-9 ✅) and a **13.2 V capstan motor** (`MMI-6N3LKP`, OQ-10).
> What still needs Phase-0 capture is the transport *control* wiring (below).

## Unknowns to reverse-engineer (Phase 0)
- Tape head signal levels / where they come out.
- Existing tape preamp availability and whether it is separable from the dead
  logic board.
- Motor control voltage/current.
- Tape-in switch.
- FFWD/RWD motor/solenoid control.
- End-of-tape detection.
- Eject mechanism behavior.

## Build stages (firmware phasing — hardware supports Level 2 throughout)

### Stage 1 — Tape audio + detect (firmware milestone, not the ship target)
- Reuse the tape mechanism and the separable preamp board `04832548`.
- Bring stereo cassette **line-level** audio (preamp output) into the PCB.
- ESP32 / audio mux selects cassette as a source.
- Detect tape-in to engage cassette mode / light the tape icon.

### Stage 2 — Full transport control (REQUIRED end state)
- ESP32 drives the **13.2 V motor** (via a motor driver), **FFWD / RWD**, reads
  **tape-present** and **end-of-tape**, and handles **eject**.
- Light tape / FFWD / RWD icons from real transport state.
- Map EJT / FFWD / RWD faceplate buttons to transport actions.

> The PCB **must** carry the motor driver, transport outputs, and switch inputs
> regardless of firmware staging — adding them later would mean a board respin.

## Generic cassette connector (design for both levels)

| Pin | Net | Dir | Notes |
|---|---|---|---|
| 1 | `CAS_L_IN` | in | line-level left |
| 2 | `CAS_R_IN` | in | line-level right |
| 3 | `CAS_GND` | — | audio ground/shield |
| 4 | `TAPE_PRESENT` | in | tape-in switch |
| 5 | `MOTOR_EN` | out | required (via motor driver, 13.2 V) |
| 6 | `MOTOR_PWM` | out | required (speed/torque, if applicable) |
| 7 | `FFWD_EN` | out | required |
| 8 | `RWD_EN` | out | required |
| 9 | `EJECT_SENSE` / `EJECT_OUT` | in/out | per mechanism (map in Phase 0) |
| 10 | `END_OF_TAPE` | in | required (per mechanism) |
| — | spare GPIO ×N | — | headroom |
| — | motor power | — | if motor driven from board |

## Firmware
Behavior lives in [../firmware/src/cassette.h](../firmware/src/cassette.h) /
`cassette.cpp` as an abstraction so Stage 1 audio can be brought up first and
Stage 2 transport added without touching the UI state machine. **Factory-style
default UX:** inserting a cassette engages `CASSETTE_MODE`; eject returns to the
previous source; the AM/FM button cycles `AM → FM → BT` among the non-tape
sources (final edge-case behavior in [ui-state-machine.md](ui-state-machine.md),
OQ-20).

## Recommendation
Design the PCB for **full transport control** (populate all Stage-2 nets). The
mechanism is confirmed separable with a reusable preamp, so cassette as a
first-class source is well-supported. The only true contingency: if the physical
transport proves unusable, source a same-family replacement deck — cassette
remains a required source either way.

# Cassette Integration

Retain tape playback and the EJT / FFWD / RWD buttons **if practical**. Phase it.

## Unknowns to reverse-engineer (Phase 0)
- Tape head signal levels / where they come out.
- Existing tape preamp availability and whether it is separable from the dead
  logic board.
- Motor control voltage/current.
- Tape-in switch.
- FFWD/RWD motor/solenoid control.
- End-of-tape detection.
- Eject mechanism behavior.

## Integration levels

### Level 1 — Tape audio only (minimum)
- Reuse the tape mechanism and any separable existing preamp.
- Bring stereo cassette **line-level** audio into the custom PCB.
- ESP32 / audio mux selects cassette as a source.
- Detect tape-in to switch mode / light the tape icon.

### Level 2 — Full transport control (advanced)
- ESP32 controls motor, FFWD, RWD, tape-present state, maybe auto-reverse.
- Add motor driver / transistor outputs and switch/sensor inputs.
- Light tape / FFWD / RWD icons from real transport state.

## Generic cassette connector (design for both levels)

| Pin | Net | Dir | Notes |
|---|---|---|---|
| 1 | `CAS_L_IN` | in | line-level left |
| 2 | `CAS_R_IN` | in | line-level right |
| 3 | `CAS_GND` | — | audio ground/shield |
| 4 | `TAPE_PRESENT` | in | tape-in switch |
| 5 | `MOTOR_EN` | out | Level 2 |
| 6 | `MOTOR_PWM` | out | Level 2 (speed, if applicable) |
| 7 | `FFWD_EN` | out | Level 2 |
| 8 | `RWD_EN` | out | Level 2 |
| 9 | `EJECT_SENSE` / `EJECT_OUT` | in/out | if applicable |
| 10 | `END_OF_TAPE` | in | if present |
| — | spare GPIO ×N | — | headroom |
| — | motor power | — | if motor driven from board |

## Firmware
Behavior lives in [../firmware/src/cassette.h](../firmware/src/cassette.h) /
`cassette.cpp` as an abstraction so Level 1 ships first and Level 2 is added
without touching the UI state machine. Tape insertion may override the current
mode to `CASSETTE_MODE` (final factory-style behavior TBD —
[ui-state-machine.md](ui-state-machine.md)).

## Recommendation
Design the PCB with the generic connector above and implement in phases. If the
cassette mechanism cannot be cleanly separated from the dead logic board,
fall back to "tape icon + dummy" and prioritize AM/FM/BT.

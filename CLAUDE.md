# Dodge B2500 Radio Restomod — Agent Instructions (Claude + Codex)
<!-- CLAUDE.md and AGENTS.md are identical; edit both together. Router, not a diary: keep under ~100 lines. -->

## What this is
ESP32 electronics replacing the dead internals of a **1996 Dodge B2500** factory AM/FM cassette head unit (P/N P04858531). The factory faceplate, knobs, buttons, sliders, green display, and cassette controls are kept.
Design philosophy: it should feel like Chrysler built it in 1996 with Bluetooth and WWVB. Modernize only the invisible internals.
**Current phase: 0 (teardown and documentation).** The radio was bench-tested and confirmed dead.

## Hard constraints (never violate)
- No touchscreen. Keep the factory physical controls and look, and the factory green display appearance.
- Keep AM/FM. **Cassette is required and fully functional** (playback plus motor, FFWD/RWD, eject).
- Bluetooth is a third mode on the existing AM/FM button (`AM → FM → BT`), not a new control.
- As much hardware as possible on one custom PCB.
- Automotive environment: 9–16 V nominal, cranking dips, load dump.
- **ESP32 classic (Bluetooth Classic A2DP/HFP). Do not switch to ESP32-S3** (BLE-only).
- **Never fabricate pinouts or signal behavior.** Anything not measured stays `TODO`/`UNKNOWN` (docs and `firmware/src/pins.h`) until Phase 0 data exists.

## Where things live
| Need | Go to |
|---|---|
| One-page overview | `docs/project-summary.md` |
| Reading order for all docs | `README.md` → "Recommended reading order" |
| Every control and its intended behavior | `docs/factory-functions.md`, `docs/ui-state-machine.md` |
| Hardware spec by block | `docs/hardware-requirements.md`, `audio-architecture.md`, `power-protection.md`, `display-options.md`, `cassette-integration.md` |
| Reuse vs. replace decisions | `docs/reuse-strategy.md` |
| **Teardown (current work)** | `docs/teardown-protocol.md` → record in `docs/reverse-engineering-notes.md` and `mechanical/measurements.md` |
| What's still needed | `docs/next-capture-punchlist.md`, `docs/bench-worksheet.md`, `docs/open-questions.md` |
| Pins (placeholder) | `docs/pin-map.md`, `firmware/src/pins.h` |
| BOM and bring-up | `docs/bom-planning.md`, `hardware/bom/`, `docs/bringup-test-plan.md` |
| KiCad, symbols, footprints, datasheets | `hardware/` |
| Photos | `mechanical/*-photos/` |

## Commands
- Firmware (PlatformIO, env `esp32dev`): `cd firmware && pio run`; tests in `firmware/test/` (`pio test`).
- Library deps in `platformio.ini` stay commented until their module is implemented; pin versions when you enable them.

## Rules
- Phase gating: don't design the schematic or PCB ahead of the Phase 0 data it depends on (see the phases table in `README.md`).
- New unknowns go in `docs/open-questions.md`. Resolved ones record the measurement and its source.
- Commit or push only when Nathan says so.

## Applied learning
<!-- One-line bullets added when something fails repeatedly. Prune often. -->
-

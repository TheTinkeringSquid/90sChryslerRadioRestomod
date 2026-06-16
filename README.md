# Dodge B2500 Factory Radio — ESP32 Restomod

Custom ESP32-based electronics that replace the dead internals of a **1996 Dodge
B2500** factory AM/FM cassette head unit (Chrysler/Dodge/Jeep RAS-style,
P/N **P04858531**) while preserving the factory faceplate, knobs, buttons,
sliders, green segmented display, cassette controls, and OEM look/feel.

> **Design philosophy:** This should feel like Chrysler could have built it in
> 1996 if Bluetooth and WWVB sync had existed in a factory cassette deck.
> Modernize only the invisible internals. No touchscreen.

---

## What it does

| Feature | Status / approach |
|---|---|
| AM/FM reception | Modern Si4735-class tuner (I²C), analog L/R out |
| Bluetooth audio (A2DP) | ESP32 Bluetooth Classic → I²S codec |
| Hands-free calling (HFP) | Codec ADC + external mic; HW now, FW phased |
| Radio-controlled clock | WWVB 60 kHz receiver + optional DS3231 RTC fallback |
| Factory green display | Reuse original VFD glass **or** green-LED replacement behind window |
| Cassette | Audio passthrough min.; full transport control as a later phase |
| 4-channel audio out | Automotive BTL amp (TDA7388/TDA7850-class) to factory speaker harness |

The existing **AM/FM button** becomes the source selector: `AM → FM → BT → AM`.

## Hard constraints (do not violate)

- No touchscreen.
- Retain factory physical controls and look.
- Retain AM/FM; retain cassette if practical.
- Bluetooth is a *third mode on the existing AM/FM button*, not a new control.
- Use the factory green display appearance.
- Keep as much hardware as possible on one custom PCB.
- Must be compatible with 1996 B2500 wiring and survive the automotive
  electrical environment (9–16 V nominal, cranking dips, load dump).

## Repository layout

```
docs/         Design + planning documentation (start here)
hardware/     KiCad schematic/PCB, symbols, footprints, datasheets, BOM
firmware/     PlatformIO ESP32 firmware (skeleton)
mechanical/   Teardown measurements and photo archive
```

Recommended reading order in `docs/`:

1. [project-summary.md](docs/project-summary.md) — one-page overview
2. [factory-functions.md](docs/factory-functions.md) — every control + intended behavior
3. [hardware-requirements.md](docs/hardware-requirements.md) — block-by-block HW spec
4. [audio-architecture.md](docs/audio-architecture.md)
5. [power-protection.md](docs/power-protection.md)
6. [display-options.md](docs/display-options.md)
7. [cassette-integration.md](docs/cassette-integration.md)
8. [ui-state-machine.md](docs/ui-state-machine.md)
9. [teardown-protocol.md](docs/teardown-protocol.md) — Phase 0 field guide
10. [next-capture-punchlist.md](docs/next-capture-punchlist.md) — **round-2 to-do (what's still needed)**
11. [reverse-engineering-notes.md](docs/reverse-engineering-notes.md) — **teardown capture (in progress)**
12. [open-questions.md](docs/open-questions.md) — tracked unknowns
13. [bom-planning.md](docs/bom-planning.md)
14. [pin-map.md](docs/pin-map.md) — **PLACEHOLDER** ESP32 pin assignments
15. [bringup-test-plan.md](docs/bringup-test-plan.md)

## Development phases

| Phase | Goal | Blocked on |
|---|---|---|
| 0 | Teardown + documentation | Physical radio |
| 1 | Bench proof-of-concept (dev boards) | Parts on hand |
| 2 | Faceplate integration prototype | Phase 0 pinouts |
| 3 | Display prototype (VFD reuse or LED) | Phase 0 display mapping |
| 4 | Cassette integration | Phase 0 cassette signals |
| 5 | Main custom PCB | Phases 1–4 proven |
| 6 | Bring-up + vehicle test | Phase 5 board |

> **Current real-world status:** factory radio bench-tested and confirmed dead.
> Next physical action is **Phase 0 teardown** — follow the step-by-step
> [docs/teardown-protocol.md](docs/teardown-protocol.md), recording results into
> [docs/reverse-engineering-notes.md](docs/reverse-engineering-notes.md) and
> [mechanical/measurements.md](mechanical/measurements.md). That one pass
> resolves the open questions that gate the schematic and PCB layout.

## ⚠️ Unknowns

No factory faceplate, display, or cassette pinouts are assumed. Everything that
depends on teardown data is marked **`TODO`/`UNKNOWN`** in the docs and in
[firmware/src/pins.h](firmware/src/pins.h). Do not fabricate pinouts — fill them
in only from measured Phase 0 data.

---

*Project vehicle: Nathaniel Moore's white 1996 Dodge B2500 Ram Van, Elkhart
high-top conversion, 3.9L Magnum V6, blue interior.*

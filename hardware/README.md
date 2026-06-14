# Hardware

KiCad project + supporting files for the replacement main board. **Nothing here
yet** — schematic capture (Phase 5) is gated on Phases 0–4. Folders are
placeholders so the structure is ready.

```
schematic/    KiCad schematic (.kicad_sch) — top sheet + per-block sub-sheets
pcb/          KiCad board (.kicad_pcb), Edge.Cuts from mechanical/measurements.md
symbols/      Project-specific schematic symbols (.kicad_sym)
footprints/   Project-specific footprints (.pretty) incl. OEM connectors
datasheets/   Vendor PDFs for chosen parts (ESP32, Si4735, codec, amp, drivers)
bom/          Per-revision BOM (CSV) once the schematic exists
```

## Before starting the schematic
1. Complete [../docs/reverse-engineering-notes.md](../docs/reverse-engineering-notes.md)
   and [../mechanical/measurements.md](../mechanical/measurements.md).
2. Resolve the four placeholder conflicts in
   [../docs/pin-map.md](../docs/pin-map.md).
3. Lock parts from [../docs/bom-planning.md](../docs/bom-planning.md)
   (verify availability + KiCad libs).

## Block sheets to create (suggested hierarchy)
- Power: protection front-end, 12V_AMP, 5V buck, 3V3.
- Controller: ESP32 module + program/debug + strapping.
- Tuner: Si4735 + antenna front-end.
- Codec/audio: codec + audio processor + source mux + mic front-end.
- Amplifier: 4-ch BTL + mute/standby + thermal.
- Display: VFD driver + HV/filament **or** LED driver (modular connector).
- Clock: WWVB header + DS3231.
- Connectors: rear harness, front panel, cassette, mic.

## Conventions
- 4-layer stackup (top / GND / power+GND / bottom) — see
  [../docs/hardware-requirements.md](../docs/hardware-requirements.md) §12.
- Net names match [../docs/pin-map.md](../docs/pin-map.md).
- Run ERC + DRC clean before exporting gerbers; export gerbers + assembly to a
  `pcb/fab/` subfolder per revision.

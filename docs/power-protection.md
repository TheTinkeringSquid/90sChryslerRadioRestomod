# Power & Automotive Robustness

The board must survive a real vehicle electrical environment.

## Input power

- Nominal 12 V; normal operation ~9–16 V.
- Cranking dips and load-dump/transients must be tolerated.

**Required at input:**
- Fuse footprint.
- Reverse-polarity protection (P-FET ideal, or diode).
- Automotive TVS diode (load-dump rated).
- LC / PI filtering + bulk capacitance.
- Separate filtered rails for analog/RF sections.

## Rails

| Rail | Source | Feeds |
|---|---|---|
| `12V_IN` | vehicle | protection front-end |
| `12V_AMP` | filtered 12 V | speaker amplifier |
| `5V_SYS` | buck from 12 V | codec, display (opt), tuner (opt) |
| `3V3_LOGIC` | LDO or buck/LDO | ESP32, tuner logic, button scan, WWVB (if 3.3 V) |

## Power sequencing

- ESP32 controls amp mute/standby.
- **Delay amplifier enable after source/codec init** to prevent turn-on pops.
- **Mute amp before shutdown.**
- See sequencing detail in [audio-architecture.md](audio-architecture.md).

## Grounding

- Solid ground plane.
- Separate analog and digital zones.
- Star / single-point tie between noisy power ground and quiet analog ground.
- Keep buck return currents away from audio-input and tuner sections.
- Keep speaker currents away from ESP32 / tuner / codec.

## EMI / noise

**Sources:** ESP32 RF, buck regulators, speaker amp, vehicle alternator/ignition.
**Sensitive victims:** WWVB 60 kHz, AM band, FM/BT RF, audio inputs, mic.

**Mitigations:**
- Shield/partition RF and analog sections.
- Ferrite beads where appropriate.
- Input/output ESD protection.
- Short, controlled antenna trace.
- Keep WWVB input away from high-current switching traces (consider external
  antenna placement / shielded cable).
- Proper decoupling at every IC.

## Illumination / dimmer input

- Orange/white illumination/dimmer line is common in this Chrysler era.
- Blue AMP/ANT lead may be present if an Infinity amp / power antenna exists.
- **Verify against the actual van harness** (see [open-questions.md](open-questions.md)).
- Firmware should read dimmer to adjust display brightness day/night.

## Validation
Power-rail and current-draw checks are the first steps of
[bringup-test-plan.md](bringup-test-plan.md).

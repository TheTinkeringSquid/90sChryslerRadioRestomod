# UI State Machine

Mirrors [../firmware/src/ui_state_machine.h](../firmware/src/ui_state_machine.h).
This is the authoritative behavioral spec; the header is the code contract.

## States

```text
OFF              power switch off / standby
BOOT             init rails, codec, tuner, BT, display
AM_MODE          AM tuner active
FM_MODE          FM tuner active
BT_MODE          Bluetooth A2DP source
CASSETTE_MODE    tape inserted/selected
SETTINGS_MODE    general settings (clock/TZ/format)
PRESET_SET_MODE  storing a preset
CLOCK_DISPLAY_MODE  display showing clock (overlay on a source mode)
ERROR_MODE       fault (e.g. codec/tuner init fail)
```

## Events

```text
POWER_ON / POWER_OFF
AMFM_SHORT_PRESS / AMFM_LONG_PRESS
SET_SHORT_PRESS / SET_LONG_PRESS
PRESET_{1..5}_SHORT / PRESET_{1..5}_LONG
SEEK_UP_PRESS / SEEK_DOWN_PRESS
TUNE_CHANGE
VOL_CHANGE / BAL_CHANGE / FADER_CHANGE / BASS_CHANGE / TREBLE_CHANGE
H_PRESS / M_PRESS
TAPE_INSERTED / TAPE_EJECTED
FFWD_PRESS / RWD_PRESS
BT_CONNECTED / BT_DISCONNECTED
CALL_INCOMING / CALL_ENDED
WWVB_SYNC_OK / WWVB_SYNC_FAIL
```

## Mode cycling (the AM/FM button)

```text
AMFM_SHORT_PRESS:
  AM_MODE       -> FM_MODE
  FM_MODE       -> BT_MODE
  BT_MODE       -> AM_MODE
  CASSETTE_MODE -> (TBD: ignore, or switch to AM_MODE)

AMFM_LONG_PRESS (in BT_MODE) -> enter Bluetooth pairing
```

Tape insertion may override to `CASSETTE_MODE` (final factory-style behavior TBD).

## Key behaviors

### SET
- **Short:** toggle display clock ↔ source (factory behavior).
- **Long:** begin preset set / settings; light `SET` icon.

### Presets 1–5 (two banks, `1`/`2` icon)
- **Short:** recall preset in active bank.
- **Long:** store current station (AM/FM: band+frequency) into active bank.
- Bank select: TBD (e.g. SET combo) — preserve factory feel.

### Clock buttons (repurposed)
- **H** — long press: enter time-zone setting; short press in that mode: cycle
  TZ / hours offset. ("Home zone".)
- **M** — toggle 12/24-hour format. ("Military time".)

### Seek / Tune
- AM/FM: seek up/down to next station; tune knob for manual.
- BT: seek/tune optionally map to AVRCP next/prev (or inactive).

### Calls (HFP, phase-gated)
- `CALL_INCOMING` → call UI; answer/end mapping TBD (candidate: BT-mode + SET
  short press = answer/end; BT-mode + AM/FM long press = pairing).

## Display modes
Clock / radio frequency / Bluetooth status / cassette status. SET short press
toggles clock ↔ source. Icons (`SET`, `1`/`2`, tape, FFWD/RWD, `NR`) reflect
state — see [display-options.md](display-options.md).

## Persistence (NVS/flash)
Presets (×2 banks), time zone, DST handling, 12/24-hour format, last source,
volume/tone/balance/fader, BT pairing state. See
[../firmware/src/settings.h](../firmware/src/settings.h).

## ASCII state sketch

```text
        POWER_ON                 AMFM_SHORT (cycle)
 OFF ───────────► BOOT ──► AM_MODE ⇄ FM_MODE ⇄ BT_MODE ──┐
  ▲                 │         ▲          ▲        ▲       │
  │ POWER_OFF       │ fault   │ TAPE_EJECTED      │       │
  └─────────────────┴──► ERROR_MODE   CASSETTE_MODE◄──────┘ TAPE_INSERTED

  SET_LONG  → PRESET_SET_MODE / SETTINGS_MODE  (returns to prior source)
  SET_SHORT → toggle CLOCK_DISPLAY_MODE overlay
```

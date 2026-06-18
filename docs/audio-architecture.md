# Audio Architecture

## Signal flow

```text
  Si4735 tuner  L/R --\
  BT codec/DAC  L/R ---+--> source mux --> audio processor --> 4-ch amp --> speakers
  Cassette      L/R --/      (select)      (vol/tone/bal/fade)   (BTL)
                                                ^
  Faceplate pots/sliders --> ESP32 ADC --------/  (digital control)

  Mic --> codec ADC --> ESP32 (BT HFP uplink)
  BT HFP downlink (call audio) --> codec DAC --> into source mux as "BT" path
```

## Chosen approach: ADC-read controls + digital audio processor

Because this is a **dead-radio full replacement**, controls are read by the ESP32
ADC and applied digitally, rather than left in the analog path.

**Why (Option A over Option B):**
- Clean integration of the mux inputs — tuner (AM/FM), BT, cassette — i.e. the
  four user sources AM / FM / Cassette / BT (cassette is a required source).
- Consistent channel levels; easy balance/fader/tone.
- Settings can be stored/restored.
- Avoids depending on unknown original pot impedance/taper/condition and their
  noise susceptibility.

Option B (original pots/sliders directly in the analog path) is more factory-like
and lower firmware effort but makes multi-source mixing and noise control harder.
Kept as a fallback only if a specific control proves better left analog.

## Devices under consideration

| Role | Candidates | Notes |
|---|---|---|
| Codec (DAC+ADC+mic bias) | WM8960, ES8388 | I²S; needed for HFP mic path |
| Music-only DAC (phase 1) | PCM5102A | No mic ADC |
| Audio processor | TDA7313, TDA7439, modern I²C automotive AP | vol/tone/bal/fade + input select |
| Source switch | TS3A-series, MAX4544/MAX4xxx | low-distortion analog switches |
| 4-ch amp | TDA7388, TDA7850 | automotive BTL |

A single codec/audio-processor may cover several roles; final partitioning is a
schematic-phase decision.

## Mode → source mapping

| Mode | Source into mux | Display |
|---|---|---|
| AM | Si4735 (AM) | AM frequency |
| FM | Si4735 (FM) | FM frequency |
| BT | Codec DAC (A2DP stream) | `BT` / status |
| Cassette | Cassette line-in | tape icon + status |
| Call (HFP) | Codec DAC (downlink), mic → codec ADC (uplink) | call status |

## Anti-pop / sequencing

- **Startup:** init codec → mute amp → select source → apply vol/tone/bal/fade →
  enable amp after delay.
- **Source switch:** soft-mute during the switch.
- **Runtime:** smooth/ramped volume changes.
- **Shutdown:** mute amp → save state → power down gracefully.

ESP32 owns the amp mute/standby line — see [pin-map.md](pin-map.md) (`AMP_MUTE`,
`AMP_STBY`) and [power-protection.md](power-protection.md).

## Open audio questions
- Final audio-processor part (discrete switches + codec DSP, or dedicated AP IC)?
- Are cassette levels line-level out of the existing preamp, or do we need our
  own tape head preamp? (Phase 0 / [cassette-integration.md](cassette-integration.md).)
- Mic type: electret + bias vs digital MEMS? (Affects codec choice.)

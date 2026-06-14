# BOM Planning (Initial)

Part **classes** for early planning. Final parts must be verified for
availability, automotive suitability, and KiCad library/footprint support before
schematic capture. This is not a purchasable BOM yet.

## Controller
| Item | Candidate | Notes |
|---|---|---|
| MCU module | ESP32-WROOM-32 / ESP32-WROVER | **Bluetooth Classic required** (A2DP+HFP). NOT ESP32-S3. → OQ-19 |

## Audio
| Item | Candidate | Notes |
|---|---|---|
| Codec (DAC+ADC+mic) | WM8960 / ES8388 | for full HFP |
| DAC only (phase 1) | PCM5102A | music only, no mic |
| Audio processor | TDA7313 / TDA7439 / I²C automotive AP | vol/tone/bal/fade + input select → OQ-18 |
| Source switches | TS3A-series / MAX4544 / MAX4xxx | low-distortion analog |
| 4-ch amplifier | TDA7388 / TDA7850 | automotive BTL |

## Tuner
| Item | Candidate | Notes |
|---|---|---|
| AM/FM tuner | Si4735 (IC or module) | I²C, analog L/R out |

## Clock
| Item | Candidate | Notes |
|---|---|---|
| WWVB receiver | 60 kHz receiver module | external antenna may be needed → OQ-15 |
| RTC (fallback) | DS3231 | high-accuracy, key-off holdover |
| RTC backup | coin cell / supercap | optional |

## Display
| Item | VFD path | LED fallback |
|---|---|---|
| Driver | MAX6921 / PT631x / HT16512-class (after pin map) | HT16K33 / MAX7219 / TLC5940 / shift regs |
| Supplies | HV boost (~25–40 V) + filament (~2–4 V) | 5 V/3.3 V |
| Emitters | original glass | green 7-seg modules + discrete green icon LEDs |

→ Path decided by OQ-1/OQ-2.

## Power / protection
| Item | Class |
|---|---|
| Input fuse | automotive blade/holder |
| Reverse-polarity | P-FET (preferred) or diode |
| TVS | automotive load-dump-rated |
| Buck 12→5 V | automotive-grade switcher |
| 3.3 V | LDO or buck/LDO |
| Filtering | ferrites, LC/PI, bulk caps |
| ESD | TVS/ESD arrays on external lines |

## Microphone
| Item | Candidate |
|---|---|
| Electret + bias | external mic, shielded cable |
| or MEMS module | digital I²S/PCM |

## Connectors (footprints TBD after teardown)
Power/illumination, speaker (BTL ×4), front-panel, display (30–40 pin), cassette,
mic (3-pin), antenna (Motorola/U.FL), UART program/debug + test pads.

## Output of this doc
Feeds `../hardware/bom/` (per-revision CSV BOM once schematic exists) and the
KiCad symbol/footprint libraries under `../hardware/symbols/` and
`../hardware/footprints/`.

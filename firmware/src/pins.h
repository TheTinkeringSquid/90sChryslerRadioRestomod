// pins.h — ESP32 pin assignments
//
// ⚠️ PLACEHOLDER. Every value here is provisional and mirrors docs/pin-map.md.
// Do NOT treat these as final. Known conflicts to resolve at schematic time:
//   1. ADC1 is oversubscribed (6 analog controls + dimmer + maybe tune pot).
//      With Bluetooth Classic always on, ADC2 is unusable -> add an I2C ADC.
//   2. TUNE_A (25) collides with I2S LRCK (25).
//   3. Strapping/boot-sensitive pins used as placeholders: 0, 2, 5, 15.
//   4. Preset/H/M/EJT/FFWD/RWD assume an I/O expander (confirm after OQ-4).
// Keep this file and docs/pin-map.md in sync.

#pragma once

// ---- Analog controls (ADC1 only; GPIO34-39 are input-only) ----
#define PIN_VOL_ADC      36   // volume pot
#define PIN_BAL_ADC      39   // balance
#define PIN_FADER_ADC    34   // fader
#define PIN_BASS_ADC     35   // bass slider   (conflicts w/ DIMMER_SENSE)
#define PIN_TREBLE_ADC   32   // treble slider
#define PIN_TUNE_ADC     33   // only if tune is a pot (OQ-7)

// ---- Tune encoder (if encoder instead of pot) ----
#define PIN_TUNE_A       25   // ⚠ collides with I2S LRCK below
#define PIN_TUNE_B       26

// ---- Buttons (direct GPIO subset; rest via I/O expander if matrixed) ----
#define PIN_BTN_SEEK_UP   27
#define PIN_BTN_SEEK_DOWN 14
#define PIN_BTN_AMFM      13  // mode cycle (short) / pairing (long)
#define PIN_BTN_SET       23
// PRESET_1..5, H, M, EJT, FFWD, RWD: via I/O expander (see buttons.cpp)

// ---- I2C (Si4735, audio processor, DS3231, I/O expander, ext ADC) ----
#define PIN_I2C_SDA      21
#define PIN_I2C_SCL      22

// ---- I2S (codec WM8960 / ES8388) ----
#define PIN_I2S_MCLK     0    // ⚠ strapping pin — verify/relocate
#define PIN_I2S_BCLK     5    // ⚠ strapping pin — verify/relocate
#define PIN_I2S_LRCK     25   // ⚠ collides with PIN_TUNE_A
#define PIN_I2S_DOUT     19   // to codec (DAC)
#define PIN_I2S_DIN      18   // from codec (ADC / mic)

// ---- Control / status ----
#define PIN_AMP_MUTE     4    // amp mute   (active level TBD)
#define PIN_AMP_STBY     16   // amp standby
#define PIN_WWVB_DATA    17   // demodulated WWVB
#define PIN_WWVB_EN      2    // ⚠ strapping pin — verify/relocate
#define PIN_RADIO_ON     15   // ⚠ strapping pin — volume-knob power switch
#define PIN_DIMMER_SENSE 35   // ⚠ conflicts w/ PIN_BASS_ADC — needs own ADC ch

// ---- I/O expander (for the button block that doesn't fit native GPIO) ----
#define I2C_ADDR_IOEXP   0x20 // placeholder (e.g. MCP23017 / PCF8575)
#define I2C_ADDR_EXT_ADC 0x48 // placeholder external ADC for extra controls

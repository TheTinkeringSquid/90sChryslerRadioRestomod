# Bring-Up & Test Plan

Run top-to-bottom on a new board. Do not enable the amplifier until power rails
pass. Use a current-limited bench supply throughout early steps.

## 1. Power
1. Verify no shorts on 12 V, 5 V, 3.3 V (ohmmeter, power off).
2. Power via current-limited supply; watch inrush.
3. Confirm 5 V rail in tolerance.
4. Confirm 3.3 V rail in tolerance.
5. Confirm ESP32 boots.
6. Confirm amp stays **muted** during boot.
7. Confirm idle current draw is reasonable.

## 2. ESP32
1. Flash basic firmware.
2. Verify serial logging.
3. Test reset / boot buttons.
4. Test NVS settings read/write.

## 3. Controls
1. Verify each button input registers.
2. Verify debouncing.
3. Verify ADC values across each knob/slider travel.
4. Verify tune behavior (encoder counts or pot sweep).

## 4. Display
1. Test all digits / segments / icons.
2. Test brightness control (+ dimmer input).
3. Test time / frequency rendering.
4. Test SET, 1/2, tape, FFWD/RWD icons.

## 5. Audio
1. Inject test tone into amp path.
2. Verify all four speaker channels.
3. Verify mute / standby.
4. Test volume.
5. Test balance / fader.
6. Test bass / treble.
7. Test source switching **without pops**.

## 6. AM/FM
1. Confirm Si4735 I²C comms.
2. Confirm FM tuning.
3. Confirm AM tuning.
4. Confirm seek up/down.
5. Confirm presets (5 × 2 banks).
6. Test vehicle antenna input.

## 7. Bluetooth
1. Pair phone (A2DP).
2. Stream audio.
3. Test reconnect behavior.
4. Test AVRCP (if implemented).
5. Test BT-mode display.
6. Test call audio + mic (if HFP implemented).

## 8. Clock
1. Test RTC fallback (DS3231).
2. Test WWVB data input / decode.
3. Test time-zone setting (H).
4. Test 12/24-hour toggle (M).
5. Test SET display toggle.

## 9. Cassette
1. Detect tape insertion.
2. Route cassette audio.
3. Test eject.
4. Test FFWD/RWD signals.
5. Test tape icon + arrows.

## 10. Vehicle test
1. Install temporarily with fuse.
2. Verify current draw is sane.
3. Verify no alternator whine.
4. Verify AM/FM reception in-vehicle.
5. Verify Bluetooth range.
6. Verify display visibility day/night.
7. Verify dimmer/illumination behavior.
8. Check heat after extended listening.

---
Power/rail detail: [power-protection.md](power-protection.md).
Audio anti-pop sequencing: [audio-architecture.md](audio-architecture.md).

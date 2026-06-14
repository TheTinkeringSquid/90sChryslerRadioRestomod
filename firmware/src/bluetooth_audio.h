// bluetooth_audio.h — Bluetooth Classic A2DP (sink) + AVRCP + HFP abstraction.
// Requires an ESP32 with Bluetooth Classic (WROOM-32 / WROVER). NOT ESP32-S3.
// A2DP first; HFP hardware-ready but firmware-phased (build flag ENABLE_HFP).
#pragma once
#include <stdint.h>

enum class BtStatus : uint8_t { OFF, IDLE, PAIRING, CONNECTED, STREAMING, IN_CALL };

class BluetoothAudio {
 public:
  bool begin(const char* device_name);   // init A2DP sink -> I2S codec
  void startPairing();                    // discoverable (AMFM long press in BT)
  BtStatus status() const { return status_; }

  // AVRCP (optional)
  void play();
  void pause();
  void next();
  void prev();

  // HFP (phased; guarded by ENABLE_HFP)
  void answerCall();
  void endCall();

 private:
  BtStatus status_ = BtStatus::OFF;
  // TODO: A2DP sink callbacks -> I2S; AVRCP metadata for display; HFP audio
  // routing through codec ADC(mic)/DAC(call). See docs/audio-architecture.md.
};

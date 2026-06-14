// bluetooth_audio.cpp — SKELETON.
#include "bluetooth_audio.h"

bool BluetoothAudio::begin(const char* device_name) {
  (void)device_name;
  // TODO: init A2DP sink (e.g. ESP32-A2DP), wire stream to I2S codec,
  // register AVRCP + connection callbacks. status_ = IDLE on success.
  return true;
}

void BluetoothAudio::startPairing() { status_ = BtStatus::PAIRING; /* TODO */ }

void BluetoothAudio::play()  { /* TODO: AVRCP play */ }
void BluetoothAudio::pause() { /* TODO: AVRCP pause */ }
void BluetoothAudio::next()  { /* TODO: AVRCP next */ }
void BluetoothAudio::prev()  { /* TODO: AVRCP prev */ }

void BluetoothAudio::answerCall() { /* TODO: HFP answer (ENABLE_HFP) */ }
void BluetoothAudio::endCall()    { /* TODO: HFP end (ENABLE_HFP) */ }

// audio.h — audio source routing + volume/tone/balance/fader + amp mute/standby.
// Chosen approach: ADC-read controls applied digitally via codec/audio processor
// (see docs/audio-architecture.md). Owns anti-pop sequencing.
#pragma once
#include <stdint.h>

enum class AudioSource : uint8_t { NONE, TUNER, BLUETOOTH, CASSETTE, CALL };

class Audio {
 public:
  bool begin();                       // init codec + audio processor; amp muted
  bool selectSource(AudioSource s);   // soft-mute, switch, unmute

  void setVolume(uint8_t v);          // 0..255
  void setBalance(uint8_t b);         // 128 = center
  void setFader(uint8_t f);           // 128 = center
  void setBass(uint8_t b);            // 128 = flat
  void setTreble(uint8_t t);          // 128 = flat

  void muteAmp(bool mute);            // PIN_AMP_MUTE
  void ampStandby(bool standby);      // PIN_AMP_STBY
  void enableAmpAfterDelay();         // post-init anti-pop enable

 private:
  AudioSource source_ = AudioSource::NONE;
  // TODO: codec driver handle (WM8960/ES8388), audio-processor I2C ops,
  // source-mux control, ramped volume.
};

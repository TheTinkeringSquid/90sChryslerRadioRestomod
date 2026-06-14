// tuner_si4735.h — AM/FM tuner abstraction (Si4735 over I2C).
// Wraps a vendor driver (e.g. PU2CLR SI4735) behind a project interface so the
// UI doesn't depend on the specific part.
#pragma once
#include <stdint.h>

enum class Band : uint8_t { AM, FM };

class TunerSi4735 {
 public:
  bool begin();                       // I2C init + reset; false -> ERROR_MODE
  void setBand(Band b);
  void setFrequencyKHz(uint32_t khz);  // FM in 10s of kHz internally as needed
  uint32_t frequencyKHz() const { return freq_khz_; }
  Band band() const { return band_; }

  void seekUp();
  void seekDown();
  void tuneStep(int8_t steps);        // manual tune knob delta

  uint8_t signalQuality();            // RSSI/SNR for display/seek stop (TODO)

 private:
  Band band_ = Band::FM;
  uint32_t freq_khz_ = 0;
  // TODO: vendor driver instance; AM vs FM step/limits; antenna config.
};

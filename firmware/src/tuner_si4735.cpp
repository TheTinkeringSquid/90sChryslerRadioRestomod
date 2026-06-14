// tuner_si4735.cpp — SKELETON.
#include "tuner_si4735.h"
#include "pins.h"

bool TunerSi4735::begin() {
  // TODO: Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL); init vendor driver; reset.
  return true;  // TODO: false on I2C failure
}

void TunerSi4735::setBand(Band b)              { band_ = b; /* TODO: program */ }
void TunerSi4735::setFrequencyKHz(uint32_t k)  { freq_khz_ = k; /* TODO */ }
void TunerSi4735::seekUp()                     { /* TODO: hardware seek up */ }
void TunerSi4735::seekDown()                   { /* TODO: hardware seek down */ }
void TunerSi4735::tuneStep(int8_t steps)       { (void)steps; /* TODO */ }
uint8_t TunerSi4735::signalQuality()           { return 0; /* TODO: RSSI/SNR */ }

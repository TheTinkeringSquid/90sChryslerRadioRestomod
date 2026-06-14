// cassette.cpp — SKELETON.
#include "cassette.h"

bool Cassette::begin() {
  // TODO Level 1: configure TAPE_PRESENT (+ END_OF_TAPE) inputs.
  // TODO Level 2: configure MOTOR_EN/PWM, FFWD_EN, RWD_EN outputs (if present).
  return true;
}

void Cassette::poll(uint32_t now_ms) {
  (void)now_ms;
  // TODO: debounce tape-present / end-of-tape; app dispatches TAPE_INSERTED /
  // TAPE_EJECTED on edges.
}

void Cassette::play()        { transport_ = TapeTransport::PLAY;     /* TODO L2 */ }
void Cassette::stop()        { transport_ = TapeTransport::STOP;     /* TODO L2 */ }
void Cassette::fastForward() { transport_ = TapeTransport::FFWD;     /* TODO L2 */ }
void Cassette::rewind()      { transport_ = TapeTransport::RWD;      /* TODO L2 */ }
void Cassette::eject()       { transport_ = TapeTransport::EJECTING; /* TODO L2 */ }

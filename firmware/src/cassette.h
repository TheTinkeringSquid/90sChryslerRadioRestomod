// cassette.h — cassette mechanism abstraction (phased).
// Level 1: tape-present sense + route line-level audio. Level 2: full transport
// control (motor/FFWD/RWD/eject/sensors). See docs/cassette-integration.md.
#pragma once
#include <stdint.h>

enum class TapeTransport : uint8_t { STOP, PLAY, FFWD, RWD, EJECTING };

class Cassette {
 public:
  bool begin();
  void poll(uint32_t now_ms);     // update tape-present / end-of-tape (Level 1+)
  bool tapePresent() const { return tape_present_; }

  // Level 2 (optional; no-ops until motor control HW exists)
  void play();
  void stop();
  void fastForward();
  void rewind();
  void eject();
  TapeTransport transport() const { return transport_; }

 private:
  bool tape_present_ = false;
  TapeTransport transport_ = TapeTransport::STOP;
  // TODO: debounce TAPE_PRESENT/END_OF_TAPE; Level 2 motor/FFWD/RWD outputs.
};

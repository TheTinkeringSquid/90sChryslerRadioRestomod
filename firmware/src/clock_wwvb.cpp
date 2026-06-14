// clock_wwvb.cpp — SKELETON.
#include "clock_wwvb.h"
#include "pins.h"

bool ClockWwvb::begin() {
  // TODO: pinMode(PIN_WWVB_DATA, INPUT); drive PIN_WWVB_EN; init DS3231 over I2C.
  return true;
}

void ClockWwvb::poll(uint32_t now_ms) {
  (void)now_ms;
  // TODO: sample WWVB DATA, run the 60-bit/minute decoder; on a valid frame set
  // RTC + synced_ = true and have the app dispatch WWVB_SYNC_OK (else _FAIL).
}

TimeHMS ClockWwvb::now() {
  // TODO: read RTC, apply tz_offset_/DST. Placeholder:
  return TimeHMS{0, 0, 0};
}

void ClockWwvb::setTimeZoneOffset(int8_t hours) { tz_offset_ = hours; /* TODO persist */ }
void ClockWwvb::set24HourFormat(bool en)        { fmt24_ = en;        /* TODO persist */ }

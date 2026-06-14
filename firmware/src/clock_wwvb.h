// clock_wwvb.h — WWVB 60 kHz radio-controlled clock + DS3231 RTC fallback.
// Decodes WWVB, keeps time across key-off via RTC, holds TZ + 12/24h preference.
#pragma once
#include <stdint.h>

struct TimeHMS { uint8_t hour; uint8_t minute; uint8_t second; };

class ClockWwvb {
 public:
  bool begin();                 // init WWVB pins + DS3231 (if present)
  void poll(uint32_t now_ms);   // sample/decode WWVB frame; sync RTC on success

  TimeHMS now();                // current local time (RTC + TZ/DST applied)
  bool synced() const { return synced_; }

  void setTimeZoneOffset(int8_t hours);   // H button (hours offset)
  void set24HourFormat(bool en);          // M button (military time)
  bool is24Hour() const { return fmt24_; }

 private:
  bool synced_ = false;
  int8_t tz_offset_ = 0;        // TODO: persist via Settings
  bool dst_ = false;            // TODO: DST handling policy
  bool fmt24_ = false;
  // TODO: WWVB bit decoder/state machine; weak-signal tolerance; DS3231 driver.
};

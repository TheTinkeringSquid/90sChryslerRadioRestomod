// ui_state_machine.h — top-level UI/behavior state machine.
// Behavioral spec: docs/ui-state-machine.md (keep in sync with this file).

#pragma once
#include <stdint.h>

enum class UiState : uint8_t {
  OFF,
  BOOT,
  AM_MODE,
  FM_MODE,
  BT_MODE,
  CASSETTE_MODE,
  SETTINGS_MODE,
  PRESET_SET_MODE,
  CLOCK_DISPLAY_MODE,
  ERROR_MODE,
};

enum class UiEvent : uint8_t {
  POWER_ON, POWER_OFF,
  AMFM_SHORT_PRESS, AMFM_LONG_PRESS,
  SET_SHORT_PRESS, SET_LONG_PRESS,
  PRESET_1_SHORT, PRESET_1_LONG,
  PRESET_2_SHORT, PRESET_2_LONG,
  PRESET_3_SHORT, PRESET_3_LONG,
  PRESET_4_SHORT, PRESET_4_LONG,
  PRESET_5_SHORT, PRESET_5_LONG,
  SEEK_UP_PRESS, SEEK_DOWN_PRESS,
  TUNE_CHANGE,
  VOL_CHANGE, BAL_CHANGE, FADER_CHANGE, BASS_CHANGE, TREBLE_CHANGE,
  H_PRESS, M_PRESS,
  TAPE_INSERTED, TAPE_EJECTED,
  FFWD_PRESS, RWD_PRESS,
  BT_CONNECTED, BT_DISCONNECTED,
  CALL_INCOMING, CALL_ENDED,
  WWVB_SYNC_OK, WWVB_SYNC_FAIL,
};

class UiStateMachine {
 public:
  void begin();                 // init; enters BOOT then settles to last source
  void dispatch(UiEvent e);     // feed an event (from buttons/controls/BT/etc.)
  void tick(uint32_t now_ms);   // periodic housekeeping (timeouts, blink, etc.)

  UiState state() const { return state_; }

 private:
  void enter(UiState s);        // on-entry side effects (display/audio/source)
  void cycleSource();           // AM -> FM -> BT -> AM (AMFM short press)

  UiState state_ = UiState::OFF;
  UiState prev_source_ = UiState::AM_MODE;  // source to restore after settings
  uint8_t preset_bank_ = 1;                 // 1 or 2 (shown by display icon)
  // TODO: timers for long-press, settings timeout, clock-overlay auto-revert.
};

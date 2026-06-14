// ui_state_machine.cpp — SKELETON. Transitions outlined; effects are TODO.
#include "ui_state_machine.h"

#include "audio.h"
#include "display.h"
#include "settings.h"
#include "tuner_si4735.h"
#include "bluetooth_audio.h"

void UiStateMachine::begin() {
  enter(UiState::BOOT);
  // TODO: bring up subsystems (settings -> audio -> tuner -> BT -> display),
  // then restore last source from Settings and enter it.
  prev_source_ = UiState::AM_MODE;  // TODO: load from Settings
  enter(prev_source_);
}

void UiStateMachine::cycleSource() {
  switch (state_) {
    case UiState::AM_MODE: enter(UiState::FM_MODE); break;
    case UiState::FM_MODE: enter(UiState::BT_MODE); break;
    case UiState::BT_MODE: enter(UiState::AM_MODE); break;
    case UiState::CASSETTE_MODE:
      // OQ-20: factory-style behavior when tape is in. TODO: ignore or -> AM.
      enter(UiState::AM_MODE);
      break;
    default: enter(UiState::AM_MODE); break;
  }
}

void UiStateMachine::dispatch(UiEvent e) {
  switch (e) {
    case UiEvent::POWER_ON:        enter(UiState::BOOT); break;
    case UiEvent::POWER_OFF:       enter(UiState::OFF); break;

    case UiEvent::AMFM_SHORT_PRESS: cycleSource(); break;
    case UiEvent::AMFM_LONG_PRESS:
      if (state_ == UiState::BT_MODE) { /* TODO: BluetoothAudio::startPairing() */ }
      break;

    case UiEvent::SET_SHORT_PRESS:
      // TODO: toggle CLOCK_DISPLAY_MODE overlay vs current source.
      break;
    case UiEvent::SET_LONG_PRESS:
      prev_source_ = state_;
      enter(UiState::PRESET_SET_MODE);
      break;

    case UiEvent::SEEK_UP_PRESS:   /* TODO: tuner seek up / BT next */ break;
    case UiEvent::SEEK_DOWN_PRESS: /* TODO: tuner seek down / BT prev */ break;
    case UiEvent::TUNE_CHANGE:     /* TODO: manual tune */ break;

    case UiEvent::VOL_CHANGE:      /* TODO: Audio::setVolume(...) */ break;
    case UiEvent::BAL_CHANGE:      /* TODO: Audio::setBalance(...) */ break;
    case UiEvent::FADER_CHANGE:    /* TODO: Audio::setFader(...) */ break;
    case UiEvent::BASS_CHANGE:     /* TODO: Audio::setBass(...) */ break;
    case UiEvent::TREBLE_CHANGE:   /* TODO: Audio::setTreble(...) */ break;

    case UiEvent::H_PRESS:         /* TODO: time-zone / hours offset */ break;
    case UiEvent::M_PRESS:         /* TODO: 12/24h toggle */ break;

    case UiEvent::TAPE_INSERTED:   enter(UiState::CASSETTE_MODE); break;
    case UiEvent::TAPE_EJECTED:    enter(prev_source_); break;
    case UiEvent::FFWD_PRESS:      /* TODO: cassette FFWD / BT next */ break;
    case UiEvent::RWD_PRESS:       /* TODO: cassette RWD / BT prev */ break;

    case UiEvent::BT_CONNECTED:    /* TODO: display BT status */ break;
    case UiEvent::BT_DISCONNECTED: /* TODO: display BT status */ break;
    case UiEvent::CALL_INCOMING:   /* TODO: HFP call UI */ break;
    case UiEvent::CALL_ENDED:      /* TODO: restore */ break;

    case UiEvent::WWVB_SYNC_OK:    /* TODO: mark clock synced */ break;
    case UiEvent::WWVB_SYNC_FAIL:  /* TODO: fall back to RTC */ break;

    // Preset short/long handled by a helper in real impl; omitted in skeleton.
    default: break;
  }
}

void UiStateMachine::enter(UiState s) {
  state_ = s;
  // TODO on-entry effects per state:
  //  - select audio source + soft-mute during switch (see audio-architecture.md)
  //  - update display content + icons
  //  - for AM/FM: program tuner band/frequency
  //  - for BT: ensure A2DP active
  switch (s) {
    case UiState::AM_MODE:
    case UiState::FM_MODE:
    case UiState::BT_MODE:
      prev_source_ = s;
      break;
    default: break;
  }
}

void UiStateMachine::tick(uint32_t now_ms) {
  (void)now_ms;
  // TODO: long-press detection windows, settings-mode timeout,
  // clock-overlay auto-revert, blink SET icon while setting.
}

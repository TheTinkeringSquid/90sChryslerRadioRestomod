// settings.cpp — SKELETON.
#include "settings.h"
// #include <Preferences.h>

bool Settings::begin() {
  // TODO: Preferences.begin("radio", false); if (!load()) save() defaults.
  return true;
}

bool Settings::load() {
  // TODO: read blob/keys into `data`; return false if missing/corrupt.
  return true;
}

bool Settings::save() {
  // TODO: write `data` to NVS; throttle to avoid flash wear on rapid changes.
  return true;
}

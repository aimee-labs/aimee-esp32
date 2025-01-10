#pragma once

#include <Arduino.h>

inline String formatTimeSpan(time_t timeSpan) {
  int totalSeconds = timeSpan / 1000;
  int minutes = (totalSeconds % (60 * 60)) / 60;
  int seconds = totalSeconds % 60;
  return (minutes < 10 ? "0" : "") + String(minutes) + ":" +
         (seconds < 10 ? "0" : "") + String(seconds);
}

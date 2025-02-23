#include "PLCTimer.h"

static bool isTimerDone(timer *timer, unsigned long currentTime) {
  return (timer->startTime + timer->PRE < currentTime);
}

static void handleTONUpdate(timer *timer, unsigned long currentTime) {
  if (timer->EN) {
    if (isTimerDone(timer, currentTime)) {
      timer->DN = true;
      timer->TT = false;
    } else {
      timer->ACC = currentTime - timer->startTime;
      timer->TT = true;
    }
  } else {
    timer->startTime = currentTime;
    timer->DN = false;
    timer->ACC = 0;
    timer->TT = false;
  }
}

static void handleTOFUpdate(timer *timer, unsigned long currentTime) {
  if (timer->EN) {
    timer->startTime = currentTime;
    timer->DN = true;
    timer->ACC = 0;
    timer->TT = false;
  } else {
    if (isTimerDone(timer, currentTime)) {
      timer->DN = false;
      timer->TT = false;
    } else {
      timer->ACC = currentTime - timer->startTime;
      timer->TT = true;
      timer->DN = true;
    }
  }
}

static void handleRTOUpdate(timer *timer, unsigned long currentTime) {
  if (timer->EN) {
    if (isTimerDone(timer, currentTime)) {
      timer->TT = false;
      timer->ACC = timer->PRE;
      timer->startTime = currentTime - timer->ACC;
    } else {
      timer->ACC = currentTime - timer->startTime;
      timer->TT = true;
    }
  } else {
    timer->startTime = currentTime - timer->ACC;
    timer->TT = false;
  }
  if (timer->ACC >= timer->PRE) {
    timer->DN = true;
  } else {
    timer->DN = false;
  }
}

// Update array of timers based on the current time
void updateTimers(timer *timers, int numberofTimers) {
  unsigned long currentTime = millis();
  for (int i = 0; i < numberofTimers; i++) {
    switch (timers[i].type) {
      case TON:  // Timer On Delay
        handleTONUpdate(&timers[i], currentTime);
        break;

      case TOF:  // Timer Off Delay
        handleTOFUpdate(&timers[i], currentTime);
        break;

      case RTO:  // Retentive Timer On
        handleRTOUpdate(&timers[i], currentTime);
        break;
    }
  }
}

// Update a single timer based on the current time
void updateTimer(timer *timer) {
  unsigned long currentTime = millis();
  switch (timer->type) {
    case TON:  // Timer On Delay
      handleTONUpdate(timer, currentTime);
      break;

    case TOF:  // Timer Off Delay
      handleTOFUpdate(timer, currentTime);
      break;

    case RTO:  // Retentive Timer On
      handleRTOUpdate(timer, currentTime);
      break;
  }
}

void handleTimerReset(timer *timer, unsigned long currentTime) {
  timer->startTime = currentTime;
  timer->DN = false;
  timer->ACC = 0;
}

// Reset array of timers to their initial state
void resetTimers(timer *timers, int numberofTimers) {
  unsigned long currentTime = millis();
  for (int i = 0; i < numberofTimers; i++) {
    handleTimerReset(&timers[i], currentTime);
  }
}
// Reset a single timer to its initial state
void resetTimer(timer *timer) {
  unsigned long currentTime = millis();
  handleTimerReset(timer, currentTime);
}
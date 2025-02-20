#include "PLCTimer.h"
// Update array of timers based on the current time
void updateTimers(timer *timers, int numberofTimers) {
  unsigned long currentTime = millis();
  for (int i = 0; i < numberofTimers; i++) {
    switch (timers[i].type) {
      case TON:  // Timer On Delay
        if (timers[i].EN) {
          if (timers[i].startTime + timers[i].PRE < currentTime) {
            timers[i].DN = true;
            timers[i].TT = false;
          } else {
            timers[i].ACC = currentTime - timers[i].startTime;
            timers[i].TT = true;
          }
        } else {
          timers[i].startTime = currentTime;
          timers[i].DN = false;
          timers[i].ACC = 0;
          timers[i].TT = false;
        }
        break;

      case TOF:  // Timer Off Delay
        if (timers[i].EN) {
          timers[i].startTime = currentTime;
          timers[i].DN = true;
          timers[i].ACC = 0;
          timers[i].TT = false;

        } else {
          if (timers[i].startTime + timers[i].PRE < currentTime) {
            timers[i].DN = false;
            timers[i].TT = false;
          } else {
            timers[i].ACC = currentTime - timers[i].startTime;
            timers[i].TT = true;
            timers[i].DN = true;
          }
        }
        break;

      case RTO:  // Retentive Timer On
        if (timers[i].EN) {
          if (timers[i].startTime + timers[i].PRE < currentTime) {
            timers[i].TT = false;
            timers[i].ACC = timers[i].PRE;
            timers[i].startTime = currentTime - timers[i].ACC;
          } else {
            timers[i].ACC = currentTime - timers[i].startTime;
            timers[i].TT = true;
          }
        } else {
          timers[i].startTime = currentTime - timers[i].ACC;
          timers[i].TT = false;
        }
        if (timers[i].ACC >= timers[i].PRE) {
          timers[i].DN = true;
        } else {
          timers[i].DN = false;
        }

        break;
    }
  }
}

// Update a single timer based on the current time
void updateTimer(timer *timer) {
  unsigned long currentTime = millis();
  switch (timer->type) {
    case TON:  // Timer On Delay
      if (timer->EN) {
        if (timer->startTime + timer->PRE < currentTime) {
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
      break;

    case TOF:  // Timer Off Delay
      if (timer->EN) {
        timer->startTime = currentTime;
        timer->DN = true;
        timer->ACC = 0;
        timer->TT = false;

      } else {
        if (timer->startTime + timer->PRE < currentTime) {
          timer->DN = false;
          timer->TT = false;
        } else {
          timer->ACC = currentTime - timer->startTime;
          timer->TT = true;
          timer->DN = true;
        }
      }
      break;

    case RTO:  // Retentive Timer On
      if (timer->EN) {
        if (timer->startTime + timer->PRE < currentTime) {
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

      break;
  }
}
// Reset array of timers to their initial state
void resetTimers(timer *timers, int numberofTimers) {
  unsigned long currentTime = millis();
  for (int i = 0; i < numberofTimers; i++) {
    timers[i].startTime = currentTime;
    timers[i].DN = false;
    timers[i].ACC = 0;
  }
}
// Reset a single timer to its initial state
void resetTimer(timer *timer) {
  unsigned long currentTime = millis();
  timer->startTime = currentTime;
  timer->DN = false;
  timer->ACC = 0;
}
#ifndef PLCTIMER_H
#define PLCTIMER_H

#include <Arduino.h>
typedef enum {
  TON = 0,  // Timer On Delay
  TOF = 1,  // Timer Off Delay
  RTO = 2   // Retentive Timer On
} TIMER_TYPE;

typedef struct {
  unsigned long startTime;  // Timer start time
  union {
    unsigned long preset;  // Timer preset time
    unsigned long PRE;     // Alias for preset
  };
  union {
    unsigned long accumulated;  // Timer accumulated time
    unsigned long ACC;          // Alias for accumulated
  };
  union {
    bool enable;  // Enable flag for the timer
    bool EN;      // Alias for enable flag
  };
  union {
    bool timerTiming;  // Timer timing flag
    bool TT;           // Alias for timing flag
  };
  union {
    bool done;  // Done flag for the timer
    bool DN;    // Alias for done flag
  };
  TIMER_TYPE type;  // Type of timer (TON, TOF, RTO)
} timer;

void updateTimers(timer *timers, int numberofTimers);
void updateTimer(timer *timer);
void resetTimers(timer *timers, int numberofTimers);
void resetTimer(timer *timer);

#endif  // PLCTIMER_H
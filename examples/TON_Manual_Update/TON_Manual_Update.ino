/*
This example showcases how to manually update the timers. If you want to ensure simialar operation to a standard PLC,
you might want to update your inputs to a buffer, run your logic, update outputs, and update timers then repeat.
By default when you create a timer, each time you attempt to reference it, say checking if it is done, the timer will
automaticlly update using the current time. However, if you don't want this behavior and want to update timers when you choose,
You can disable autoUpdate for one or more timers. If you do this, you must remember to update your timers manually.

*/

#include <PLCTimer.h>

int LED = LED_BUILTIN;
const int numberofTimers = 2;
Timer T[numberofTimers];


void setup() {
  pinMode(LED, OUTPUT);
  // using the constructor for multiple settings
  T[0] = Timer(TON, 1000);
  // using individual setters
  T[0].EN(true);
  T[0].autoUpdate(false);
  T[1].PRE(1000);
  T[1].type(TON);
  T[1].autoUpdate(false);
}

void loop() {
  //update timers manually at top of loop
  T[0].updateTimer();
  T[1].updateTimer();
  //Run code later
  if (T[0].TT()) {
    digitalWrite(LED, true);
    T[1].EN(false);
  } else {
    T[1].EN(true);
  }

  if (T[1].TT()) {
    digitalWrite(LED, false);
    T[0].EN(false);
  } else {
    T[0].EN(true);
  }
}

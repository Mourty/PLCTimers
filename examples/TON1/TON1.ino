/*
This example showcases how a Timer On Delay (TON) works. Typical operation is if the timer enable (EN) bit is on,
 the accumulated time (ACC) begins counting up This will set the Timer Timing (TT) bit. If ACC is equal to the preset (PRE) value,
 the time stops counting up, and sets the done bit (DN). The ACC value is reset to 0 if EN is turned off. 
 If you want it to keep it, check the RTO type.
 In this example we are using the built in LED. We are flashing it on and off with 1 second on, and 1 second off.
 I modeled the operation of the TON after Allen Bradley PLC Timers. Link below
 https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/timer-on-delay--ton-.html

*/

#include <PLCTimer.h>
unsigend long millitime = millis();
unssigned long microtime = micros();
int LED = LED_BUILTIN;
const int numberofTimers = 2;
Timer T[numberofTimers];

void setup() {
  pinMode(LED, OUTPUT);
  // using the constructor for multiple settings
  T[0] = Timer(TON,1000,true);

  // using individual setters
  T[1].PRE(1000);
  T[1].type(TON);
}

void loop() {

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

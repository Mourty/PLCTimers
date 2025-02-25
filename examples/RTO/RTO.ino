/*
This example showcases how a Retentive Timer On (RTO) works. This instruction works very similarly to the TON
The major difference is the accumulated (ACC) value is kept when the enable (EN) bit is turned off. This means
the timer is able to add different times an event happened over time. Another difference is since the ACC isn't
cleared when the EN bit is turned off, the done (DN) bit can be on even if the EN bit is off. This type of timer
must be reset using the provided resetTimer, or resetTimers functions. Note on singular timer update or reset,
the timer must be passed by reference using the & symbol just before it.
In this example we are turning off the built in LED after a button connected between pin 3 and ground is pressed
for a cumulative total of 2 seconds. if the button is held down for a consecutive 5 seconds the LED will turn back
off. The button must be released for the second timer to reset. This allows for the cycle to continue.
I modeled the operation of the RTO after Allen Bradley PLC Timers. Link below
https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/retentive-timer-on--rto-.html
I did the same for the reset function.
https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/reset--res-.html

*/
#include <PLCTimer.h>

int LED = LED_BUILTIN;
const int buttonPin = 3;
const int numberofTimers = 2;
Timer T[numberofTimers];

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  T[0] = Timer(RTO,2000);
  T[1] = Timer(TON, 5000);
}

void loop() {
  if (digitalRead(buttonPin)) {
    T[0].EN(true);
  } else {
    T[0].EN(false);
  }

  if (T[0].DN()) {
    digitalWrite(LED, true);
  } else {
    digitalWrite(LED, false);
  }

  if (digitalRead(buttonPin)) {
    T[1].EN(true);
  } else {
    T[1].EN(false);
  }

  if (T[1].DN()) {
    T[0].resetTimer();
  }
}

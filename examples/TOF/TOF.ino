/*
This example showcases how a Timer Off Delay (TOF) works. This type of timer is desgined to work in a backwards way
compared to TON. The Done (DN) bit is set when the accumulated (ACC) does not equal the preset (PRE) amount.
When the enable (EN) bit is set the Timer Timing (TT) bit will be set, and the accumulated value ACC will start counting.
When the ACC = the preset (PRE) value, the DN bit will turn off.
In this example we are using the built in LED, and a button that connects pin 3 to ground when pressed. the LED is always off
unless the button is pressed. The LED will Turn on while the button is pressed. The LED will remain on for 1 second after the button is released.

*/
#include <PLCTimer.h>

int LED = LED_BUILTIN;
const int buttonPin = 3;
timer T;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  T.PRE = 1000;
  T.type = TOF;
}

void loop() {
  updateTimer(&T);

  if (digitalRead(buttonPin)) {
    T.EN = true;
  } else {
    T.EN = false;
  }

  if (T.DN) {
    digitalWrite(LED, true);
  } else {
    digitalWrite(LED, false);
  }
}

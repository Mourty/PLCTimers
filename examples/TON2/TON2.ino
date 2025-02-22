/*
This example shows a different way to utilize a Timer On Delay (TON). This program uses pins 10-13 as LED outputs. It will light one at a time, for 1 second each , in a repeating cycle.
This is using the accumulated time (ACC) to determine which LED to turn on. There are better ways to write this code with parameterization, and other cool optimizations.
However, I just wanted to make plain the utility of the ACC value.

*/
#include <PLCTimer.h>

int LED1 = 13;
int LED2 = 12;
int LED3 = 11;
int LED4 = 10;
timer T;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  T.PRE = 4000;
  T.type = TON;
  T.EN = true;
}

void loop() {
  updateTimer(&T);

if (T.DN){
  resetTimer(&T);
}
if (T.ACC >= 0 && T.ACC <1000){
  digitalWrite(LED1, true);
}else{
  digitalWrite(LED1, false);
}

if (T.ACC >= 1001 && T.ACC <2000){
  digitalWrite(LED2, true);
}else{
  digitalWrite(LED2, false);
}

if (T.ACC >= 2001 && T.ACC <3000){
  digitalWrite(LED3, true);
}else{
  digitalWrite(LED3, false);
}

if (T.ACC >= 3001 && T.ACC <4000){
  digitalWrite(LED4, true);
}else{
  digitalWrite(LED4, false);
}
}

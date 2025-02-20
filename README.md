# PLC Timers Library
<br/>

This is a timer library for Arduino that provides Timer On Delay (TON), Timer Off Delay(TOF), and Retentive Timer On(RTO) timers similar to Allen Bradley PLC timers.
I want to note that I'm not a professional programmer. I'm sure this shows in the code, but I was working on something for class and wanted to make it public. This is a very basic library mainly made for my own use, but maybe someone else will like it. I hope it works for you, and I hope you find it useful.
<br/>

## Installation
### I. Using Arduino Library Manager (Hopefully)
Search for **PLCTimer** in the Arduino Library Manager and install the latest version.

### II. Manual Installation

If you would like to install manually, you can follow these steps:

1. Download the latest release
2. Extract and place the folder in `~/Arduino/libraries/`

<br/>

## API Reference
Functions: 

	void updateTimers(timer *timers, int numberofTimers); - Updates multiple timers.

	void updateTimer(timer *timer; - Updates one timer.

	void resetTimers(timer *timer int numberofTimers); - Resets multiple specific timers.

	void resetTimer(timer *timer); - Resets a specific timer.

TIMER_TYPE - Enum defining timer types:

	TON (0) - Timer On Delay

	TOF (1) - Timer Off Delay

	RTO (2) - Retentive Timer On

The behavior of the timers are based on Allen Bradley timer behavior and names. Below you can find links to what I referenced to do this.
https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/timer-on-delay--ton-.html

https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/timer-off-delay--tof-.html

https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/retentive-timer-on--rto-.html

https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/reset--res-.html

<br/>

## License
This library is licensed under the MIT license. Basically, freely use how you want, just attribute.


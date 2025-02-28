# PLC Timers Library
<br/>

This is a timer library for Arduino that provides Timer On Delay (TON), Timer Off Delay(TOF), and Retentive Timer On(RTO) timers similar to Allen Bradley PLC timers.
I want to note that I'm not a professional programmer. I'm sure this shows in the code, but I was working on something for class and wanted to make it public. This is a very basic library mainly made for my own use, but maybe someone else will like it. I hope it works for you, and I hope you find it useful.
<br/>

## Installation
### I. Using Arduino Library Manager
Search for **PLCTimer** in the Arduino Library Manager and install the latest version.

### II. Manual Installation

If you would like to install manually, you can follow these steps:

1. Download the latest release
2. Extract and place the folder in `~/Arduino/libraries/`

<br/>

## API Reference

Create a timer with
Timer myTimer;

Edit a timer with
myTimer.type(TON);
myTimer.PRE(1000);

Check a timer with
myTimer.DN();
myTimer.ACC();
See full documentation in the [DOCUMENTATION](DOCUMENTATION) file. 
This library has native support for the Extended Time Library. https://github.com/Mourty/ExtendedTime

The behavior of the timers are based on Allen Bradley timer behavior and names. Below you can find links to what I referenced to do this.
https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/timer-on-delay--ton-.html

https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/timer-off-delay--tof-.html

https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/retentive-timer-on--rto-.html

https://www.rockwellautomation.com/en-ca/docs/factorytalk-design-studio/current/contents-ditamap/instructions/instruction-set/timer-and-counter-instructions/reset--res-.html

<br/>

## License
### The Licensing of this library has changed from MIT, to LGPL 2.1+ as of Version 2.0.0
This library is licensed under the **GNU Lesser General Public License v2.1 or later (LGPL 2.1+).**  

This means you are free to use, modify, and distribute this library under the terms of the LGPL 2.1+.  
However, if you modify and distribute this library, you must also release the modified version under the same LGPL license.  

For more details, see the [LICENSE](LICENSE) file.  

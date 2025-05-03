/*
  PLCTimer - PLC style timers for Arduino
  Copyright (c) [2025] [Mourty]

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this library; if not, see <https://www.gnu.org/licenses/>.
*/
#ifndef PLCTIMER_H
#define PLCTIMER_H

#include <Arduino.h>

#ifndef FORCE_ULL
#define FORCE_ULL 0
#endif

// Support for my ExtenedTime Library
// This changes data types on compile based on if you have the lib included.
// If you have FORCE_ULL enabled, all the unsigned long data types will be
// unsigned long long type instead.
#ifdef __has_include
#if __has_include("ExtendedTime.h")
#define USE_EXTENDED_TIME 1
typedef unsigned long long TimerStartTimeDataType;
#else
#define USE_EXTENDED_TIME 0
typedef unsigned long TimerStartTimeDataType;
#endif
#endif

#if USE_EXTENDED_TIME && FORCE_ULL
typedef unsigned long long TimerOtherTimeDataType;
#else
typedef unsigned long TimerOtherTimeDataType;
#endif

typedef enum
{
    TON = 0, // Timer On Delay
    TOF = 1, // Timer Off Delay
    RTO = 2  // Retentive Timer On
} TIMER_TYPE;

class Timer
{
  public:
    // Single Timer constructors
    Timer();
    Timer(TIMER_TYPE timerType, TimerOtherTimeDataType presetTime);
    Timer(TIMER_TYPE timerType, TimerOtherTimeDataType presetTime, bool enableTimer);

    // Getters and Setters, also has aliases
    void PRE(TimerOtherTimeDataType value);
    TimerOtherTimeDataType PRE();
    void preset(TimerOtherTimeDataType value);
    TimerOtherTimeDataType preset();

    void ACC(TimerOtherTimeDataType value);
    TimerOtherTimeDataType ACC();
    void accumulated(TimerOtherTimeDataType value);
    TimerOtherTimeDataType accumulated();

    void EN(bool value);
    bool EN();
    void enable(bool value);
    bool enable();

    void TT(bool value);
    bool TT();
    void timerTiming(bool value);
    bool timerTiming();

    void DN(bool value);
    bool DN();
    void done(bool value);
    bool done();

    void startTime(TimerStartTimeDataType value);
    TimerStartTimeDataType startTime();

    void type(TIMER_TYPE value);
    TIMER_TYPE type();

    // helper functions
    void resetTimer();
    void resetTimers(Timer *timers, int numTimers);

  protected:
    TimerStartTimeDataType startTime_V;
    TimerOtherTimeDataType preset_V;
    TimerOtherTimeDataType accumulated_V;
    bool enable_V;
    bool timerTiming_V;
    bool done_V;
    TIMER_TYPE type_V;
    // protected helper functions
    void updateTimer();
    void handleTimerReset(TimerStartTimeDataType currentTime);
    bool isTimerDone(TimerStartTimeDataType currentTime);
    void handleTONUpdate(TimerStartTimeDataType currentTime);
    void handleTOFUpdate(TimerStartTimeDataType currentTime);
    void handleRTOUpdate(TimerStartTimeDataType currentTime);
    virtual TimerStartTimeDataType getTime();
};

class MicroTimer : public Timer
{
  public:
    // Single Timer constructors
    MicroTimer();
    MicroTimer(TIMER_TYPE timerType, TimerOtherTimeDataType presetTime);
    MicroTimer(TIMER_TYPE timerType, TimerOtherTimeDataType presetTime, bool enableTimer);

  protected:
    TimerStartTimeDataType getTime() override;
};

// Timer arrays constructors
void initializeTimers(Timer timers[], int numTimers);
void initializeTimers(Timer timers[], int numTimers, TIMER_TYPE timerType, TimerOtherTimeDataType presetTime);
void initializeTimers(Timer timers[], int numTimers, TIMER_TYPE timerType, TimerOtherTimeDataType presetTime,
                      bool enableTimer);
// MicroTimer arrays constructors
void initializeMicroTimers(MicroTimer timers[], int numTimers);
void initializeMicroTimers(MicroTimer timers[], int numTimers, TIMER_TYPE timerType,
                           TimerOtherTimeDataType presetTime);
void initializeMicroTimers(MicroTimer timers[], int numTimers, TIMER_TYPE timerType, TimerOtherTimeDataType presetTime,
                           bool enableTimer);
#endif // PLCTIMER_H
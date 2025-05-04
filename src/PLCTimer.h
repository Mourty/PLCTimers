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

#pragma once
#include "PLCTimerConfig.h"

#ifndef PLCTIMER_H
#define PLCTIMER_H

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
    Timer(TIMER_TYPE timerType, TimerTimeDataType presetTime);
    Timer(TIMER_TYPE timerType, TimerTimeDataType presetTime, bool enableTimer);
    Timer(TIMER_TYPE timerType, TimerTimeDataType presetTime, bool enableTimer, bool autoUpdate);

    // Getters and Setters, also has aliases
    void PRE(TimerTimeDataType value);
    TimerTimeDataType PRE();
    void preset(TimerTimeDataType value);
    TimerTimeDataType preset();

    void ACC(TimerTimeDataType value);
    TimerTimeDataType ACC();
    void accumulated(TimerTimeDataType value);
    TimerTimeDataType accumulated();

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

    void startTime(TimerTimeDataType value);
    TimerTimeDataType startTime();

    void type(TIMER_TYPE value);
    TIMER_TYPE type();

    void autoUpdate(bool value);
    bool autoUpdate();

    // helper functions
    void resetTimer();
    void updateTimer();
    
    //TimerTimeDataType getTime();
  protected:
    TimerTimeDataType startTime_V;
    TimerTimeDataType preset_V;
    TimerTimeDataType accumulated_V;
    bool enable_V;
    bool timerTiming_V;
    bool done_V;
    TIMER_TYPE type_V;
    bool autoUpdate_V;
    // protected helper functions

    void handleTimerReset(TimerTimeDataType currentTime);
    void handleUpdateTimer(TimerTimeDataType currentTime);
    bool isTimerDone(TimerTimeDataType currentTime);
    void handleTONUpdate(TimerTimeDataType currentTime);
    void handleTOFUpdate(TimerTimeDataType currentTime);
    void handleRTOUpdate(TimerTimeDataType currentTime);
    virtual TimerTimeDataType getTime();
};

class MicroTimer : public Timer
{
  public:
    // Single Timer constructors
    MicroTimer();
    MicroTimer(TIMER_TYPE timerType, TimerTimeDataType presetTime);
    MicroTimer(TIMER_TYPE timerType, TimerTimeDataType presetTime, bool enableTimer);
    MicroTimer(TIMER_TYPE timerType, TimerTimeDataType presetTime, bool enableTimer, bool autoUpdate);

  protected:
    TimerTimeDataType getTime();
};
// Timer arrays constructors
void initializeTimers(Timer timers[], int numTimers);
void initializeTimers(Timer timers[], int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime);
void initializeTimers(Timer timers[], int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime,
                      bool enableTimer);
void initializeTimers(Timer timers[], int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime,
                      bool enableTimer, bool autoUpdate);

// MicroTimer arrays constructors
void initializeMicroTimers(MicroTimer timers[], int numTimers);
void initializeMicroTimers(MicroTimer timers[], int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime);
void initializeMicroTimers(MicroTimer timers[], int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime,
                           bool enableTimer);
void initializeMicroTimers(MicroTimer timers[], int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime,
                           bool enableTimer, bool autoUpdate);
#endif // PLCTIMER_H
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

#include "PLCTimer.h"
#include <Arduino.h>

// Single Timer Constructors
Timer::Timer()
{
    preset_V = 0;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = TON;
}
Timer::Timer(TIMER_TYPE timerType, TimerOtherTimeDataType presetTime)
{
    preset_V = presetTime;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
}

Timer::Timer(TIMER_TYPE timerType, TimerOtherTimeDataType presetTime, bool enableTimer)
{
    preset_V = presetTime;
    enable_V = enableTimer;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
}
// Single MicroTimer Constructors
MicroTimer::MicroTimer()
{
    preset_V = 0;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = TON;
}
MicroTimer::MicroTimer(TIMER_TYPE timerType, TimerOtherTimeDataType presetTime)
{
    preset_V = presetTime;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
}

MicroTimer::MicroTimer(TIMER_TYPE timerType, TimerOtherTimeDataType presetTime, bool enableTimer)
{
    preset_V = presetTime;
    enable_V = enableTimer;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
}

// Timer Arrays Contructors

void initializeTimers(Timer *timers, int numTimers)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer();
    }
}

void initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, TimerOtherTimeDataType presetTime)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer(timerType, presetTime);
    }
}

void initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, TimerOtherTimeDataType presetTime,
                      bool enableTimer)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer(timerType, presetTime, enableTimer);
    }
}

// Micro Timer Arrays Constructors
void initializeMicroTimers(MicroTimer *timers, int numTimers)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = MicroTimer();
    }
}

void initializeMicroTimers(MicroTimer *timers, int numTimers, TIMER_TYPE timerType, TimerOtherTimeDataType presetTime)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = MicroTimer(timerType, presetTime);
    }
}

void initializeMicroTimers(MicroTimer *timers, int numTimers, TIMER_TYPE timerType, TimerOtherTimeDataType presetTime,
                           bool enableTimer)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = MicroTimer(timerType, presetTime, enableTimer);
    }
}

// Getters and Setters, also has aliases
void Timer::PRE(TimerOtherTimeDataType value)
{
    preset_V = value;
}

TimerOtherTimeDataType Timer::PRE() const
{
    updateTimer();
    return preset_V;
}

void Timer::preset(TimerOtherTimeDataType value)
{
    PRE(value);
}

TimerOtherTimeDataType Timer::preset() const
{
    updateTimer();
    return PRE();
}

void Timer::ACC(TimerOtherTimeDataType value)
{
    accumulated_V = value;
}

TimerOtherTimeDataType Timer::ACC() const
{
    updateTimer();
    return accumulated_V;
}

void Timer::accumulated(TimerOtherTimeDataType value)
{
    ACC(value);
}

TimerOtherTimeDataType Timer::accumulated() const
{
    updateTimer();
    return ACC();
}

void Timer::EN(bool value)
{
    enable_V = value;
}

bool Timer::EN() const
{
    updateTimer();
    return enable_V;
}

void Timer::enable(bool value)
{
    EN(value);
}

bool Timer::enable() const
{
    updateTimer();
    return EN();
}

void Timer::TT(bool value)
{
    timerTiming_V = value;
}

bool Timer::TT() const
{
    updateTimer();
    return timerTiming_V;
}

void Timer::timerTiming(bool value)
{
    TT(value);
}

bool Timer::timerTiming() const
{
    updateTimer();
    return TT();
}

void Timer::DN(bool value)
{
    done_V = value;
}

bool Timer::DN() const
{
    updateTimer();
    return done_V;
}

void Timer::done(bool value)
{
    DN(value);
}

bool Timer::done() const
{
    updateTimer();
    return DN();
}

void Timer::startTime(TimerStartTimeDataType value)
{
    startTime_V = value;
}

TimerStartTimeDataType Timer::startTime() const
{
    updateTimer();
    return startTime_V;
}

void Timer::type(TIMER_TYPE value)
{
    type_V = value;
}

TIMER_TYPE Timer::type() const
{
    updateTimer();
    return type_V;
}

// Timer Updating logic

bool Timer::isTimerDone(TimerStartTimeDataType currentTime)
{
    return (startTime_V + preset_V < currentTime);
}

void Timer::handleTONUpdate(TimerStartTimeDataType currentTime)
{
    if (!enable_V)
    {
        startTime_V = currentTime;
        done_V = false;
        accumulated_V = 0;
        timerTiming_V = false;
        return;
    }
    if (isTimerDone(currentTime))
    {
        done_V = true;
        timerTiming_V = false;
        return;
    }
    accumulated_V = currentTime - startTime_V;
    timerTiming_V = true;
}

void Timer::handleTOFUpdate(TimerStartTimeDataType currentTime)
{
    if (enable_V)
    {
        startTime_V = currentTime;
        done_V = true;
        accumulated_V = 0;
        timerTiming_V = false;
        return;
    }
    if (isTimerDone(currentTime))
    {
        done_V = false;
        timerTiming_V = false;
        return;
    }
    accumulated_V = currentTime - startTime_V;
    timerTiming_V = true;
    done_V = true;
}

void Timer::handleRTOUpdate(TimerStartTimeDataType currentTime)
{
    if (!enable_V)
    {
        startTime_V = currentTime - accumulated_V;
        timerTiming_V = false;
        return;
    }
    if (isTimerDone(currentTime))
    {
        done_V = true;
        timerTiming_V = false;
        accumulated_V = preset_V;
        return;
    }
    accumulated_V = currentTime - startTime_V;
    timerTiming_V = true;
}

#if USE_EXTENDED_TIME
TimerStartTimeDataType Timer::getTime()
{
    return extendedMillis();
}

TimerStartTimeDataType MicroTimer::getTime()
{
    return extendedMicros();
}
#else
TimerStartTimeDataType Timer::getTime()
{
    return millis();
}

TimerStartTimeDataType MicroTimer::getTime()
{
    return micros();
}
#endif

// Update a single timer based on the current time
void Timer::updateTimer()
{
    TimerStartTimeDataType currentTime = getTime();
    switch (type_V)
    {
    case TON: // Timer On Delay
        handleTONUpdate(currentTime);
        break;

    case TOF: // Timer Off Delay
        handleTOFUpdate(currentTime);
        break;

    case RTO: // Retentive Timer On
        handleRTOUpdate(currentTime);
        break;
    }
}

void Timer::handleTimerReset(TimerStartTimeDataType currentTime)
{
    startTime_V = currentTime;
    done_V = false;
    accumulated_V = 0;
}

// Reset a single timer to its initial state
void Timer::resetTimer()
{
    TimerStartTimeDataType currentTime = millis();
    handleTimerReset(currentTime);
}
// Reset multiple timers
void Timer::resetTimers(Timer *timers, int numTimers)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i].resetTimer();
    }
}

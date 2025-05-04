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

// Single Timer Constructors
Timer::Timer()
{
    preset_V = 0;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = TON;
    autoUpdate_V = true;
}

Timer::Timer(TIMER_TYPE timerType, TimerTimeDataType presetTime)
{
    preset_V = presetTime;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
    autoUpdate_V = true;
}

Timer::Timer(TIMER_TYPE timerType, TimerTimeDataType presetTime, bool enableTimer)
{
    preset_V = presetTime;
    enable_V = enableTimer;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
    autoUpdate_V = true;
}

Timer::Timer(TIMER_TYPE timerType, TimerTimeDataType presetTime, bool enableTimer, bool autoUpdate)
{
    preset_V = presetTime;
    enable_V = enableTimer;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
    autoUpdate_V = autoUpdate;
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
    autoUpdate_V = true;
}
MicroTimer::MicroTimer(TIMER_TYPE timerType, TimerTimeDataType presetTime)
{
    preset_V = presetTime;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
    autoUpdate_V = true;
}

MicroTimer::MicroTimer(TIMER_TYPE timerType, TimerTimeDataType presetTime, bool enableTimer)
{
    preset_V = presetTime;
    enable_V = enableTimer;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
    autoUpdate_V = true;
}

MicroTimer::MicroTimer(TIMER_TYPE timerType, TimerTimeDataType presetTime, bool enableTimer, bool autoUpdate)
{
    preset_V = presetTime;
    enable_V = enableTimer;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
    autoUpdate_V = autoUpdate;
}

// Timer Arrays Contructors

void initializeTimers(Timer *timers, int numTimers)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer();
    }
}

void initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer(timerType, presetTime);
    }
}

void initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime,
                      bool enableTimer)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer(timerType, presetTime, enableTimer);
    }
}

void initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime,
                      bool enableTimer, bool autoUpdate)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer(timerType, presetTime, enableTimer, autoUpdate);
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

void initializeMicroTimers(MicroTimer *timers, int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = MicroTimer(timerType, presetTime);
    }
}

void initializeMicroTimers(MicroTimer *timers, int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime,
                           bool enableTimer)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = MicroTimer(timerType, presetTime, enableTimer);
    }
}

void initializeMicroTimers(MicroTimer *timers, int numTimers, TIMER_TYPE timerType, TimerTimeDataType presetTime,
                           bool enableTimer, bool autoUpdate)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = MicroTimer(timerType, presetTime, enableTimer, autoUpdate);
    }
}

// Getters and Setters, also has aliases
void Timer::PRE(TimerTimeDataType value)
{
    preset_V = value;
}

TimerTimeDataType Timer::PRE()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return preset_V;
}

void Timer::preset(TimerTimeDataType value)
{
    PRE(value);
}

TimerTimeDataType Timer::preset()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return PRE();
}

void Timer::ACC(TimerTimeDataType value)
{
    accumulated_V = value;
}

TimerTimeDataType Timer::ACC()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return accumulated_V;
}

void Timer::accumulated(TimerTimeDataType value)
{
    ACC(value);
}

TimerTimeDataType Timer::accumulated()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return ACC();
}

void Timer::EN(bool value)
{
    enable_V = value;
}

bool Timer::EN()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return enable_V;
}

void Timer::enable(bool value)
{
    EN(value);
}

bool Timer::enable()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return EN();
}

void Timer::TT(bool value)
{
    timerTiming_V = value;
}

bool Timer::TT()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return timerTiming_V;
}

void Timer::timerTiming(bool value)
{
    TT(value);
}

bool Timer::timerTiming()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return TT();
}

void Timer::DN(bool value)
{
    done_V = value;
}

bool Timer::DN()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return done_V;
}

void Timer::done(bool value)
{
    DN(value);
}

bool Timer::done()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return DN();
}

void Timer::startTime(TimerTimeDataType value)
{
    startTime_V = value;
}

TimerTimeDataType Timer::startTime()
{
    if (autoUpdate_V)
    {
        updateTimer();
    }
    return startTime_V;
}

void Timer::type(TIMER_TYPE value)
{
    type_V = value;
}

TIMER_TYPE Timer::type()
{
    return type_V;
}

void Timer::autoUpdate(bool value)
{
    autoUpdate_V = value;
}

bool Timer::autoUpdate()
{
    return autoUpdate_V;
}

// Timer Updating logic

bool Timer::isTimerDone(TimerTimeDataType currentTime)
{
    return (startTime_V + preset_V < currentTime);
}

void Timer::handleTONUpdate(TimerTimeDataType currentTime)
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

void Timer::handleTOFUpdate(TimerTimeDataType currentTime)
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

void Timer::handleRTOUpdate(TimerTimeDataType currentTime)
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
TimerTimeDataType Timer::getTime()
{
    return extendedMillis();
}

TimerTimeDataType MicroTimer::getTime()
{
    return extendedMicros();
}
#else
TimerTimeDataType Timer::getTime()
{
    return plcMillis();
}

TimerTimeDataType MicroTimer::getTime()
{
    return plcMicros();
}
#endif

// Update a single timer based on the current time
void Timer::handleUpdateTimer(TimerTimeDataType currentTime)
{
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

void Timer::updateTimer()
{
    TimerTimeDataType currentTime = getTime();
    handleUpdateTimer(currentTime);
}



void Timer::handleTimerReset(TimerTimeDataType currentTime)
{
    startTime_V = currentTime;
    done_V = false;
    accumulated_V = 0;
}

// Reset a single timer to its initial state
void Timer::resetTimer()
{
    TimerTimeDataType currentTime = getTime();
    handleTimerReset(currentTime);
}



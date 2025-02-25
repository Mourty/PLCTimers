#include "PLCTimer.h"

#include <Arduino.h>

Timer::Timer()
{
    preset_V = 0;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = TON;
}
Timer::Timer(TIMER_TYPE timerType, unsigned long presetTime)
{
    preset_V = presetTime;
    enable_V = false;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
}

Timer::Timer(TIMER_TYPE timerType, unsigned long presetTime, bool enableTimer)
{
    preset_V = presetTime;
    enable_V = enableTimer;
    startTime_V = 0;
    accumulated_V = 0;
    done_V = false;
    type_V = timerType;
}

// Timer Arrays
void Timer::initializeTimers(Timer *timers, int numTimers)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer();
    }
}
void Timer::initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, unsigned long presetTime)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer(timerType, presetTime);
    }
}
void Timer::initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, unsigned long presetTime,
                             bool enableTimer)
{
    for (int i = 0; i < numTimers; ++i)
    {
        timers[i] = Timer(timerType, presetTime, enableTimer);
    }
}

// Getters and Setters, also has aliases
void Timer::PRE(unsigned long value)
{
    preset_V = value;
}

unsigned long Timer::PRE() const
{
    updateTimer();
    return preset_V;
}

void Timer::preset(unsigned long value)
{
    PRE(value);
}

unsigned long Timer::preset() const
{
    updateTimer();
    return PRE();
}

void Timer::ACC(unsigned long value)
{
    accumulated_V = value;
}

unsigned long Timer::ACC() const
{
    updateTimer();
    return accumulated_V;
}

void Timer::accumulated(unsigned long value)
{

    ACC(value);
}

unsigned long Timer::accumulated() const
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

void Timer::startTime(unsigned long value)
{
    startTime_V = value;
}

unsigned long Timer::startTime() const
{
    updateTimer();
    return startTime_V;
}

void Timer::epoch(unsigned long value)
{
    epoch_V = value;
}

unsigned long Timer::epoch() const
{
    updateTimer();
    return epoch_V;
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

bool Timer::isTimerDone(unsigned long currentTime)
{
    return (startTime_V + preset_V < currentTime);
}

void Timer::handleTONUpdate(unsigned long currentTime)
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

void Timer::handleTOFUpdate(unsigned long currentTime)
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

void Timer::handleRTOUpdate(unsigned long currentTime)
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

// Update a single timer based on the current time
void Timer::updateTimer()
{
    unsigned long currentTime = millis();
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

void Timer::handleTimerReset(unsigned long currentTime)
{
    startTime_V = currentTime;
    done_V = false;
    accumulated_V = 0;
}

// Reset a single timer to its initial state
void Timer::resetTimer()
{
    unsigned long currentTime = millis();
    handleTimerReset(currentTime);
}
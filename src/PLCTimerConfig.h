#pragma once
// if you want to force all numeric data types to be unsigned long long data types, you need to uncomment the next line
// #define FORCE_ULL 1

// if you want to use your own custom time function to replace millis() and micros() or you aren't using this with
// ardunio , uncomment the next line

// #define PLCTIMERS_USE_CUSTOM_TIME 1

// If the user defines this compiler flag, they must define the following two functions before including this library:
//    TimerTimeDataType plcMillis();
//    TimerTimeDataType plcMicros();
// note: you will need to manually ensure the "TimerTimeDataType" matches either the unsigned long, or unsigned long
// long format chosen by the FORCE_ULL flag

#ifndef FORCE_ULL
#define FORCE_ULL 0
#endif

#ifndef PLCTIMERS_USE_CUSTOM_TIME
#define PLCTIMERS_USE_CUSTOM_TIME 0
#endif

// Support for my ExtenedTime Library
// This changes data types on compile based on if you have the lib included.
// If you have FORCE_ULL enabled, all the unsigned long data types will be
// unsigned long long type instead.
#ifdef __has_include
#if __has_include("ExtendedTime.h") && PLCTIMERS_USE_CUSTOM_TIME == 0
#define USE_EXTENDED_TIME 1
typedef unsigned long long TimerTimeDataType;
#else
#define USE_EXTENDED_TIME 0
typedef unsigned long TimerTimeDataType;
#endif
#endif

#if FORCE_ULL
typedef unsigned long long TimerTimeDataType;
#else
typedef unsigned long TimerTimeDataType;
#endif

#if PLCTIMERS_USE_CUSTOM_TIME == 1
#warning "PLCTimers: Custom Timer Functions Enabled. Ensure you have replacment functions defined before the include"
extern TimerTimeDataType plcMillis();
extern TimerTimeDataType plcMicros();

#elif (defined(ARDUINO) || defined(ARDUINO_ARCH_AVR) || defined(ESP_PLATFORM))
#warning "PLCTimers: Default Arduino Timer Functions Enabled."
#include <Arduino.h>

inline TimerTimeDataType plcMillis()
{
    return millis();
}

inline TimerTimeDataType plcMicros()
{
    return micros();
}
#else
#error "PLCTimers: This library is intended for Arduino. Please check the config header to adapt to your use"
#endif
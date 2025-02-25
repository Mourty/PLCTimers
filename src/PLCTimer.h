#ifndef PLCTIMER_H
#define PLCTIMER_H

#include <Arduino.h>
typedef enum
{
    TON = 0, // Timer On Delay
    TOF = 1, // Timer Off Delay
    RTO = 2  // Retentive Timer On
} TIMER_TYPE;

class Timer
{
  public:
    // Constructors
    // Single Timers
    Timer();
    Timer(TIMER_TYPE timerType, unsigned long presetTime);
    Timer(TIMER_TYPE timerType, unsigned long presetTime, bool enableTimer);

    // Timer Arrays
    static void initializeTimers(Timer *timers, int numTimers);
    static void initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, unsigned long presetTime);
    static void initializeTimers(Timer *timers, int numTimers, TIMER_TYPE timerType, unsigned long presetTime,
                                 bool enableTimer);

    // Getters and Setters, also has aliases
    void PRE(unsigned long value);
    unsigned long PRE() const;
    void preset(unsigned long value);
    unsigned long preset() const;

    void ACC(unsigned long value);
    unsigned long ACC() const;
    void accumulated(unsigned long value);
    unsigned long accumulated() const;

    void EN(bool value);
    bool EN() const;
    void enable(bool value);
    bool enable() const;

    void TT(bool value);
    bool TT() const;
    void timerTiming(bool value);
    bool timerTiming() const;

    void DN(bool value);
    bool DN() const;
    void done(bool value);
    bool done() const;

    void startTime(unsigned long value);
    unsigned long startTime() const;

    void epoch(unsigned long value);
    unsigned long epoch() const;

    void type(TIMER_TYPE value);
    TIMER_TYPE type() const;

    // helper functions
    void resetTimer();

  private:
    unsigned long startTime_V;
    unsigned long preset_V;
    unsigned long accumulated_V;
    unsigned long epoch_V;
    bool enable_V;
    bool timerTiming_V;
    bool done_V;
    TIMER_TYPE type_V;
    // private helper functions
    void updateTimer();
    void handleTimerReset(unsigned long currentTime);
    bool isTimerDone(unsigned long currentTime);
    void handleTONUpdate(unsigned long currentTime);
    void handleTOFUpdate(unsigned long currentTime);
    void handleRTOUpdate(unsigned long currentTime);
};

#endif // PLCTIMER_H
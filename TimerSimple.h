#ifndef TimerSimple_h
#define TimerSimple_h

#include <stdint.h>
#include <Arduino.h>

//----------------
class TimerSimple{
  protected:
    bool is_on_=false;//true если еще работает, false если выкл или закончился  
    unsigned long ring_time_=0;
    unsigned long last_time_=0;

    bool IsCanRing();
  public:
    void Start(unsigned long duration);
    void Stop();
    bool Check();
};
//----------------
#endif

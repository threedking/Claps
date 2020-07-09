#ifndef Worker_h
#define Worker_h

#include <stdint.h>
#include <Arduino.h>

//----------------
class iWorker{
  private:  
  public:
    virtual ~iWorker(){};
    virtual void Work()=0;
};
//----------------    
class WorkerSwitch: public iWorker{
  private:
    bool IsOn=false;//Если переключения доступны, то это текущее состояние
    bool RegularIsOn=false;//Если переключения НЕ доступны, то это текущее состояние
    bool IsRegular=false;//Недоступны ли переключения    
    
    uint8_t pinWork=255;//255 - неправильно или не задан
  public:
    WorkerSwitch(uint8_t new_pinWork);
    virtual ~WorkerSwitch(){};
    
    void Work() override;//Переключает IsOn, если переключения доступны + применяет
    
    bool GetIsOn();
    void SetRegularIsOn(bool newRegularIsOn);
    bool SetIsRegular(bool newIsRegular);
};
//----------------
#endif

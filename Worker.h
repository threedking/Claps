#ifndef Worker_h
#define Worker_h

#include <stdint.h>
#include <Arduino.h>

//----------------
class IWorker{
  private:  
  public:
    virtual ~IWorker()=default;
    virtual void Work()=0;
};
//----------------    
class WorkerSwitch: public IWorker{
  private:
    bool is_on_=false;//Если переключения доступны, то это текущее состояние
    bool regular_is_on_=true;//Если переключения НЕ доступны, то это текущее состояние(без хлопков выключается вручную)
    bool is_regular_=false;//Недоступны ли переключения    
    
    uint8_t pin_work_=255;//255 - неправильно или не задан
  public:
    WorkerSwitch(uint8_t new_pin_work);
    virtual ~WorkerSwitch()=default;
    
    void Work() override;//Переключает IsOn, если переключения доступны + применяет
    void Apply();
    
    bool GetIsOn() const;
    void SetRegularIsOn(bool new_regular_is_on);
    void SetIsRegular(bool new_is_regular);
};
//----------------
#endif

#ifndef WorkerObserveClaps_h
#define WorkerObserveClaps_h

#include "Worker.h"
#include "ClapsCounter.h"

#include <stdint.h>
//#include <Arduino.h>

#include <ArduinoSTL.h>
#include <list>

//----------------
class IObserver{    
  public:
    virtual ~IObserver()=default;
    virtual void Update(const int &event_code) = 0;
};

class ISubject{
 public:
  virtual ~ISubject()=default;
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};

class ClapsCounterSubj : public ISubject, public ClapsCounter{
  protected:
    std::list<IObserver *> list_observer_;
  public:
    ClapsCounterSubj(uint8_t new_pin_audio_d);
    virtual ~ClapsCounterSubj()=default;
    void Attach(IObserver *observer) override;
    void Detach(IObserver *observer) override;
    void Notify() override;
    void Announce()override;
};

class WorkerSwitchObs : public IObserver, public WorkerSwitch{
  private:
    ClapsCounterSubj &claps_counter_subj_;
    int trigger_number_=0;//Наблюдатель отреагирует, если код события соответствует этому коду срабатывания
  public:
    WorkerSwitchObs(uint8_t new_pin_work, int new_trigger_number, ClapsCounterSubj &new_claps_counter_Subj_);
    virtual ~WorkerSwitchObs();
    
    void Update(const int &eventCode) override;
    void RemoveMeFromTheList();
};
//----------------
#endif

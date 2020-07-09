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
    virtual ~IObserver(){};
    virtual void Update(const int &eventCode) = 0;
};

class ISubject{
 public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};

class ClapsCounterSubj : public ISubject, public ClapsCounter{
  protected:
    std::list<IObserver *> list_observer_;
  public:
    virtual ~ClapsCounterSubj(){}
    void Attach(IObserver *observer) override;
    void Detach(IObserver *observer) override;
    void Notify() override;
    void Announce()override;
};

class WorkerSwitchObs : public IObserver, public WorkerSwitch{
  private:
    ClapsCounterSubj &ClapsCounterSubj_;
    int TriggerNumber;//Наблюдатель будет оповещен, если код события соответствует этому коду срабатывания
  public:
    WorkerSwitchObs(uint8_t new_pinWork, int newTriggerNumber, ClapsCounterSubj &newClapsCounterSubj);
    virtual ~WorkerSwitchObs();
    
    void Update(const int &eventCode) override;
    void RemoveMeFromTheList();
};
//----------------
#endif

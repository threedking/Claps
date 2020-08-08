#include "WorkerObserveClaps.h"
//------------------------
ClapsCounterSubj::ClapsCounterSubj(uint8_t new_pinAudioD):ClapsCounter(new_pinAudioD){}
//------------------------
void ClapsCounterSubj::Attach(IObserver *observer){
  list_observer_.push_back(observer);
}
//------------------------
void ClapsCounterSubj::Detach(IObserver *observer){
  list_observer_.remove(observer);
}
//------------------------    
void ClapsCounterSubj::Notify(){
  uint8_t Claps=this->GetClaps();
  for (auto &it : list_observer_){
    it->Update(int(Claps));
  }
}
//------------------------
void ClapsCounterSubj::Announce(){
  this->Notify();
  this->ResetClaps();
}
//------------------------
//------------------------
//------------------------
WorkerSwitchObs::WorkerSwitchObs(uint8_t new_pinWork, int newTriggerNumber, ClapsCounterSubj &newClapsCounterSubj) :WorkerSwitch(new_pinWork), ClapsCounterSubj_(newClapsCounterSubj),TriggerNumber(newTriggerNumber) {
      this->ClapsCounterSubj_.Attach(this);
    }
//------------------------
WorkerSwitchObs::~WorkerSwitchObs(){
      this->RemoveMeFromTheList();  
    }
//------------------------
void WorkerSwitchObs::Update(const int &eventCode){
      if(this->TriggerNumber==eventCode){
        this->Work();
      }
    }
//------------------------
void WorkerSwitchObs::RemoveMeFromTheList() {
      this->ClapsCounterSubj_.Detach(this);
    }
//------------------------

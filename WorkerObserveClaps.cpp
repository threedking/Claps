#include "WorkerObserveClaps.h"
//------------------------
ClapsCounterSubj::ClapsCounterSubj(uint8_t new_pin_audio_d):ClapsCounter(new_pin_audio_d){}
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
  uint8_t claps=this->GetClaps();
  for (auto &it : list_observer_){
    it->Update(int(claps));
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
WorkerSwitchObs::WorkerSwitchObs(uint8_t new_pin_work, int new_trigger_number, ClapsCounterSubj &new_claps_counter_subj_) :WorkerSwitch(new_pin_work), claps_counter_subj_(new_claps_counter_subj_),trigger_number_(new_trigger_number) {
      this->claps_counter_subj_.Attach(this);
    }
//------------------------
WorkerSwitchObs::~WorkerSwitchObs(){
      this->RemoveMeFromTheList();  
    }
//------------------------
void WorkerSwitchObs::Update(const int &event_code){
      if(this->trigger_number_ == event_code){
        this->Work();
      }
    }
//------------------------
void WorkerSwitchObs::RemoveMeFromTheList() {
      this->claps_counter_subj_.Detach(this);
    }
//------------------------

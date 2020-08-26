#include "TimerSimple.h"
//------------------------
bool TimerSimple::IsCanRing(){
  unsigned long now = millis();
  if(this->ring_time_ >= this->last_time_){
    return this->ring_time_ <= now || now < this->last_time_ && now < this->ring_time_; //С защитой от переполнения после ring
  }else{
    return this->ring_time_ <= now && now < this->last_time_;//С защитой от переполнения после last
  }
}
//------------------------
void TimerSimple::Start(unsigned long duration){
  if(duration > 0){
    this->last_time_ = millis();
    this->ring_time_ = this->last_time_ + duration;
    this->is_on_=true;
  }
}
//------------------------
void TimerSimple::Stop(){
  this->is_on_=false;
}
//------------------------
bool TimerSimple::Check(){
  if(this->is_on_){ 
    this->is_on_=!this->IsCanRing();
  }
  return this->is_on_;
}
//------------------------

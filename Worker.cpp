#include "Worker.h"
//------------------------
WorkerSwitch::WorkerSwitch(uint8_t new_pin_work){
  if(new_pin_work <= 13){
    this->pin_work_=new_pin_work;
    pinMode(this->pin_work_,INPUT);
  }else{
    //Serial.println("Worker pin set wrong");
  }  
}
//------------------------    
void WorkerSwitch::Work(){//Переключает is_on, если переключения доступны + применяет
  if(!this->is_regular_){
    this->is_on_=!this->is_on_;
  }
  this->Apply();
}
//------------------------
void WorkerSwitch::Apply(){
  digitalWrite(this->pin_work_, !this->is_regular_ ? this->is_on_ : this->regular_is_on_);  
}
//------------------------
bool WorkerSwitch::GetIsOn() const{
  return !this->is_regular_ ? this->is_on_ : this->regular_is_on_;
}
//------------------------
void WorkerSwitch::SetRegularIsOn(bool new_regular_is_on){
  this->regular_is_on_=new_regular_is_on;
  this->Apply();
}
//------------------------
bool WorkerSwitch::SetIsRegular(bool new_is_regular){
  this->is_regular_=new_is_regular;
  this->Apply();
}
//------------------------    

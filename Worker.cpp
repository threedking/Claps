#include "Worker.h"
//------------------------
WorkerSwitch::WorkerSwitch(uint8_t new_pinWork){
  if(new_pinWork<=13){
    this->pinWork=new_pinWork;
    pinMode(this->pinWork,INPUT);
  }else{
    //Serial.println("Worker pin set wrong");
  }  
}
//------------------------    
void WorkerSwitch::Work(){//Переключает IsOn, если переключения доступны + применяет
  if(!this->IsRegular){
    this->IsOn=!this->IsOn;
  }
  digitalWrite(this->pinWork,!this->IsRegular?this->IsOn:this->RegularIsOn);
}
//------------------------
bool WorkerSwitch::GetIsOn(){
  return !this->IsRegular?this->IsOn:this->RegularIsOn;
}
//------------------------
void WorkerSwitch::SetRegularIsOn(bool newRegularIsOn){
  this->RegularIsOn=newRegularIsOn;
}
//------------------------
bool WorkerSwitch::SetIsRegular(bool newIsRegular){
  this->IsRegular=newIsRegular;
}
//------------------------    

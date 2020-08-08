#include "WorkerObserveClaps.h"

#include <ArduinoSTL.h>
#include <vector>

ClapsCounterSubj ClCounter(2);

//std::vector<std::unique_ptr<WorkerSwitchObs>> vec_Workers;
std::vector<WorkerSwitchObs*> vec_Workers;

bool ClapsOn=true;//Вкл ли управление хлопками

void setup() {
  //Serial.begin(9600);

  vec_Workers.push_back(new WorkerSwitchObs( 3,2,ClCounter ));
  vec_Workers.push_back(new WorkerSwitchObs( 4,3,ClCounter ));
}

void loop() {  
  if(ClapsOn != (analogRead(A1)>600?true:false)){ //Нужно ли переключить?
    ClapsOn=!ClapsOn;
    for(auto &it : vec_Workers){
      it->SetIsRegular(!ClapsOn);
    }
    if(!ClapsOn){
      ClCounter.HardReset();
    }
  }  
  if(ClapsOn){
    ClCounter.Update();  
  }
}

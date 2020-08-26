#include "WorkerObserveClaps.h"

#include <ArduinoSTL.h>
#include <vector>

ClapsCounterSubj claps_counter(2);

//std::vector<std::unique_ptr<WorkerSwitchObs>> vec_workers;
std::vector<WorkerSwitchObs*> vec_workers;

bool claps_on=true;//Вкл ли управление хлопками

void setup() {
  //Serial.begin(9600);

  vec_workers.push_back(new WorkerSwitchObs( 3,2,claps_counter ));
  vec_workers.push_back(new WorkerSwitchObs( 4,3,claps_counter ));
}

void loop() {  
  if(claps_on != (analogRead(A1)>600?true:false)){ //Нужно ли переключить?
    claps_on=!claps_on;
    for(auto &it : vec_workers){
      it->SetIsRegular(!claps_on);
    }
    if(!claps_on){
      claps_counter.HardReset();
    }
  }  
  if(claps_on){
    claps_counter.Update();  
  }
}

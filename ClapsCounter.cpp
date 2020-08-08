#include "ClapsCounter.h"
//------------------------
void TimerSimple::Start(unsigned long duration){
  if(duration>0){
    this->ringTime=millis()+duration;
    IsOn=true;
  }
}
//------------------------
void TimerSimple::Stop(){
  IsOn=false;
}
//------------------------
bool TimerSimple::Check(){
  if(IsOn){
    IsOn=!((this->ringTime <= millis())?true:false);
  }
  return IsOn;      
}
//------------------------
//------------------------
//------------------------
ClapsCounter::ClapsCounter(uint8_t new_pinAudioD){
  if(new_pinAudioD<=13){
    this->pinAudioD=new_pinAudioD;
    pinMode(this->pinAudioD,INPUT);
  }else{
    this->state=CounterState::ERR;
    //Serial.println("Audio pin set wrong"); 
  }
}
//------------------------
void ClapsCounter::Update(){
  switch(this->state){
    case CounterState::OFF:       //Счет не начат
      if( (!this->timer.Check()) && (digitalRead(this->pinAudioD)) ){//Наничать только если таймер не активен
        this->claps=1;
        this->state=CounterState::WAIT;
        this->timer.Start(this->timeconsts.WAIT);
      }
      break;
    case CounterState::WAIT:      //Глухое ожидание после хлопка
      if(!this->timer.Check()){
        this->state=CounterState::SILENCE;
        this->timer.Start(this->timeconsts.SILENCE);
      }
      break;
    case CounterState::SILENCE:   //Выжидание в тишине между хлопками         
      if(this->timer.Check()){
        if(digitalRead(this->pinAudioD)){//Тишина нарушена
          this->state=CounterState::OFF;//Прекратить подсчет
          this->timer.Start(this->timeconsts.END);
          //this->claps=0; //Или обнулить, или анонсировать зафиксированные хлопки
          Announce();
        }
      }else{//Время вышло, тишина не нарушена
        this->state=CounterState::LISTEN;
        this->timer.Start(this->timeconsts.LISTEN);
      }
      break;
      case CounterState::LISTEN:    //Ожидание нового хлопка         
        if(this->timer.Check()){
          if(digitalRead(this->pinAudioD)){//Обнаружен ли новый хлопок
            this->claps++;
            this->state=CounterState::WAIT;
            this->timer.Start(this->timeconsts.WAIT);
          }
        }else{//Время вышло, хлопков не было
          this->state=CounterState::OFF;
          this->timer.Start(this->timeconsts.END);
          Announce();
        }
      break;
      default:
      break;
  }
}
//------------------------
uint8_t ClapsCounter::GetClaps(){//Возвращает значение, если подсчет окончен. Иначе 0
  return this->state==CounterState::OFF?this->claps:0;
}
//------------------------
void ClapsCounter::ResetClaps(){//Сбрасывает последний подсчет в 0
  if(this->state==CounterState::OFF){
    this->claps=0;    
  }
}
//------------------------
void ClapsCounter::HardReset(){//Сбрасывает и подсчет, и состяние
  this->timer.Stop();
  this->state=CounterState::OFF;
  this->claps=0;
}
//------------------------

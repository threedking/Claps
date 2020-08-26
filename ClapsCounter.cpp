#include "ClapsCounter.h"
//------------------------
ClapsCounter::ClapsCounter(uint8_t new_pin_audio_d){
  if(new_pin_audio_d <= 13){
    this->pin_audio_d_=new_pin_audio_d;
    pinMode(this->pin_audio_d_,INPUT);
  }else{
    this->state_=CounterState::kErr;
    //Serial.println("Audio pin set wrong"); 
  }
}
//------------------------
void ClapsCounter::Update(){
  switch(this->state_){
    case CounterState::kOff:       //Счет не начат
      if( !this->timer_.Check() && digitalRead(this->pin_audio_d_) ){//Наничать только если таймер не активен
        this->claps_=1;
        this->state_=CounterState::kWait;
        this->timer_.Start(this->time_consts_.kWait);
      }
      break;
    case CounterState::kWait:      //Глухое ожидание после хлопка
      if(!this->timer_.Check()){
        this->state_=CounterState::kSilence;
        this->timer_.Start(this->time_consts_.kSilence);
      }
      break;
    case CounterState::kSilence:   //Выжидание в тишине между хлопками         
      if(this->timer_.Check()){
        if(digitalRead(this->pin_audio_d_)){//Тишина нарушена
          this->state_=CounterState::kOff;//Прекратить подсчет
          this->timer_.Start(this->time_consts_.kEnd);
          //this->claps_=0; //Или обнулить, или анонсировать зафиксированные хлопки
          Announce();
        }
      }else{//Время вышло, тишина не нарушена
        this->state_=CounterState::kListen;
        this->timer_.Start(this->time_consts_.kListen);
      }
      break;
      case CounterState::kListen:    //Ожидание нового хлопка         
        if(this->timer_.Check()){
          if(digitalRead(this->pin_audio_d_)){//Обнаружен ли новый хлопок
            this->claps_++;
            this->state_=CounterState::kWait;
            this->timer_.Start(this->time_consts_.kWait);
          }
        }else{//Время вышло, хлопков не было
          this->state_=CounterState::kOff;
          this->timer_.Start(this->time_consts_.kEnd);
          Announce();
        }
      break;
      default://CounterState::ERR не обрабатывать
      break;
  }
}
//------------------------
uint8_t ClapsCounter::GetClaps() const{//Возвращает значение, если подсчет окончен. Иначе 0
  return this->state_ == CounterState::kOff ? this->claps_ : 0;
}
//------------------------
void ClapsCounter::ResetClaps(){//Сбрасывает хлопки в 0, если не ведется подчет
  if(this->state_ == CounterState::kOff){
    this->claps_=0;    
  }
}
//------------------------
void ClapsCounter::HardReset(){//Сбрасывает и подсчет, и состяние
  this->timer_.Stop();
  this->state_=CounterState::kOff;
  this->claps_=0;
}
//------------------------

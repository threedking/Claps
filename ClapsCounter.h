#ifndef ClapsCounter_h
#define ClapsCounter_h

#include "TimerSimple.h"

//----------------
class ClapsCounter{
  private:
    enum class CounterState{
      kOff,      //Счет не начат
      kWait,     //Глухое ожидание после хлопка
      kSilence,  //Выжидание в тишине между хлопками 
      kListen,   //Ожидание нового хлопка
      kErr       //Работа невозможна
    };
    CounterState state_=CounterState::kOff;

    struct TimeConstants{
      const unsigned long kWait=100;     //Глухое ожидание после хлопка
      const unsigned long kSilence=100;  //Выжидание в тишине между хлопками
      const unsigned long kListen=300;   //Ожидание нового хлопка
      const unsigned long kEnd=500;      //Время нереагирования после окончания серии
    };
    TimeConstants time_consts_;
    
    TimerSimple timer_;
    
    uint8_t pin_audio_d_=255;//255 - неправильно или не задан
    uint8_t claps_=0;//количество хлопков в завершенной серии

    /*ClapsCounter
    
    class iState{      
      private:  
      public:
    }
    class StateOFF: public iState{
      private:
      public:
    }
    class StateWAIT: public iState{
      private:
      public:
    }
    class StateSILENCE: public iState{
      private:
      public:
    }
    class StateLISTEN: public iState{
      private:
      public:
    }
    class StateERR: public iState{
      private:
      public:
    } */   
    
 public:      
    ClapsCounter(uint8_t new_pin_audio_d);
    virtual ~ClapsCounter()=default;
    void Update();
    uint8_t GetClaps() const;//Возвращает значение, если подсчет окончен. Иначе 0
    void ResetClaps();//Сбрасывает хлопки в 0, если не ведется подчет
    void HardReset();//Сбрасывает и подсчет, и состяние
    virtual void Announce(){}; // Вызывается в Update. При наследовании с интерфейсом издателя, переопределить. 
};
//----------------
#endif

#ifndef ClapsCounter_h
#define ClapsCounter_h

#include <stdint.h>
#include <Arduino.h>

//----------------
class TimerSimple{
  private:
    bool IsOn=false;//true если еще работает, false если выкл или закончился  
    unsigned long ringTime=0;  
  public:
    void Start(unsigned long duration);
    void Stop();
    bool Check();
};
//----------------
class ClapsCounter{
  private:
    enum class CounterState{
      OFF,      //Счет не начат
      WAIT,     //Глухое ожидание после хлопка
      SILENCE,  //Выжидание в тишине между хлопками 
      LISTEN,   //Ожидание нового хлопка
      ERR       //Работа невозможна
    };
    CounterState state=CounterState::OFF;

    struct TimeConstants{
      unsigned long WAIT=100;     //Глухое ожидание после хлопка
      unsigned long SILENCE=100;  //Выжидание в тишине между хлопками
      unsigned long LISTEN=300;   //Ожидание нового хлопка
      unsigned long END=500;      //Время нереагирования после окончания серии
    };
    const TimeConstants timeconsts;
    
    TimerSimple timer;
    
    uint8_t pinAudioD=255;//255 - неправильно или не задан
    uint8_t claps=0;//количество хлопков в завершенной серии

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
    ClapsCounter(uint8_t new_pinAudioD);
    virtual ~ClapsCounter(){};
    void Update();
    uint8_t GetClaps();//Возвращает значение, если подсчет окончен. Иначе 0
    void ResetClaps();//Сбрасывает последний подсчет в 0
    void HardReset();//Сбрасывает и подсчет, и состяние
    virtual void Announce(){}; // Вызывается в Update. При наследовании с интерфейсом издателя, переопределить. 
};
//----------------
#endif

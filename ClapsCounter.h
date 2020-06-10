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
    enum CounterState{
      OFF,      //Счет не начат
      WAIT,     //Глухое ожидание после хлопка
      SILENCE,  //Выжидание в тишине между хлопками 
      LISTEN,   //Ожидание нового хлопка
      ERR       //Работа невозможна
    };
    CounterState state=CounterState::OFF;

    struct TimeConstants{
      const unsigned long WAIT=100;     //Глухое ожидание после хлопка
      const unsigned long SILENCE=100;  //Выжидание в тишине между хлопками
      const unsigned long LISTEN=300;   //Ожидание нового хлопка
      const unsigned long END=500;      //Время нереагирования после окончания серии
    };
    TimeConstants timeconsts;
    
    TimerSimple timer;
    
    uint8_t pinAudioD=255;//255 - неправильно или не задан
    uint8_t claps=0;//количество хлопков в завершенной серии
    
 public:  
    ClapsCounter(uint8_t new_pinAudioD);
    void Update();
    uint8_t GetClaps();//Возвращает значение, если подсчет окончен. Иначе 0
    void ResetClaps();//Сбрасывает последний подсчет
};
//----------------
#endif

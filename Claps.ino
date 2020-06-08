class TimerSimple{
  private:
    bool IsOn=false;//true если еще работает, false если выкл или закончился  
    unsigned long ringTime=0;  
  public:
    void Start(unsigned long duration){
      if(duration>0){
        this->ringTime=millis()+duration;
        IsOn=true;
      }
    }
    bool Check(){      
      if(IsOn){
        IsOn=!((this->ringTime <= millis())?true:false);
      }
      return IsOn;      
    }
};
//----------------

byte pinAudioD=2;
byte pinLowLight=3;
byte pinHightLight=4;

bool ClapsOn=true;

bool onLowLight=0;
bool onHightLight=0;
byte claps=0;

//int voiseLevel=0; //voiseLevel=analogRead(A0);

TimerSimple Timer;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinAudioD,INPUT);  
  pinMode(pinLowLight,OUTPUT);
  pinMode(pinHightLight,OUTPUT);
  
  digitalWrite(pinLowLight,onLowLight);
  digitalWrite(pinHightLight,onHightLight);
}

void loop() {
  if(ClapsOn != (analogRead(A1)>600?true:false)){ //ClapsOn - вкл ли управление хлопками. Нужно ли переключить?
    ClapsOn=!ClapsOn;
    if(ClapsOn){
      digitalWrite(pinLowLight,onLowLight);
      digitalWrite(pinHightLight,onHightLight);
    }else{
      digitalWrite(pinLowLight,HIGH);
      digitalWrite(pinHightLight,HIGH);
    }
  }
  
  if(ClapsOn){
    if(digitalRead(pinAudioD)){     Serial.println("Clap 1");
      claps=1;
      Timer.Start(200);
      while(Timer.Check());    
      Timer.Start(300);
      while(Timer.Check()){    
        if(digitalRead(pinAudioD)){ 
          claps++;                  Serial.print("Claps ");Serial.println(claps);
          Timer.Start(200);
          while(Timer.Check());
          Timer.Start(300);
        }
      }
      if(claps>1 && claps<=3){      Serial.println("In if");
        if(claps==2){
          onLowLight=!onLowLight;
          digitalWrite(pinLowLight,onLowLight);
        }else if(claps==3){
          onHightLight=!onHightLight;
          digitalWrite(pinHightLight,onHightLight);
        }         
        Timer.Start(500);
        while(Timer.Check());      Serial.print(onLowLight);Serial.print(" ");Serial.println(onHightLight);   
      }
    }
  }
}

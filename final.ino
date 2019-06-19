//원본 수정 금지
//header file zone
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

//global variable zone
int sound=22;//sound variable declaration
double LastTime;
double ThisTime;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM;
#define UpperThreshold 700
#define LowerThreshold 699

int apple(){
  ThisTime=millis();
  int value=analogRead(A0);
  int y=60-(value/16);
  
  if(value>UpperThreshold) //value>UpperThreshold
  {
    if(BeatComplete)
    {
      BPM=ThisTime-LastTime;
      BPM=int(60/(float(BPM)/1000));
      BPMTiming=false;
      BeatComplete=false;
      //tone(4,1000,250); 
    }
    if(BPMTiming==false)
    {
      LastTime=millis();
      BPMTiming=true;
    }
  }
  if((value<LowerThreshold)&(BPMTiming))
    BeatComplete=true;

    return BPM;
}

void useOled() {//using oled function
  u8g.firstPage();
  do{
    u8g.setPrintPos(1, 15);//set where = (0. 35)
    if(sound==0){
       u8g.print("senser ERROR!");
    }
    
    u8g.setPrintPos(1, 35);//set where = (0. 35)
    u8g.print("sound: ");
    u8g.print(sound);//oled <- ("%d", sound);

    u8g.setPrintPos(1, 55);//set where = (0. 55)
    u8g.print("BPM: ");
    u8g.print(BPM);
  }while(u8g.nextPage());
}

/*
void alarm(){
  if(
}
*/

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);//use 2pin(sound sensor)
  u8g.setFont(u8g_font_unifont);//u8g font select
}



void loop() {
  apple();
  //alarm();
  useOled();
  //delay(10);

  sound=analogRead(A0);

 
  //Serial.println(sound);
  Serial.println(BPM);
}

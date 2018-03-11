#include <IRremote.h>

const int volumeMinusPin = 8;  
const int volumePlusPin  = 9;   
const int mutePin        = 10;
const int prevTrackPin   = 11;   
const int nextTrackPin   = 12;   

const int standartDelay = 100;

#define volumeMinus 0x83B19366  
#define volumePlus  0x68733A46 
#define mute        0x2340B922 
#define trackPrev   0x189D7928 
#define trackNext   0x5F12E8C4


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(3, OUTPUT);
  pinMode(volumePlusPin, INPUT);
  pinMode(volumeMinusPin, INPUT);
}
IRsend irsend;      //3 Pin

void loop() {     
    if(digitalRead(volumePlusPin) == HIGH){
      irsend.sendRC5(volumePlus, 32);
      delay(standartDelay);  
    }
    else if(digitalRead(volumeMinusPin) == HIGH){
     irsend.sendRC5(volumeMinus, 32);
     delay(standartDelay);
    }
    /*else if(digitalRead(mutePin) == HIGH){
     irsend.sendRC5(mute, 32);
     delay(standartDelay);
    }
    else if(digitalRead(prevTrackPin) == HIGH){
     irsend.sendRC5(trackPrev, 32);
     delay(standartDelay);
    }
    else if(digitalRead(nextTrackPin) == HIGH){
     irsend.sendRC5(trackNext, 32);
     delay(standartDelay);
    }*/
}





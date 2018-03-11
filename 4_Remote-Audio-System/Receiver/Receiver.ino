#include <Keyboard.h>
#include <IRremote.h>

const int pausePin       = 2;   
const int receiverPin    = 7;
const int standartDelay = 50;

#define volumeMinus 0x83B19366  
#define volumePlus  0x68733A46 
#define mute        0x2340B922 
#define trackPrev   0x189D7928 
#define trackNext   0x5F12E8C4

IRrecv irrecv(receiverPin);
decode_results results;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode( pausePin, INPUT); 
  Keyboard.begin();
  irrecv.enableIRIn();
}

void loop() {
  if(digitalRead(pausePin) == LOW){  
   if (irrecv.decode(&results)) {
    if(results.value == volumePlus){
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press('=');
       delay(standartDelay / 2);
       Keyboard.releaseAll();
      }
      else if(results.value == volumeMinus){
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press('-');
       delay(standartDelay / 2);
       Keyboard.releaseAll();
      }
      else if(results.value == trackNext){
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press(']');
       delay(standartDelay * 5);
       Keyboard.releaseAll();
      }
      else if(results.value == trackPrev){
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press('[');
       delay(standartDelay * 5);
       Keyboard.releaseAll();
      }
      else if(results.value == mute){
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.press('\\');
       delay(standartDelay);
       Keyboard.releaseAll();
      }
    irrecv.resume();
   }
  }
  else{
    Keyboard.end();
  }
}

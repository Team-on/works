#include <IRremote.h>
int RECEIVE_PIN = 7;
IRrecv irrecv(RECEIVE_PIN);
decode_results results;
 
void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
}
 
void loop() {
    if (irrecv.decode(&results)) {
        Serial.println(results.decode_type);
        Serial.println(results.bits);
        for(int i = 0; i < results.rawlen; i++){
          Serial.print(results.rawbuf[i]);
          Serial.print(" ");
        }
          Serial.println();
        Serial.println(results.rawlen);
        Serial.print("0x");
        Serial.println(results.value, HEX);
        delay(50);
        irrecv.resume();// Receive the next value
    }
}

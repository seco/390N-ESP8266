#include "pitches.h"
#define PIN_BUZZER 13 // the digital pin the Buzzer is attached to

void play_note(int freq){
  if (freq > 0){
    analogWrite(PIN_BUZZER, 512);
    analogWriteFreq(freq);
    } else {
      analogWrite(PIN_BUZZER, 0);
    }
}

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  play_note(NOTE_G3);
}

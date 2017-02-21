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

  play_note(NOTE_B13);
  delay(300);
  play_note(NOTE_B13);
  delay(300);
  play_note(NOTE_B13);
  delay(300);
  play_note(NOTE_B13);
  delay(300);

  play_note(NOTE_B9);
  delay(550);
 
  play_note(NOTE_B9);
  delay(550);
  play_note(NOTE_B11);
  delay(550);

  play_note(NOTE_B13);
  delay(200);
  play_note(NOTE_B11);
  delay(200);
  play_note(NOTE_B13);
  delay(500);
  
  




  
}

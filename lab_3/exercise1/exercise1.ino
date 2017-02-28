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

  // intro
  play_note(NOTE_E7);
  delay(110);
  play_note(NOTE_E7);
  delay(220);
  play_note(NOTE_E7);
  delay(220);
  play_note(NOTE_C7);
  delay(110);
  play_note(NOTE_E7);
  delay(220);
  play_note(NOTE_G7);
  delay(440);
  play_note(NOTE_G6);
  delay(440);

  // riff
  play_note(NOTE_C7);
  delay(330);
  play_note(NOTE_G6);
  delay(330);
  play_note(NOTE_E6);
  delay(330);
  play_note(NOTE_A6);
  delay(220);
  play_note(NOTE_B6);
  delay(220);
  play_note(NOTE_AS6);
  delay(110);
  play_note(NOTE_A6);
  delay(110);

  // riff
  play_note(NOTE_G6);
  delay(110);
  play_note(NOTE_E7);
  delay(110);
  play_note(NOTE_G7);
  delay(110);
  play_note(NOTE_A7);
  delay(220);
  play_note(NOTE_F7);
  delay(110);
  play_note(NOTE_G7);
  delay(220);
  play_note(NOTE_E7);
  delay(220);
  play_note(NOTE_C7);
  delay(110);
  play_note(NOTE_D7);
  delay(110);
  play_note(NOTE_B6);
  delay(330);

  // riff
  play_note(NOTE_C7);
  delay(330);
  play_note(NOTE_G6);
  delay(330);
  play_note(NOTE_E6);
  delay(220);
  play_note(NOTE_A6);
  delay(220);
  play_note(NOTE_B6);
  delay(220);
  play_note(NOTE_AS6);
  delay(110);
  play_note(NOTE_A6);
  delay(220);

  // riff
  play_note(NOTE_G6);
  delay(110);
  play_note(NOTE_E7);
  delay(110);
  play_note(NOTE_G7);
  delay(110);
  play_note(NOTE_A7);
  delay(220);
  play_note(NOTE_F7);
  delay(110);
  play_note(NOTE_G7);
  delay(220);
  play_note(NOTE_E7);
  delay(220);
  play_note(NOTE_C7);
  delay(110);
  play_note(NOTE_D7);
  delay(110);
  play_note(NOTE_B6);
  delay(330);
  

  
}

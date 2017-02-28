#include "pitches.h" // contains frequencies for notes
#define PIN_BUTTON 0 // the button
#define PIN_BUZZER 13 // the digital pin the Buzzer is attached to

bool stop = false; // button pressed

void play_note(int freq){
    if (freq > 0 && !stop){
      analogWrite(PIN_BUZZER, 512);
      analogWriteFreq(freq);
    } else {
      analogWrite(PIN_BUZZER, 0);
    }
}

void stopMusic(){
  stop = !stop;
  play_note(0);
}

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), stopMusic, RISING);
}

void loop() {

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

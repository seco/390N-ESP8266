// Lab 2 Submission
// Team 14
// Pranjal Singhal, Humad Syed, Daoxu Ye

#include <Adafruit_NeoPixel.h>

#define PIN_LED 15
#define PIN_BUZZER 13
#define POT A0 //analog input for potentiometer
int analogValue = 0; //variable to hold the analog value
volatile int delaytime = 200; // milliseconds

// create pixel object, 1 pixel connected at PIN_LED
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  // turn off buzzer
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, 0);
  // initialize LED
  pixel.begin();
  // lower brightess (default is 256)
  pixel.setBrightness(48);
  pixel.show();
}

void loop() { 
  analogValue = analogRead(POT);
  analogValue = analogValue/4;
  pixel.show();
  if(analogValue > 255){
    analogValue = 255;
  }
  if(analogValue < 1){
    analogValue = 1;
  }
  if (analogValue > 166){
    pixel.setPixelColor(0, pixel.Color(analogValue, analogValue/200, analogValue/200));
  } else if (analogValue < 83){
    pixel.setPixelColor(0, pixel.Color(analogValue/200, analogValue/2, 255/analogValue));
  } else {
    pixel.setPixelColor(0, pixel.Color(analogValue/200, analogValue*2, analogValue/200));
  }
  delay(10);
}

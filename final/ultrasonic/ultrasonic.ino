// TODO: 
// 1. Define output pins to send signals to other board
// 2. Define threshold

#include <Wire.h>

// Front ultrasonic
#define TRIGGERFRONT  5
#define ECHOFRONT     4

// Back ultrasonic
#define TRIGGERBACK   12
#define ECHOBACK     14

// Distance from front object
long distanceFront;

// Distance from back object
long distanceBack = 0;

// Get distance from the front of the car to the object in front
int getFrontDistance(){
  long duration;
  long distance;

  Serial.println("Getting front distance");

  digitalWrite(TRIGGERFRONT, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGERFRONT, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGERFRONT, LOW);
  duration = pulseIn(ECHOFRONT, HIGH);

  Serial.print("Duration: ");
  Serial.println(duration);
    
  distance = (duration / 2) / 29.1;

  Serial.print(distanceFront);
  Serial.println(" Centimeters from front");

  return distance;
}

// Get the distance from the back of the car to the object in the back
int getBackDistance(){
  long duration;
  long distance;

  Serial.println("Getting back distance");

  digitalWrite(TRIGGERBACK, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGERBACK, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGERBACK, LOW);
  duration = pulseIn(ECHOBACK, HIGH);

  Serial.print("Duration: ");
  Serial.println(duration);
    
  distance = (duration / 2) / 29.1;

  Serial.print(distanceBack);
  Serial.println(" Centimeters from back");

  return distance;
}

void setup() {
  Serial.begin (9600);
  pinMode(TRIGGERFRONT, OUTPUT);
  pinMode(ECHOFRONT, INPUT);
  pinMode(TRIGGERBACK, OUTPUT);
  pinMode(ECHOBACK, INPUT);
  
  Wire.begin();
}

void loop() {
  distanceFront = getFrontDistance();
  //distanceBack = getBackDistance();

  // Send data to slave
  Wire.beginTransmission(8);
  Wire.write(distanceFront);
  Wire.write(distanceBack);
  Wire.endTransmission();
  
  delay(100); // added for easy serial readability; remove later
}


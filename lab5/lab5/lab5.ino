#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define different pins
#define PIN_BUTTON 0
#define REED_SWITCH A0
#define LED 2
#define PIN_BUZZER 13

// Flags for status
boolean doorOpen = false;
boolean systemOn = true;

// alarm can be in 3 states:
// 0: Running
// 1: Triggered
// 2: Turned off by user
int alarm = 0;
long previousMillis = 0; // needed to track time for repeated buzzer & LED

// Blynk auth
char auth[] = "af0f68df444b43edbcd37bc7147ab608";

// Update these to whatever Wifi your phone is connected to
char ssid[] = "Somnus";
char password[] = "00000000";

// V0 -> Alarm status
// V1 -> Alarm button
// V2 -> System status
// V3 -> System button
// V6 -> Door status

// If user turns off the alarm
BLYNK_WRITE(V1){
  alarm = 2;
  turnOffAlarm();
}

// User turns off the system
BLYNK_WRITE(V2){
  systemOn = false;
  alarm = 2;
  turnOffAlarm();
}

// User turns on the system
BLYNK_WRITE(V5){
  systemOn = true;
  alarm = 0;
  turnOffAlarm();
}

// Generates a sound and blinks the LED every second
void soundAlarm(){
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000){

    previousMillis = currentMillis;

    if (digitalRead(LED) == LOW){
      analogWrite(PIN_BUZZER, 0);
      digitalWrite(LED, HIGH);
    } else {
      analogWrite(PIN_BUZZER, 256);
      digitalWrite(LED, LOW);  
    }
  }
}

// Turns off the LED and the buzzer
void turnOffAlarm(){
  digitalWrite(LED, HIGH);
  analogWrite(PIN_BUZZER, 0);
}

// Update status of alarm and system on Blynk
void sendStatusToBlynk(){
  String status;

  // Alarm status
  if (alarm == 0){
    status = "RUNNING";
  } else if (alarm == 1){
    status = "TRIGGERED";
  } else {
    status = "OFF";  
  }
  Blynk.virtualWrite(V0, status);
  
  // System status
  if (systemOn){
    status = "ON";
  } else {
    status = "OFF";
  }
  Blynk.virtualWrite(V3, status);
  
  // Door status
  if (doorOpen){
    status = "DOOR OPEN";
  } else {
    status = "DOOR CLOSED";
  }
  Blynk.virtualWrite(V6, status);
}


void setup() {
  Serial.begin(9600);

  // Set up pins
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  analogWrite(PIN_BUZZER, 0); // set the buzzer to be off
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), turnOffAlarm, CHANGE);
  
  // Blynk initialization
  Blynk.begin(auth, ssid, password);
  Blynk.virtualWrite(V0, "RUNNING");
  Blynk.virtualWrite(V3, "ON");
}

void loop() {
  Blynk.run();

  // Update status of door
  doorOpen = analogRead(A0) > 1000;

  // Update status on Blynk
  sendStatusToBlynk();

  // if alarm has been triggered
  if (alarm == 1){
    soundAlarm();  
  }

  if (systemOn){
    // if door opens and alarm was running
    if (doorOpen && alarm == 0){
      Serial.println("Door was opened");
      alarm = 1;
      Blynk.notify("Someone opened your door!");
      soundAlarm();
    }

    // if door is closed and alarm was turned off by the user
    if (!doorOpen && alarm == 2){
      alarm = 0;
    }
  }
}

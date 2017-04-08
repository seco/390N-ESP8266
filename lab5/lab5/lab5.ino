#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Temboo.h>
#include "TembooAccount.h"
#include <TimeLib.h>
#include <BlynkSimpleEsp8266.h>
WiFiClient client;

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
char ssid[] = "Catherine";
char password[] = "00000000";

// V0 -> Alarm status
// V1 -> Alarm button
// V2 -> System status
// V3 -> System button
// V6 -> Door status

// If user turns off the alarm
BLYNK_WRITE(V1){
  turnOffAlarm();
  alarm = 2;
  // updateSpreadsheet("Alarm turned off");
}

// User turns off the system
BLYNK_WRITE(V2){
  systemOn = false;
  alarm = 2;
  turnOffAlarm();
  //updateSpreadsheet("System turned off");
}

// User turns on the system
BLYNK_WRITE(V5){
  //updateSpreadsheet("System turned on");
  systemOn = true;
  alarm = 0;
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
  //updateSpreadsheet("Alarm turned off");
  digitalWrite(LED, HIGH);
  analogWrite(PIN_BUZZER, 0);
  alarm = 2;
}

// Update status of alarm and system on Blynk
void sendStatusToBlynk(){

  // Alarm status
  if (alarm == 0){
    Blynk.virtualWrite(V0, "RUNNING");
  } else if (alarm == 1){
    Blynk.virtualWrite(V0, "TRIGGERED");
  } else {
    Blynk.virtualWrite(V0, "OFF");
  }
  
  // System status
  if (systemOn){
    Blynk.virtualWrite(V3, "ON");
  } else {
    Blynk.virtualWrite(V3, "OFF");
  }
  
  // Door status
  if (doorOpen){
    Blynk.virtualWrite(V6, "DOOR OPEN");
  } else {
    Blynk.virtualWrite(V6, "DOOR CLOSED");
  }
}

void updateSpreadsheet(String data){
 TembooChoreo AppendValuesChoreo(client);
 Serial.println("Beginning choreo");

  // Invoke the Temboo client
  AppendValuesChoreo.begin();

  // Set Temboo account credentials
  AppendValuesChoreo.setAccountName(TEMBOO_ACCOUNT);
  AppendValuesChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  AppendValuesChoreo.setAppKey(TEMBOO_APP_KEY);

  Serial.println("Credentials set");

  time_t t = now();
  String timeData = (String) month(t) + 
                    "-" + 
                    (String) day(t) + 
                    "-" + 
                    (String) year(t) + 
                    " " + 
                    (String) hour(t) + 
                    ":" + 
                    (String) minute(t);

  String values = "[[\"" + timeData + "\", \"" + data + "\"]]";

  Serial.println("values: " + values);
  
  // Set Choreo inputs
  AppendValuesChoreo.addInput("RefreshToken", REFRESH_TOKEN);
  AppendValuesChoreo.addInput("ClientSecret", CLIENT_SECRET);
  AppendValuesChoreo.addInput("Values", values);
  AppendValuesChoreo.addInput("ClientID", CLIENT_ID);
  AppendValuesChoreo.addInput("SpreadsheetID", SPREADSHEET_ID);
  
  // Identify the Choreo to run
  AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");

  Serial.println("Choreo values set");
  
  // Run the Choreo;
  unsigned int returnCode = AppendValuesChoreo.run();

  Serial.println("Choreo ran");

  if (returnCode == 0){
    Serial.println("Sucess!");
  } else {
    while (AppendValuesChoreo.available()){
      char c = AppendValuesChoreo.read();
      Serial.print(c);
    }    
  }
  
  AppendValuesChoreo.close();
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

  Serial.println("Setup complete");
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
      //updateSpreadsheet("Alarm triggered");
      alarm = 1;
      Blynk.notify("Someone opened your door!");
      soundAlarm();
    }

    // if door is closed and alarm was turned off by the user
    if (!doorOpen && alarm == 2){
      //updateSpreadsheet("Door closed, alarm running");
      alarm = 0;
    }
  }
}

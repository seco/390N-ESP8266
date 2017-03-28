#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
#include <Temboo.h>
#include "TembooAccount.h"
WiFiClient client;

#define BLYNK_PRINT Serial

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed
char auth[] = "af0f68df444b43edbcd37bc7147ab608";
char ssid[] = "CS190IOT";
char pass[] = "12345678";

void setup() {
 Serial.begin(115200);
 Serial.println();
 WiFi.begin(ssid, pass); //connecting to the router
 Blynk.begin(auth, ssid, pass);
 Serial.print("Connecting");
 while (WiFi.status() != WL_CONNECTED){
   delay(500);
   Serial.print(".");
 }
 Serial.println();
 Serial.print("Connected, IP address: ");
 Serial.println(WiFi.localIP());
}

void loop() {

  Blynk.run();
  if (calls <= maxCalls) {
    Serial.println("Running GetWeatherByAddress - Run #" + String(calls++));
    
    TembooChoreo GetWeatherByAddressChoreo(client);

    // Invoke the Temboo client
    GetWeatherByAddressChoreo.begin();

    // Set Temboo account credentials
    GetWeatherByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetWeatherByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetWeatherByAddressChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    GetWeatherByAddressChoreo.addInput("Address", "Amherst, MA");
    
    // Identify the Choreo to run
    GetWeatherByAddressChoreo.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");
    
    // Run the Choreo; when results are available, print them to serial
    GetWeatherByAddressChoreo.run();
    
    while(GetWeatherByAddressChoreo.available()) {
      char c = GetWeatherByAddressChoreo.read();
      Serial.print(c);
    }
    GetWeatherByAddressChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between GetWeatherByAddress calls
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "html_homepage.h"

#define PIN_BUTTON   0
#define PIN_LED     15
#define PIN_BUZZER  13


// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);

int r, g, b;

void on_homepage(){
  Serial.println("On homepage");
  String html = FPSTR(html_homepage);
  server.send(200, "text/html", html);
}

void on_color_change(){
  Serial.println("On color change");
  if (server.hasArg("r") && server.hasArg("g") && server.hasArg("b")){
    r = server.arg("r").toInt();
    g = server.arg("g").toInt();
    b = server.arg("b").toInt();
  }
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
  server.send(200, "text/html", "<h1>Received color change</h1>");
}

void on_js(){
  Serial.println("On js");
  String json = "{";
  json += "\"light\":";
  json += (analogRead(A0));
  json += ", \"button\":";
  json += (1-digitalRead(PIN_BUTTON));
  json += ", \"color\": \"(";
  json += r;
  json += ", ";
  json += g;
  json += ", ";
  json += b;
  json += ")\"}";
  Serial.println(json);
  server.send(200, "text/html", json);
}

void setup() {
  Serial.begin(115200);
  pixel.begin();
  pixel.show();

  WiFi.mode(WIFI_AP);
  String ap_name = "Group 14";
  WiFi.softAP(ap_name.c_str());

  server.on("/", on_homepage);
  server.on("/color_change", on_color_change);
  server.on("/js", on_js);

  server.begin();
}

void loop() {
 server.handleClient();
}


#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

#define PIN_LED   15

ESP8266WebServer server(80);

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

int r, g, b;

void on_homepage() {
  String html = FPSTR(html_homepage);
  Serial.println("Rendering home page");
  server.send(200, "text/html", html);
}

void on_color_change(){
  Serial.println("Request received on /color_change");
  if (server.hasArg("r") && server.hasArg("g") && server.hasArg("b")){
    Serial.println("Server has arguments");
    r = server.arg("r").toInt();
    g = server.arg("g").toInt();
    b = server.arg("b").toInt();
    pixel.setPixelColor(0, pixel.Color(r, g, b));
  }
  
  server.send(200, "html", "<h1>Received request</h1>");
}

void send_color_change(){
  Serial.println("Sending color change");
  String jsonResponse = "{light: (";
  jsonResponse += "" + r;
  jsonResponse += ", " + g;
  jsonResponse += ", " + b;
  jsonResponse += ")}";
  server.send(200, "text/json", jsonResponse);
}

void setup(void){
  pixel.begin();
  pixel.show();
  
  WiFi.mode(WIFI_AP);
  String name = "Group 14";
  WiFi.softAP(name.c_str());

  server.on("/", on_homepage);
  server.on("/color_change", on_color_change);
  server.on("/js", send_color_change);
  server.begin();
}
 
void loop(void){
  server.handleClient();
}


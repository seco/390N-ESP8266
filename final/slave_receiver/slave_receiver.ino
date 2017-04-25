#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(receiveData);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
}

void receiveData(int num){
  Serial.println("Front distance: " + Wire.read());
  Serial.println("Back distance: " + Wire.read());
}

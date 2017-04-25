// V0 = Accelerate Button
// V1 = Reverse Button
// V2/V3 = Joystick (V2 is Vertical)

// Blynk auth
char auth[] = "af0f68df444b43edbcd37bc7147ab608";

// User is pressing Accelerate button
BLYNK_WRITE(V0){
  // check front ultrasound sensor
  // accelerate if clear
}

// User is pressing Reverse button
BLYNK_WRITE(V1){
  // check back ultrasound sensor
  // reverse if clear
}

// User is using the joystick
BLYNK_WRITE(V2){
  // read value
  // figure out direction
  // figure out degree of rotation
  // rotate  
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

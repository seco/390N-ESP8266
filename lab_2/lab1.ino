#define LED 2

void setup() {
  // put your setup code here, to run once:
  pinMode (LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int x = 0; x < 4; x++){
    digitalWrite(LED, HIGH);    //blinks 4 times
    delay(10);                  //delays for a moment
    digitalWrite(LED, LOW);
    delay(500);                 //waits half a second
  }
  digitalWrite(LED, HIGH);      //turns on the LED for the 5th time
  for (int x = 4; x > -1; x--){
    int analogValue = 255*x;
    analogWrite(analogValue);
	delay(1000)
  }
}
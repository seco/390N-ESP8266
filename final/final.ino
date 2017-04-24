#define TRIGGERFRONT 5
#define ECHOFRONT 4
// define triggerback and echoback

// Distance from front object
long distanceFront;

// Distance from back object
long distanceBack;

int getFrontDistance(){
  long duration;

  Serial.println("Running...");

  digitalWrite(TRIGGERFRONT, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGERFRONT, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGERFRONT, LOW);
  duration = pulseIn(ECHOFRONT, HIGH);

  Serial.print("Duration: ");
  Serial.println(duration);
    
  distanceFront = (duration / 2) / 29.1;

  Serial.print(distanceFront);
  Serial.println(" Centimeters");
}

int getBackDistance(){
  return 0;
}

void setup() {
  Serial.begin (9600);
  pinMode(TRIGGERFRONT, OUTPUT);
  pinMode(ECHOFRONT, INPUT);
}

void loop() {
  distanceFront = getFrontDistance();
  distanceBack = getBackDistance();
  delay(1000); // added for easy serial readability; remove later
}

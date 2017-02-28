#include <Ticker.h>
#include <EEPROM.h>
#define PIN_BUZZER 13 // the digital pin the Buzzer is attached to

PROGMEM const int freqs[] = {31, 49, 78, 123, 196, 311, 494, 784, 1245, 1976, 3136,
4978};

Ticker secondTick;

volatile int watchdogCount = 0;
volatile int freqIdx = 0; //the index that will store the last frequency before it restarts

int EEPROM_Addr = 42;

//The Watchdog Interrupt Service Routine (ISR)
void ISRwatchdog() {
  watchdogCount++;
  //The watchdog will be waken up when the couter reaches 4
  if (watchdogCount == 4) {
    ESP.restart(); //restarting the board
  }
}

void setup() {
  EEPROM.begin(4096);
  Serial.begin(115200);
  secondTick.attach(1, ISRwatchdog); //registering the watchdog ISR
  pinMode(PIN_BUZZER, OUTPUT);

  int prevFreq = EEPROM.read(EEPROM_Addr); // read previous frequency
  if (prevFreq != 255){
    Serial.println("Previous frequency found : ");
    Serial.println(prevFreq);
    analogWrite(PIN_BUZZER, 256);
    analogWriteFreq(prevFreq);
    delay(1000);
  }
}

void loop() {
  Serial.print("Watchdog counter = ");
  Serial.println(watchdogCount);
  watchdogCount = 0;

  int freq = freqs[random(0, 11)];
  Serial.print("Frequency: ");
  Serial.println(freq);
  Serial.println("Saving to EEPROM");
  EEPROM.write(EEPROM_Addr, freq);
  EEPROM.commit();
  
  // generating 50% PWM
  analogWrite(PIN_BUZZER, 256);
  analogWriteFreq(freq);
  
  //depending on the value of delay, the program may wake up the watchdog
  int delayTime = random(1, 5) * 1000;
  Serial.print("Delay time: ");
  Serial.println(delayTime);
  delay(delayTime);
}

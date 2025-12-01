// EX6_1

#include <SPI.h>
#define SS_PIN 5

void setup() {
  Serial.begin(9600);

  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);

  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  Serial.println("MKR1010 SPI Master Ready");
}

void loop() {
  uint8_t data = 0x55; 

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(data);
  digitalWrite(SS_PIN, HIGH);

  Serial.println("Sent: 0x55");
  delay(1000);
}

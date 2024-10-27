
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  // Check if the nRF24L01 module is connected
  if (radio.isChipConnected()) {
    Serial.println("nRF24L01 is connected successfully!");
  } else {
    Serial.println("ERROR: nRF24L01 is NOT connected. Please check wiring.");
    while (true)
      ;  // Stop further execution if the module is not connected
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(119);
  radio.setDataRate(RF24_2MBPS); 
  radio.stopListening();
  delay(1000);
}

void loop() {
  const char text[] = "Hello World";
  bool success = radio.write(&text, sizeof(text));
  Serial.println(success);
  if (success) {
    Serial.println("Data Sent Successfully");
  } else {
    Serial.println("Data Transmission Failed");
  }

  delay(100);
}
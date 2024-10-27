#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();

  // Check if the nRF24L01 module is connected
  if (radio.isChipConnected()) {
    Serial.println("nRF24L01 is connected successfully!");
  } else {
    Serial.println("ERROR: nRF24L01 is NOT connected. Please check wiring.");
    while (true); // Stop further execution if the module is not connected
  }

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(119);  // Example of setting a higher channel
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  } else {
    Serial.println("Not Available");
  }

  delay(200); // Delay to reduce serial output frequency
}

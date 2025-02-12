#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
int count = 0;


void setup() {
    Serial.begin(115200);
    SerialBT.begin("LORD_Krishna"); // Set Bluetooth Name
    Serial.println("Bluetooth Started! Ready to Pair.");
}


// roll no. 2, 6, 36
void loop() {
  
  if (SerialBT.available()) {
     count+=1;
      char incomingChar = SerialBT.read();

      Serial.write(incomingChar);
      SerialBT.print(count);
      SerialBT.println(": Message from esp32. Hi drink water."); // Echo received data to Serial Monitor

  }
  delay(100);
  
}
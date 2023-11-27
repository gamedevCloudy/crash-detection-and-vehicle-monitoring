#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(2000);
  scanI2CDevices();
}

void loop() {
}

void scanI2CDevices() {
  byte error, address;
  int devices = 0;

  Serial.println("Scanning I2C devices...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println(" !");
      devices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (devices == 0) {
    Serial.println("No I2C devices found.\n");
  }
  else {
    Serial.println("Scan complete.\n");
  }
}

#include <Arduino.h>
#include <i2c_driver.h>
#include <i2c_driver_wire.h>

#define SECONDARY_ADDR 8

void kbReadBytes();

void setupI2c(bool isPrimary) {
  if (isPrimary) {
    Wire.setClock(100000);
    println("Primary i2c initialized.");
    Wire.begin();


  } else {
    Wire.begin(SECONDARY_ADDR);   // join i2c bus with address #slave
    Wire.onRequest(kbReadBytes);  // register event
  }
}

void kbReadBytes() {
  //Serial.println("req");  // as expected by master;
  //readKeys(keyBufSize, keyBuffer);
  Wire.write(keyBuffer, keyBufSize);
  initKeyBuf();  //clear buff after sending
}

bool readSecondary(int keyBufSize, byte* keyBuffer) {
  byte idx = 0;
  Wire.requestFrom(SECONDARY_ADDR, keyBufSize);
  while (Wire.available()) {  // peripheral may send less than requested
    char c = Wire.read();     // receive a byte as character
    keyBuffer[idx++] = c;     // receive a byte as character
  }


  for (int i = 0; i < keyBufSize; i++) {
    if (keyBuffer[i++] != 0) {
      return true;
    }
  }
  return false;
}
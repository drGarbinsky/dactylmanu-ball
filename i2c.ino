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
  uint8_t data[sizeof(keyBuffer) + sizeof(ballMotionBuffer)];
  memcpy(data, &keyBuffer, sizeof(keyBuffer));
  memcpy(data + sizeof(keyBuffer), &ballMotionBuffer, sizeof(ballMotionBuffer));

  Wire.write(data, sizeof(data));
  initKeyBuf();  //clear buff after sending
  initBallBuf();
}

bool readSecondary() {
  byte idx = 0;
  Wire.requestFrom(SECONDARY_ADDR, keyBufSize + 4);
  while (Wire.available() && idx < keyBufSize) {  // peripheral may send less than requested
    char c = Wire.read();                         // receive a byte as character
    keyBuffer[idx++] = c;                         // receive a byte as character
  }
  idx = 0;


  while (Wire.available() && idx < 2) {
    ballMotionBuffer[idx++] = Wire.read();
  }

  

  for (int i = 0; i < keyBufSize; i++) {
    if (keyBuffer[i++] != 0) {
      return true;
    }
  }

  for (int i = 0; i < ballBufSize; i++) {
    if (ballMotionBuffer[i++] != 0) {
      return true;
    }
  }

  return false;
}
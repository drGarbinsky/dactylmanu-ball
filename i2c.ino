#include <Arduino.h>
#include <i2c_driver.h>
#include <i2c_driver_Wire.h>

#define SECONDARY_ADDR 8

I2CMaster& master = Master;
void kbReadBytes();

void setupI2c(bool isPrimary) {
  if (isPrimary) {
    Wire1.setClock(100000);
    println("Primary i2c initialized.");
    Wire1.begin();


  } else {
    Wire1.begin(SECONDARY_ADDR);   // join i2c bus with address #slave
    Wire1.onRequest(kbReadBytes);  // register event
  }
}

void kbReadBytes() {
  //flashLed();
  uint8_t data[sizeof(keyBuffer) + sizeof(ballMotionBuffer)];
  memcpy(data, &keyBuffer, sizeof(keyBuffer));
  memcpy(data + sizeof(keyBuffer), &ballMotionBuffer, sizeof(ballMotionBuffer));

  Wire1.write(data, sizeof(data));
  initKeyBuf();  //clear buff after sending
  initBallBuf();
  resetWatchdog();
}

bool readSecondary() {
  
  byte idx = 0;
  Wire1.requestFrom(SECONDARY_ADDR, keyBufSize + 4);
  while (Wire1.available() && idx < keyBufSize) {  // peripheral may send less than requested
    char c = Wire1.read();                         // receive a byte as character
    keyBuffer[idx++] = c;                         // receive a byte as character
  }
  idx = 0;

  while (Wire1.available() && idx < 2) {
    ballMotionBuffer[idx++] = Wire1.read();
  }

  if (idx > 0) {
    resetWatchdog();
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
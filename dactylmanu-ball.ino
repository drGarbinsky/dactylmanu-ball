const int isRightPin = 7;
const int isRightPinOut = 8;
bool isPrimary = false;
bool LOG = true;
bool isRightHalf = false;
unsigned long lastTS = 0;
unsigned long curTime = micros();
const int keyBufSize = 8;
uint8_t keyBuffer[keyBufSize];
bool keysSent = true;
void setup() {
  Serial.begin(57600);
  Serial.println("Dactyl Manuball 2.0 starting...");
  isRightHalf = isRight();
  if (isRightHalf) {
    println("Right Side");
  } else {
    println("Left Side");
  }

 
  //isPrimary = !isRightHalf;
  if (!bitRead(USB1_PORTSC1, 7)) {
    //usb connected
    isPrimary = true;
    println("Is Primary");
  } else {
    //usb disconnected
    isPrimary = false;
    println("Is Secondary");
  }


  initKeyBuf();
  setupBall(!isRightHalf);
  setupKeys();
  setupI2c(isPrimary);
  Serial.println("Keyboad ready");
}
void loop() {
  curTime = micros();
  unsigned long elapsed = curTime - lastTS;

  if (elapsed >= 500)  // polling interval : more than > 0.5 ms.
  {

    if (isPrimary) {

      readBall();
      if (readKeys(keyBufSize, keyBuffer)) {

        processKeyStates(isRightHalf, keyBufSize, keyBuffer);
        //printBytes(keyBuffer, keyBufSize);
        initKeyBuf();
      }
      if (readSecondary(keyBufSize, keyBuffer)) {

        //printBytes(keyBuffer, keyBufSize);
        processKeyStates(!isRightHalf, keyBufSize, keyBuffer);
      }
    } else {


      readKeys(keyBufSize, keyBuffer);

      //   if (readKeys(keyBufSize, keyBuffer)) {
      //processKeyStates(isRightHalf, keyBufSize, keyBuffer);
      //   printBytes(keyBuffer, keyBufSize);
      //   initKeyBuf();
      // }
    }


    lastTS = curTime;
  }
}


void initKeyBuf() {
  for (int i = 0; i < keyBufSize; i++) {
    keyBuffer[i] = 0;
  }
}

bool isRight() {

  pinMode(isRightPin, INPUT_PULLDOWN);
  pinMode(isRightPinOut, OUTPUT);
  digitalWrite(isRightPinOut, HIGH);
  delayMicroseconds(100);
  byte isRight = digitalRead(isRightPin);
  pinMode(isRightPin, INPUT_DISABLE);
  pinMode(isRightPinOut, INPUT_DISABLE);
  return isRight == 1;
}
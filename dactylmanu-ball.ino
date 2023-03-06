const int isRightPin = 7;
const int isRightPinOut = 8;
bool isPrimary = false;
bool LOG = false;
bool isRightHalf = false;
unsigned long lastTS = 0;
unsigned long curTime = micros();
const int keyBufSize = 6;
uint8_t keyBuffer[keyBufSize];
const int ballBufSize = 2;
int8_t ballMotionBuffer[ballBufSize];
unsigned long lastMouseTime = 0;
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
  setupBall(isRightHalf);
  setupKeys();
  setupI2c(isPrimary);
  Serial.println("Keyboad ready");
}
void loop() {
  curTime = micros();
  unsigned long elapsed = curTime - lastTS;

  if (elapsed >= 5000)  // polling interval : more than > 0.5 ms.
  {

    if (isPrimary) {

      if (readBall(ballMotionBuffer)) {
        processBallMotionData(ballMotionBuffer[0], ballMotionBuffer[1], !isRightHalf);
        initBallBuf();
      }
      if (readKeys(keyBufSize, keyBuffer)) {
        processKeyStates(isRightHalf, keyBufSize, keyBuffer);
        initKeyBuf();
      }
      if (readSecondary()) {
        processKeyStates(!isRightHalf, keyBufSize, keyBuffer);
        processWheelMotionData( ballMotionBuffer[1], ballMotionBuffer[0], !isRightHalf);
        initKeyBuf();
        initBallBuf();
      }
    } else {

      readBall(ballMotionBuffer);
      readKeys(keyBufSize, keyBuffer);
    }


    lastTS = curTime;
  }
}


void initKeyBuf() {
  for (int i = 0; i < keyBufSize; i++) {
    keyBuffer[i] = 0;
  }
}

void initBallBuf() {
  for (int i = 0; i < ballBufSize; i++) {
    ballMotionBuffer[i] = 0;
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
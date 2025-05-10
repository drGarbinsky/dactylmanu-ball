//################### keyboard #########################

byte rows[] = { 23, 22, 21, 20, 15, 14, 9 };
const int rowCount = sizeof(rows) / sizeof(rows[0]);

byte cols[] = { 5, 4, 3, 2, 1, 0 };
const int colCount = sizeof(cols) / sizeof(cols[0]);

byte keyStates[colCount][rowCount];


void setupKeys() {

  initKeyStates();

  Keyboard.begin();
  for (int x = 0; x < rowCount; x++) {
    pinMode(rows[x], INPUT_PULLUP);
  }
  for (int x = 0; x < colCount; x++) {
    pinMode(cols[x], INPUT);
  }
}

bool readKeys(int keyBufSize, byte* keysBuffer) {
  int keyIdx = 0;
  bool keyRead = false;
  for (int rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    byte row = rows[rowIdx];
    pinMode(row, OUTPUT);
    digitalWrite(row, LOW);
    for (int colIdx = 0; colIdx < colCount; colIdx++) {
      byte col = cols[colIdx];
      pinMode(col, INPUT_PULLUP);
      delayMicroseconds(15);
      byte btnState = !digitalRead(col);


      if (keyStates[colIdx][rowIdx] != btnState) {  // check if button state changed
        keyRead = true;
        if (keyIdx >= keyBufSize) {  // Only so many button presses can be tracked and sent at one time via i2c
          println("Key buffer full");
          return true;  // buffer full
        }
        // col row nonce state
        // 111 111 1     1
        byte state = colIdx;
        state = state << 3;
        state += rowIdx;
        state = state << 2;
        state += 2;  // flip the empty bit as a nonce so we can distinguish between no value and 0,0 released
        state += btnState;
        keysBuffer[keyIdx++] = state;
      }

      keyStates[colIdx][rowIdx] = btnState;
      pinMode(col, INPUT);
    }
    pinMode(row, INPUT);
  }

  return keyRead;
}


void initKeyStates() {
  for (int rowIdx = 0; rowIdx < rowCount; rowIdx++) {
    for (int colIdx = 0; colIdx < colCount; colIdx++) {
      keyStates[colIdx][rowIdx] = 0;
    }
  }
}


//left map - break is currently set to insert 209
int currentLayer = 0;
const byte mod = 255;
const byte lms = 254;
const byte rms = 253;
const byte layers = 2;
const byte macro1 = 252;
const byte macro2 = 251;
const byte macro3 = 250;
const byte macro4 = 249;
const byte colMask = 0xE0;
const byte rowMask = 0X1C;

int leftKeyMap[layers][rowCount][colCount] = {
  { { KEY_EQUAL, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5 },
    { KEY_ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T },
    { KEY_TAB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G },
    { KEY_LEFT_ALT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B },
    { KEY_INSERT , KEY_TILDE, KEY_PAGE_UP, KEY_HOME, KEY_ENTER, KEY_DELETE },
    { 0, 0, KEY_PAGE_DOWN, KEY_END, KEY_BACKSPACE, mod },
    { 0, 0, 0, KEY_LEFT_SHIFT, KEY_LEFT_CTRL, mod } },
  { { KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, mod },
    { 0, 0, 0, 0, 0,  0} }
};

// right map
int rightKeyMap[layers][rowCount][colCount] = {
  { { 54, 55, 56, 57, 48, 45 },
    { 121, 117, 105, 111, 112, 92 },
    { 104, 106, 107, 108, 59, 39 },
    { 110, 109, 44, 46, 47, 133 },
    { lms, rms, 218, 217, 91, 93 },
    { 0, 32, 216, 215, 0, 0 },
    { 176, mod, 132, 135, 0, 0 } },
  { { 200, 201, 202, 203, 204, 205 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 252, 251, 0, 0 },
    { 0, mod, 0, 0, 0, 0 } }
};


int (*keyMap)[rowCount][colCount] = rightKeyMap;

void processKeyStates(bool isRight, int keyBufSize, byte* keysBuffer) {
  if (isRight == false) {
    keyMap = leftKeyMap;
  } else {
    keyMap = rightKeyMap;
  }

  for (int i = 0; i < keyBufSize && i < 6; i++) {
    if (keysBuffer[i] != 0) {
      byte col = (keysBuffer[i] & colMask) >> 5;
      byte row = (keysBuffer[i] & rowMask) >> 2;
      byte btnState = keysBuffer[i] & 1;
      handleKeyPress(keyMap[currentLayer][row][col], btnState, i);
      keysBuffer[i] = 0;
    }
  }
  //Keyboard.send_now();
}
void handleKeyPress(int key, byte btnState, int keyIndex) {
  if (btnState == 1) {
    if (key == lms) {
      Mouse.press(MOUSE_LEFT);
    } else if (key == rms) {
      Mouse.press(MOUSE_RIGHT);
    } else if (key == mod) {
      currentLayer = 1;
      println("layer 1");
    } else if (key == macro1) {
      Keyboard.press(135);
      Keyboard.press(132);
      Keyboard.press(216);
      println("macro1 pressed");
    } else if (key == macro2) {
      Keyboard.press(135);
      Keyboard.press(132);
      Keyboard.press(215);
      println("macro2 pressed");
    } else {
      Keyboard.press(key);
      //keyboard_keys[keyIndex]  = key;
      
      printInt(int(key));
      println(" pressed");
    }
  } else {
    if (key == lms) {
      Mouse.release(MOUSE_LEFT);
    } else if (key == rms) {
      Mouse.release(MOUSE_RIGHT);
    } else if (key == mod) {
      currentLayer = 0;
      println("layer 0");
    } else if (key == macro1) {
      Keyboard.release(135);
      Keyboard.release(132);
      Keyboard.release(216);
      println("macro1 release");
    } else if (key == macro2) {
      Keyboard.release(135);
      Keyboard.release(132);
      Keyboard.release(215);
      println("macro2 release");
    } else {
      Keyboard.release(key);
    
      printInt(int(key));
      println(" released");
    }
  }
}
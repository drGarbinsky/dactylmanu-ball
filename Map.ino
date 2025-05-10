

//left map - break is currently set to insert 209
int currentLayer = 0;
const byte mod = 255;
const byte lms = 254;
const byte rms = 253;
const byte bms = 252;
const byte layers = 2;
const byte macro1 = 250;
const byte macro2 = 249;
const byte macro3 = 248;
const byte macro4 = 247;


const byte colMask = 0xE0;
const byte rowMask = 0X1C;

bool tempMouseLeft = false;
bool tempMouseRight = false;
int leftKeyMap[layers][rowCount][colCount] = {
  { { KEY_EQUAL, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5 },
    { KEY_ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T },
    { KEY_TAB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G },
    { KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B },
    { KEY_RIGHT_GUI, KEY_TILDE, KEY_PAGE_UP, KEY_HOME, bms, KEY_DELETE },
    { 0, 0, KEY_PAGE_DOWN, KEY_END, KEY_BACKSPACE,  KEY_LEFT_ALT },
    { 0, 0, KEY_MEDIA_VOLUME_DEC, mod, KEY_LEFT_CTRL, KEY_MEDIA_VOLUME_INC} },
  { { KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, mod, 0, 0 } }
};

// right map
int rightKeyMap[layers][rowCount][colCount] = {
  { { KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS },
    { KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_BACKSLASH },
    { KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE },
    { KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD,  KEY_SLASH, KEY_LEFT_BRACE },
    { lms, rms,  KEY_RIGHT_CTRL ,KEY_UP, KEY_RIGHT, KEY_RIGHT_BRACE },
    { KEY_RIGHT_SHIFT, KEY_SPACE, KEY_LEFT, KEY_DOWN, 0, 0 },
    { KEY_MEDIA_NEXT_TRACK, KEY_ENTER, mod, KEY_MEDIA_PLAY_PAUSE, 0, 0 } },
  { { KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12 },
    { 0, 0, 0, 0, 0, 0 },
    { lms, rms, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, mod, 0, 0, 0 } }
};


int (*keyMap)[rowCount][colCount] = rightKeyMap;

void  processKeyStates(bool isRight, int keyBufSize, byte* keysBuffer) {
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
    // if (key == KEY_H && curTime - lastMouseTime < tempMouseKeyTime) {
    //   lastMouseTime += 250000;  // advance the time to allow more time for double clicks
    //   Mouse.press(MOUSE_LEFT);
    //   tempMouseLeft = true;
    // } else if (key == KEY_J && curTime - lastMouseTime < tempMouseKeyTime) {
    //   lastMouseTime += 250000;  // advance the time to allow more time for double clicks
    //   Mouse.press(MOUSE_RIGHT);
    //   tempMouseRight = true;
    // } else
     if (key == lms) {
      Mouse.press(MOUSE_LEFT);
    } else if (key == rms) {
      Mouse.press(MOUSE_RIGHT);
    } else if (key == bms) {
      Mouse.press(MOUSE_BACK);
    } else if (key == mod) {
      currentLayer = 1;
      println("layer 1");
    } else if (key == macro1) {
      // Keyboard.press(135);
      // Keyboard.press(132);
      // Keyboard.press(216);
      println("macro1 pressed");
    } else if (key == macro2) {
      // Keyboard.press(135);
      // Keyboard.press(132);
      // Keyboard.press(215);
      println("macro2 pressed");
    } else {
      Keyboard.press(key);
      //keyboard_keys[keyIndex]  = key;

      printInt(int(key));
      println(" pressed");
    }
  } else {
    if (key == KEY_H && tempMouseLeft) {
      Mouse.release(MOUSE_LEFT);
      tempMouseLeft = false;
    } else if (key == KEY_J && tempMouseRight) {
      Mouse.release(MOUSE_RIGHT);
      tempMouseRight = false;
    } else if (key == lms) {
      Mouse.release(MOUSE_LEFT);
    } else if (key == rms) {
      Mouse.release(MOUSE_RIGHT);
    } else if (key == bms) {
      Mouse.release(MOUSE_BACK);
    } else if (key == mod) {
      currentLayer = 0;
      println("layer 0");
    } else if (key == macro1) {
      // Keyboard.release(135);
      // Keyboard.release(132);
      // Keyboard.release(216);
      println("macro1 release");
    } else if (key == macro2) {
      // Keyboard.release(135);
      // Keyboard.release(132);
      // Keyboard.release(215);
      println("macro2 release");
    } else {
      Keyboard.release(key);

      printInt(int(key));
      println(" released");
    }
  }
}
#ifdef ADVANCE_MODE
#include <AdvMouse.h>
#define MOUSE_BEGIN AdvMouse.begin()
#define MOUSE_PRESS(x) AdvMouse.press_(x)
#define MOUSE_RELEASE(x) AdvMouse.release_(x)
#else
#include <Mouse.h>
#define MOUSE_BEGIN Mouse.begin()
#define MOUSE_PRESS(x) Mouse.press(x)
#define MOUSE_RELEASE(x) Mouse.release(x)
#endif

unsigned long lastWheelTime = 0;

void processBallMotionData(int8_t x, int8_t y, bool invertXY) {

  if (invertXY) {
    x = x * -1;
    y = y * -1;
  }

  Mouse.move(x * -1, y, 0, 0);
  lastMouseTime = curTime;
}

void processWheelMotionData(int8_t wheel, int8_t horiz, bool invertWH) {
  unsigned long elapsed = curTime - lastWheelTime;

  if (elapsed < 40000) {
    return;
  } else {
    lastWheelTime = curTime;
  }

  if (abs(wheel) <= 1) {
    wheel = 0;
  }

  if (abs(horiz) <= 1) {
    horiz = 0;
  }

  if (invertWH) {
    wheel = wheel * -1;
    horiz = horiz * -1;
  }

  if (abs(wheel) > abs(horiz)) {
    horiz = 0;
  } else if (abs(horiz) > abs(wheel)) {
    wheel = 0;
  }

  if (wheel != 0 || horiz != 0) {
    print("w: ");
    print(wheel);
    print(" h: ");
    println(horiz);

    Mouse.move(0, 0, wheel, horiz);
  }
}

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
void processBallMotionData(int8_t x, int8_t y, int8_t wheel, int8_t horiz, bool invertXY) {
  unsigned long elapsed = curTime - lastWheelTime;

  if (elapsed < 50000) {
    wheel = 0;
    horiz = 0;
  } else {
    lastWheelTime = curTime;
  }

  if (wheel <= 1 && wheel >= -1) {
    wheel = 0;
  } else {
    wheel = wheel / 2;
    print("wheel: ");
    println(wheel);
  }

  if (horiz <= 1 && horiz >= -1) {
    horiz = 0;
  } else {
    horiz = horiz / 2;
    print("horiz: ");
    println(horiz);
  }

  if (invertXY) {
    x = x * -1;
    y = y * -1;

    wheel = wheel * -1;
    horiz = horiz * -1;
  }



  Mouse.move(x * -1, y, wheel, horiz);
}

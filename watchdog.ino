// #include "Watchdog_t4.h"
// WDT_T4<WDT1> wdt;


// void setupWatchdog(){
//    WDT_timings_t config;
//   config.trigger = 5; /* in seconds, 0->128 */
//   config.timeout = 10; /* in seconds, 0->128 */
//   config.callback = myCallback;
//   wdt.begin(config);
// }


#include <Watchdog_t4.h>
const unsigned long SETUP_LED_OFF_DURATION = 1000;
const unsigned long SETUP_LED_ON_IF_NOT_TRIPPED_DURATION = 4000;
const unsigned long SETUP_LED_ON_IF_TRIPPED_DURATION = 1500;
const unsigned long TIMEOUT_DURATION = 6000;
const unsigned long BLINK_HALF_PERIOD = 100;
const unsigned long RESET_DURATION = 500;

//Watchdog watchdog;

void setupWatchdog() {

  // if (watchdog.tripped()) {
  //     Serial.println("Reset by watchdog!");
  //     delay(100);
  // }
  // // Setup watchdog
  // watchdog.enable(Watchdog::TIMEOUT_2S);
}

void resetWatchdog() {
 // watchdog.reset();
}
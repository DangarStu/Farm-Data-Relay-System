//  FARM DATA RELAY SYSTEM
//
//  GATEWAY 2.000
//
//  Developed by Timm Bogner (timmbogner@gmail.com) in Urbana, Illinois, USA.
//

#include "fdrs_gateway_config.h"
#include <fdrs_gateway.h>

#define BATTERY_VOLTAGE_PIN   7

void sendReading() {
  float batteryLevel = map(analogRead(BATTERY_VOLTAGE_PIN), 0.0f, 4095.0f, 0, 100);
  loadFDRS(batteryLevel, VOLTAGE_T, UNIT_MAC);
  sendFDRS();
}

void setup() {
  beginFDRS();
  //scheduleFDRS(sendReading, INTERVAL_SECONDS * 1000);
}

void loop() {
  loopFDRS();
}

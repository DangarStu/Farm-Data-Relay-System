//  FARM DATA RELAY SYSTEM
//
//  GATEWAY 2.000
//
//  Developed by Timm Bogner (timmbogner@gmail.com) in Urbana, Illinois, USA.
//

#include "fdrs_gateway_config.h"
#include <fdrs_gateway.h>

#define INTERVAL_SECONDS      15 * 60 * 1000
#define BATTERY_VOLTAGE_PIN   7 

void sendReading() {
  int rawADC = analogRead(BATTERY_VOLTAGE_PIN);
  DBG("Pin reads " + String(rawADC));
  float batteryLevel = rawADC * (4.2f / 3983.0f);
  DBG("Battery voltage is " + String(batteryLevel));
  loadFDRS(batteryLevel, VOLTAGE_T, UNIT_MAC);
  sendFDRS();
}

void setup() {
  beginFDRS();
  sendReading();
  scheduleFDRS(sendReading, INTERVAL_SECONDS);
}

void loop() {
  loopFDRS();
}


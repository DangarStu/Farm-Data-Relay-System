//  FARM DATA RELAY SYSTEM
//
//  LoRa Sensor Example
//
//  Developed by Timm Bogner (timmbogner@gmail.com) in Urbana, Illinois, USA.
//  An example of how to send data via LoRa using FDRS.
//

#include "fdrs_node_config.h"
#include <fdrs_node.h>
#include <Wire.h>
#include "DFRobot_INA219.h"

#define FLOAT_SWITCH_PIN  35

float data1;
float switchState = 0; 

DFRobot_INA219_IIC     ina219(&Wire, INA219_I2C_ADDRESS4);

// Revise the following two paramters according to actual reading of the INA219 and the multimeter
// for linearly calibration
float ina219Reading_mA = 1000;
float extMeterReading_mA = 1000;

void setup() {


  pinMode(FLOAT_SWITCH_PIN, INPUT_PULLDOWN);
  analogReadResolution(12); // Set ADC resolution to 12 bits
  beginFDRS();
  //Initialize the voltage and current sensor
  while(ina219.begin() != true) {
      DBG("INA219 begin failed");
      delay(2000);
  }

  //Linear calibration
  ina219.linearCalibrate(
     ina219Reading_mA, // The measured current before calibration
    extMeterReading_mA); //The current measured by other current testers
}

void loop() {
  data1 = floatSwitch();
  loadFDRS(data1, FLOAT_SWITCH);
  float batteryVoltage = readBatteryVoltage();
  loadFDRS(batteryVoltage, VOLTAGE_T);
  sendFDRS();
  sleepFDRS(10);  //Sleep time in seconds
}

float readBatteryVoltage() {
 return ina219.getBusVoltage_V();
}

float floatSwitch() {
  // Read the switch state
  switchState = digitalRead(FLOAT_SWITCH_PIN);

  if (switchState == LOW) {
    // Switch is pressed (closed)
    Serial.println("Switch is ON");
  } else {
    // Switch is not pressed (open)
    Serial.println("Switch is OFF");
  }

  return (switchState);
}

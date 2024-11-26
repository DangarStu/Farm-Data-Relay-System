// FARM DATA RELAY SYSTEM

// Global Configuration
#include <string>

// Developed by Timm Bogner (timmbogner@gmail.com) in Urbana, Illinois, USA.
#ifndef __FDRS_GLOBALS_h__
#define __FDRS_GLOBALS_h__

#define GLOBAL_DBG_LEVEL 2


#define GLOBAL_WIFI_SSID        "LoungeRoom"
#define GLOBAL_WIFI_PASS        "DangarIsland"

#define GLOBAL_DNS1_IPADDRESS    "8.8.8.8"   // Default to Google Primary DNS
#define GLOBAL_DNS2_IPADDRESS    "8.8.4.4"   // Default to Google Secondary DNS

#define GLOBAL_MQTT_ADDR "mqtt.animats.net"
#define GLOBAL_MQTT_PORT 1883

//#define GLOBAL_MQTT_AUTH   //uncomment to enable MQTT authentication  
#define GLOBAL_MQTT_USER   "dangarnet"
#define GLOBAL_MQTT_PASS   "HawkesburyR1v3r"
// MQTT Topics
#define GLOBAL_TOPIC_DATA    "fdrs/data"
#define GLOBAL_TOPIC_STATUS  "fdrs/status"
#define GLOBAL_TOPIC_COMMAND "fdrs/command"

#define TOPIC_EXPANDING

// Define an array of strings that gives names to each MAC 
// integer for the nodes on your FDRS network. The only important
// ones really are the sensors that publish data to MQTT but the
// others are needed to give the sensor its correct index in the
// array.
constexpr std::string TOPIC_NODE[] = {
    "MQTTGateway",          // 0
    "UARTGateway",          // 1
    "LoRaRepeater",         // 2
    "ESPNOWGateway",        // 3
    "Renko"                 // 4
    // Add more strings as needed
};
// Define an array of strings that gives names to each of
// the data types, feel free to add new ones to the end
constexpr std::string TOPIC_TYPE[] = {
    "STATUS_T",        // 0 - Status
    "TEMP_T",          // 1 - Temperature
    "TEMP2_T",         // 2 - Temperature #2
    "HUMIDITY_T",      // 3 - Relative Humidity
    "PRESSURE_T",      // 4 - Atmospheric Pressure
    "LIGHT_T",         // 5 - Light (lux)
    "SOIL_T",          // 6 - Soil Moisture
    "SOIL2_T",         // 7 - Soil Moisture #2
    "SOILR_T",         // 8 - Soil Resistance
    "SOILR2_T",        // 9 - Soil Resistance #2
    "OXYGEN_T",        // 10 - Oxygen
    "CO2_T",           // 11 - Carbon Dioxide
    "WINDSPD_T",       // 12 - Wind Speed
    "WINDHDG_T",       // 13 - Wind Direction
    "RAINFALL_T",      // 14 - Rainfall
    "MOTION_T",        // 15 - Motion
    "VOLTAGE_T",       // 16 - Voltage
    "VOLTAGE2_T",      // 17 - Voltage #2
    "CURRENT_T",       // 18 - Current
    "CURRENT2_T",      // 19 - Current #2
    "IT_T",            // 20 - Iterations
    "LATITUDE_T",      // 21 - GPS Latitude
    "LONGITUDE_T",     // 22 - GPS Longitude
    "ALTITUDE_T",      // 23 - GPS Altitude
    "HDOP_T",          // 24 - GPS HDOP
    "LEVEL_T",         // 25 - Fluid Level
    "UV_T",            // 26 - UV
    "PM1_T",           // 27 - 1 Particles
    "PM2_5_T",         // 28 - 2.5 Particles
    "PM10_T",          // 29 - 10 Particles
    "POWER_T",         // 30 - Power
    "POWER2_T",        // 31 - Power #2
    "ENERGY_T",        // 32 - Energy
    "ENERGY2_T",       // 33 - Energy #2
    "WEIGHT_T",        // 34 - Weight
    "WEIGHT2_T",        // 35 - Weight #2
    // Start of custom user-defined types.
    "FLOAT_SWITCH"    // 36 - Float switch
};

// NTP Time Server
#define GLOBAL_DST_RULE        USDST    // Daylight saving time rules: Use USDST for United States DST rules, EUDST for European Union
#define GLOBAL_TIME_SERVER      "0.us.pool.ntp.org"
#define GLOBAL_STD_OFFSET      (-6)                // Local standard time offset in hours from UTC - if unsure, check https://time.is
#define GLOBAL_DST_OFFSET      (STD_OFFSET + 1)    // Local savings time offset in hours from UTC - if unsure, check https://time.is
#define GLOBAL_TIME_FETCHNTP    60      // Time in minutes between fetching time from NTP server
#define GLOBAL_TIME_PRINTTIME   15      // Time in minutes between printing local time
#define GLOBAL_TIME_SEND_INTERVAL 60    // Time in minutes between sending out time

#define GLOBAL_LORA_FREQUENCY 915     // Carrier frequency in MHz. Allowed values range from 137.0 MHz to 1020.0 MHz (varies by chip).
#define GLOBAL_LORA_SF 7              // LoRa link spreading factor. Allowed values range from 6 to 12.
#define GLOBAL_LORA_BANDWIDTH 125.0   // LoRa link bandwidth in kHz. Allowed values are 10.4, 15.6, 20.8, 31.25, 41.7, 62.5, 125, 250 and 500 kHz.
#define GLOBAL_LORA_CR 5              // LoRa link coding rate denominator. Allowed values range from 5 to 8.
#define GLOBAL_LORA_SYNCWORD 0x12     // LoRa sync word. Can be used to distinguish different LoRa networks. Note that 0x34 is reserved for LoRaWAN.
#define GLOBAL_LORA_INTERVAL 5000     // Interval between LoRa buffer releases. Must be longer than transmission time-on-air.

#define MAC_PREFIX  0xAA, 0xBB, 0xCC, 0xDD, 0xEE  // MAC address prefix. Can be used to distinguish different ESP-NOW networks.

#if defined(USE_OLED) || defined(USE_RTC_DS3231) || defined(USE_RTC_DS1307)
    #define USE_I2C
#endif

#if defined(USE_RTC_DS3231) || defined(USE_RTC_DS1307)
  #define USE_RTC
#endif

#if defined(USE_GPS) && defined(ESP8266)
  #error "For ESP8266 only one UART has both Tx and Rx capabilities. GPS not supported for ESP8266"
#endif

#if defined(USE_ETHERNET) && !defined(ESP32)
  #error "Ethernet only supported for ESP32."
#endif

#if defined(USE_OLED) && (!defined(ESP32) && !defined(ESP8266))
  #warning "OLED current supported for only ESP32 or ESP8266."
  #undef USE_OLED
#endif

#endif // __FDRS_GLOBALS_h__

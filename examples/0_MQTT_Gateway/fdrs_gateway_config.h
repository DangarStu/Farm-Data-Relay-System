//  FARM DATA RELAY SYSTEM
//
//  GATEWAY 2.000 Configuration

#include <fdrs_globals.h>

#define FDRS_DEBUG     //Enable USB-Serial debugging
#define DEBUG_CONFIG // Displays full config info on startup

#define UNIT_MAC     0x00  // The address of this gateway

// Actions -- Define what happens when a packet arrives at each interface:
// Current function options are: sendESPNow(MAC), sendSerial(), sendMQTT(),
//  sendLoRaNbr(interface) , sendESPNowNbr(interface).

#define ESPNOWG_ACT    
#define SERIAL_ACT     sendMQTT();    
#define MQTT_ACT       sendSerial();   
#define LORAG_ACT      

// Protocols -- Define which protocols the gateway will use.
// Warning: ESP-NOW and WiFi should not be used simultaneously.

//#define USE_ESPNOW  
//#define USE_LORA
#define USE_WIFI    //Used only for MQTT gateway

// Neighbor addresses
#define ESPNOW_NEIGHBOR_1 0x0E  // ESPNOW1 Address 
#define ESPNOW_NEIGHBOR_2 0x0F  // ESPNOW2 Address
#define LORA_NEIGHBOR_1    0x0E  // LoRa1 Address
#define LORA_NEIGHBOR_2    0x0F  // LoRa2 Address

// Neighbor Actions
#define ESPNOW1_ACT    
#define ESPNOW2_ACT                    
#define LORA1_ACT 
#define LORA2_ACT 

// LoRa Configuration
#define RADIOLIB_MODULE SX1276 //Tested on SX1276
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DIO 26
#define LORA_TXPWR 17   // LoRa TX power in dBm (: +2dBm - +17dBm (for SX1276-7) +20dBm (for SX1278))
#define LORA_ACK        // Request LoRa acknowledgment.

//Pins for UART data interface (ESP32 only)
#define RXD2 14
#define TXD2 15

// WiFi and MQTT Credentials  -- These will override the global settings
//#define WIFI_SSID   "Your SSID"  
//#define WIFI_PASS   "Your Password"

//#define MQTT_ADDR   "192.168.0.8"
//#define MQTT_PORT   1883 // Default MQTT port is 1883
//#define MQTT_AUTH   //Enable MQTT authentication 
//#define MQTT_USER   "Your MQTT Username"
//#define MQTT_PASS   "Your MQTT Password"

//Logging settings  --  Logging will occur when MQTT is disconnected
//#define USE_SD_LOG        //Enable SD-card logging
//#define USE_FS_LOG        //Enable filesystem (flash) logging
#define LOGBUF_DELAY 10000  // Log Buffer Delay - in milliseconds
#define SD_SS 0             //SD card CS pin (Use different pins for LoRa and SD)
#define LOG_FILENAME "fdrs_log.csv"

///#define USE_OLED
#define OLED_HEADER "FDRS"
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
//  FARM DATA RELAY SYSTEM
//
//  GATEWAY CONFIGURATION

//Addresses
#define UNIT_MAC           0x00  // The address of this gateway

#define ESPNOW_NEIGHBOR_1  0x00  // Address of ESP-NOW neighbor #1
#define ESPNOW_NEIGHBOR_2  0x00  // Address of ESP-NOW neighbor #2
#define LORA_NEIGHBOR_1    0x00  // Address of LoRa neighbor #1
#define LORA_NEIGHBOR_2    0x00  // Address of LoRa neighbor #2

// Interfaces
//#define USE_ESPNOW  
//#define USE_LORA
#define USE_WIFI  // Will cause errors if used with ESP-NOW. Use a serial link instead!
//#define USE_ETHERNET

// Routing
// Options: sendESPNowNbr(1 or 2); sendESPNowPeers(); sendLoRaNbr(1 or 2); broadcastLoRa(); sendSerial(); sendMQTT();
#define ESPNOWG_ACT    
#define LORAG_ACT      
#define SERIAL_ACT     sendMQTT();
#define MQTT_ACT       sendSerial();   
#define INTERNAL_ACT   sendMQTT();
#define ESPNOW1_ACT   
#define ESPNOW2_ACT                    
#define LORA1_ACT      
#define LORA2_ACT 

///////////////////////////////////////////////////////////////
// Start of Generic configuration
///////////////////////////////////////////////////////////////

#define FDRS_DEBUG     // Enable USB-Serial debugging
#define DBG_LEVEL 2    // 0 for minimal messaging, 1 for troubleshooting, 2 for development

// UART data interface pins (ESP32 only)
#define RXD2 18
#define TXD2 19

///////////////////////////////////////////////////////////////
// End of Generic configuration
///////////////////////////////////////////////////////////////

// NTP Time settings for gateways
#define DST_RULE        USDST  // Daylight saving time rules: Use USDST for United States DST rules, EUDST for European Union
#define TIME_SERVER       "0.us.pool.ntp.org"       // NTP time server to use. If FQDN at least one DNS server is required to resolve name
#define STD_OFFSET      (-6)                // Local standard time offset in hours from UTC - if unsure, check https://time.is
#define DST_OFFSET      (STD_OFFSET + 1)    // Local savings time offset in hours from UTC - if unsure, check https://time.is
#define TIME_FETCHNTP     60      // Time, in minutes, between fetching time from NTP server
#define TIME_PRINTTIME    15     // Time, in minutes, between printing local time to debug
#define TIME_SEND_INTERVAL 10    // Time, in minutes, between sending out time to remote devices.  0 will only send when time is updated
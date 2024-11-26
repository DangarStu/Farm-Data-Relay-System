//  FARM DATA RELAY SYSTEM
//
//  GATEWAY CONFIGURATION

//Addresses
#define UNIT_MAC           0x02  // The address of this gateway

#define ESPNOW_NEIGHBOR_1  0x00  // Address of ESP-NOW neighbor #1
#define ESPNOW_NEIGHBOR_2  0x00  // Address of ESP-NOW neighbor #2
#define LORA_NEIGHBOR_1    0x01  // Address of LoRa neighbor #1
#define LORA_NEIGHBOR_2    0x03  // Address of LoRa neighbor #2

// Interfaces
//#define USE_ESPNOW  
#define USE_LORA
//#define USE_WIFI  // Will cause errors if used with ESP-NOW. Use a serial link instead!
//#define USE_ETHERNET

// Routing
// Options: sendESPNowNbr(1 or 2); sendESPNowPeers(); sendLoRaNbr(1 or 2); broadcastLoRa(); sendSerial(); sendMQTT();
#define ESPNOWG_ACT
#define LORAG_ACT      sendLoRaNbr(1);
#define SERIAL_ACT     
#define MQTT_ACT          
#define INTERNAL_ACT   sendLoRaNbr(1);
#define ESPNOW1_ACT
#define ESPNOW2_ACT                    
#define LORA1_ACT      sendLoRaNbr(2); broadcastLoRa(); 
#define LORA2_ACT      sendLoRaNbr(1);

///////////////////////////////////////////////////////////////
// Start of configuration for Lilygo TTGO LoRa32-OLED
///////////////////////////////////////////////////////////////

// LoRa Configuration
#define RADIOLIB_MODULE SX1276
#define LORA_SS    18
#define LORA_RST   14
#define LORA_DIO   26
#define LORA_BUSY  33
//#define USE_SX126X

#define LORA_TXPWR 17   // LoRa TX power in dBm (: +2dBm - +17dBm (for SX1276-7) +20dBm (for SX1278))

#define FLOAT_SWITCH_PIN 45

//#define CUSTOM_SPI
#define LORA_SPI_SCK  5
#define LORA_SPI_MISO 19
#define LORA_SPI_MOSI 27

#define LORA_TXPWR 17    // LoRa TX power in dBm (: +2dBm - +17dBm (for SX1276-7) +20dBm (for SX1278))
#define LORA_ACK        // Request LoRa acknowledgment.

#define FDRS_DEBUG     // Enable USB-Serial debugging
//#define DBG_LEVEL 0    // 0 for minimal messaging, 1 for troubleshooting, 2 for development

// I2C - OLED or RTC
#define I2C_SDA 21
#define I2C_SCL 22

// OLED -- Displays console debugging messages on an SSD1306 I²C OLED
#define USE_OLED    
#define OLED_HEADER "FDRS"
#define OLED_PAGE_SECS 30
#define OLED_RST -1

///////////////////////////////////////////////////////////////
// End of configuration for Lilygo TTGO LoRa32-OLED
///////////////////////////////////////////////////////////////

/// NTP Time settings for gateways
#define DST_RULE        USDST // Daylight saving time rules: Use USDST for United States DST rules, EUDST for European Union
#define TIME_SERVER       "0.us.pool.ntp.org"       // NTP time server to use. If FQDN at least one DNS server is required to resolve name
#define STD_OFFSET      (-6)                // Local standard time offset in hours from UTC - if unsure, check https://time.is
#define DST_OFFSET      (STD_OFFSET + 1)    // Local savings time offset in hours from UTC - if unsure, check https://time.is
#define TIME_FETCHNTP     60      // Time, in minutes, between fetching time from NTP server
#define TIME_PRINTTIME    15     // Time, in minutes, between printing local time to debug
#define TIME_SEND_INTERVAL 10    // Time, in minutes, between sending out time to remote devices.  0 will only send when time is updated
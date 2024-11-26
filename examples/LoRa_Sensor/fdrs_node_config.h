//  FARM DATA RELAY SYSTEM
//
//  NODE CONFIGURATION

//Addresses
#define READING_ID    4   //Unique ID for this sensor
#define GTWY_MAC      0x03 //Address of the nearest gateway

#define DEEP_SLEEP

// Interfaces
#define USE_ESPNOW  
//#define USE_LORA
//#define USE_WIFI  // Will cause errors if used with ESP-NOW. Use a serial link instead!
//#define USE_ETHERNET

///////////////////////////////////////////////////////////////
// Start of Sailor Hat and Ra-01 module configuration
///////////////////////////////////////////////////////////////

// LoRa Configuration 
#define RADIOLIB_MODULE SX1278
#define LORA_SS    22
#define LORA_RST   25
#define LORA_DIO   26
#define LORA_BUSY  13  // The SX1278 doesn't have a BUSY pin
//#define USE_SX126X

#define LORA_TXPWR 12   // LoRa TX power in dBm (: +2dBm - +17dBm (for SX1276-7) +20dBm (for SX1278))

//#define CUSTOM_SPI
#define LORA_SPI_SCK  18
#define LORA_SPI_MISO 19
#define LORA_SPI_MOSI 23

#define FDRS_DEBUG     // Enable USB-Serial debugging
#define DBG_LEVEL 2    // 0 for minimal messaging, 1 for troubleshooting, 2 for development

// I2C - OLED or RTC
#define I2C_SDA 16
#define I2C_SCL 17

// OLED -- Displays console debugging messages on an SSD1306 I²C OLED
//#define USE_OLED    
#define OLED_HEADER "FDRS"
#define OLED_PAGE_SECS 30
#define OLED_RST 16

// RTC - I2C
// #define USE_RTC_DS3231
// #define RTC_ADDR 0x57
// #define USE_RTC_DS1307
// #define RTC_ADDR 0x68

// UART data interface pins (ESP32 only)
#define RXD2 14
#define TXD2 15

///////////////////////////////////////////////////////////////
// End of Sailor Hat and Ra-01 module configuration
///////////////////////////////////////////////////////////////

/// NTP Time settings for gateways
#define DST_RULE        USDST // Daylight saving time rules: Use USDST for United States DST rules, EUDST for European Union
#define TIME_SERVER       "0.us.pool.ntp.org"       // NTP time server to use. If FQDN at least one DNS server is required to resolve name
#define STD_OFFSET      (-6)                // Local standard time offset in hours from UTC - if unsure, check https://time.is
#define DST_OFFSET      (STD_OFFSET + 1)    // Local savings time offset in hours from UTC - if unsure, check https://time.is
#define TIME_FETCHNTP     60      // Time, in minutes, between fetching time from NTP server
#define TIME_PRINTTIME    15     // Time, in minutes, between printing local time to debug
#define TIME_SEND_INTERVAL 10    // Time, in minutes, between sending out time to remote devices.  0 will only send when time is updated
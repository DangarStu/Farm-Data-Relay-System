#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <sstream>
#include <fdrs_gateway_config.h>

// select MQTT server address
#if defined(MQTT_ADDR)
#define FDRS_MQTT_ADDR MQTT_ADDR
#elif defined(GLOBAL_MQTT_ADDR)
#define FDRS_MQTT_ADDR GLOBAL_MQTT_ADDR
#else
// ASSERT("NO MQTT address defined! Please define in fdrs_globals.h (recommended) or in fdrs_node_config.h");
#endif // MQTT_ADDR

// select MQTT server port
#if defined(MQTT_PORT)
#define FDRS_MQTT_PORT MQTT_PORT
#elif defined(GLOBAL_MQTT_PORT)
#define FDRS_MQTT_PORT GLOBAL_MQTT_PORT
#else
#define FDRS_MQTT_PORT 1883
#endif // MQTT_PORT

// select MQTT user name
#if defined(MQTT_USER)
#define FDRS_MQTT_USER MQTT_USER
#elif defined(GLOBAL_MQTT_USER)
#define FDRS_MQTT_USER GLOBAL_MQTT_USER
#else
// ASSERT("NO MQTT user defined! Please define in fdrs_globals.h (recommended) or in fdrs_node_config.h");
#endif // MQTT_USER

// select MQTT user password
#if defined(MQTT_PASS)
#define FDRS_MQTT_PASS MQTT_PASS
#elif defined(GLOBAL_MQTT_PASS)
#define FDRS_MQTT_PASS GLOBAL_MQTT_PASS
#else
// ASSERT("NO MQTT password defined! Please define in fdrs_globals.h (recommended) or in fdrs_node_config.h");
#endif // MQTT_PASS
#if defined(MQTT_AUTH) || defined(GLOBAL_MQTT_AUTH)
#define FDRS_MQTT_AUTH
#endif // MQTT_AUTH

#if defined(TOPIC_DATA)
#define FDRS_TOPIC_DATA TOPIC_DATA
#else
#define FDRS_TOPIC_DATA GLOBAL_TOPIC_DATA
#endif // TOPIC_DATA

#if defined(TOPIC_STATUS)
#define FDRS_TOPIC_STATUS TOPIC_STATUS
#else
#define FDRS_TOPIC_STATUS GLOBAL_TOPIC_STATUS
#endif // TOPIC_STATUS

#if defined(TOPIC_COMMAND)
#define FDRS_TOPIC_COMMAND TOPIC_COMMAND
#else
#define FDRS_TOPIC_COMMAND GLOBAL_TOPIC_COMMAND
#endif // TOPIC_COMMAND

#define MQTT_MAX_BUFF_SIZE 1024

#define TOPIC_EXPANDING

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMqttConnectAttempt = 0;

const char *mqtt_server = FDRS_MQTT_ADDR;
const int mqtt_port = FDRS_MQTT_PORT;

#ifdef FDRS_MQTT_AUTH
const char *mqtt_user = FDRS_MQTT_USER;
const char *mqtt_pass = FDRS_MQTT_PASS;
#else
const char *mqtt_user = NULL;
const char *mqtt_pass = NULL;
#endif // FDRS_MQTT_AUTH

void reconnect_mqtt(short int attempts, bool silent)
{
    if (!silent)
        DBG("Connecting MQTT...");

    for (short int i = 1; i <= attempts; i++)
    {
        // Attempt to connect
        if (client.connect("FDRS_GATEWAY", mqtt_user, mqtt_pass))
        {
            // Subscribe
            client.subscribe(FDRS_TOPIC_COMMAND);
            if (!silent)
                DBG(" MQTT Connected");
            return;
        }
        else
        {
            if (!silent)
            {
                char msg[23];
                sprintf(msg, " Attempt %d/%d", i, attempts);
                DBG(msg);
            }
            if ((attempts != 1))
            {
                delay(3000);
            }
        }
    }

    if (!silent)
        DBG(" Connecting MQTT failed.");
}

void reconnect_mqtt(int attempts)
{
    reconnect_mqtt(attempts, false);
}

// Handles MQTT in loop()
void handleMQTT()
{
    if (!client.connected())
    {
        if(TDIFF(lastMqttConnectAttempt,5000)) {
            reconnect_mqtt(1, true);
            lastMqttConnectAttempt = millis();
        }
    }
    client.loop(); // for recieving incoming messages and maintaining connection
}

void mqtt_callback(char *topic, byte *message, unsigned int length)
{
    String incomingString;
    DBG(topic);
    for (unsigned int i = 0; i < length; i++)
    {
        incomingString += (char)message[i];
    }
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, incomingString);
    if (error)
    { // Test if parsing succeeds.
        DBG2("json parse err");
        DBG2(incomingString);
        return;
    }
    else
    {
        int s = doc.size();
        // UART_IF.println(s);
        for (int i = 0; i < s; i++)
        {
            theData[i].id = doc[i]["id"];
            theData[i].t = doc[i]["type"];
            theData[i].d = doc[i]["data"];
        }
        ln = s;
        newData = event_mqtt;
        DBG("Incoming MQTT.");
    }
}

void begin_mqtt()
{
    client.setServer(mqtt_server, mqtt_port);
    client.setBufferSize(MQTT_MAX_BUFF_SIZE);

    if (!client.connected())
    {
        reconnect_mqtt(5);
    }
    client.setCallback(mqtt_callback);
}

void mqtt_publish(const char *topic, const char *payload)
{
    if (!client.publish(topic, payload))
    {
        DBG(" Error on sending MQTT");

    }
}

std::string floatToString(float value) {
    std::ostringstream oss;

    // Set precision and remove trailing zeros
    oss.precision(6); // Adjust precision as needed
    oss << std::fixed << value;

    std::string result = oss.str();

    // Trim trailing zeros and the decimal point if unnecessary
    if (result.find('.') != std::string::npos) {
        result.erase(result.find_last_not_of('0') + 1); // Remove trailing zeros
        if (result.back() == '.') {
            result.pop_back(); // Remove the decimal point if it's the last character
        }
    }

    return result;
}

#ifdef TOPIC_EXPANDING
void sendMQTT()
{
    DBG("Sending MQTT topics.");
    for (int i = 0; i < ln; i++)
    {
        if (theData[i].id < 0 || theData[i].id >= sizeof(TOPIC_NODE) / sizeof(TOPIC_NODE[0])) {
            DBG("Invalid index for node: " + theData[i].id);
            continue;
        }
        if (theData[i].t < 0 || theData[i].t >= sizeof(TOPIC_TYPE) / sizeof(TOPIC_TYPE[0])) {
            DBG("Invalid index for topic: " + theData[i].t);
            continue;
        }


        std::string topic = std::string(FDRS_TOPIC_DATA) + "/" + TOPIC_NODE[theData[i].id] + "/" + TOPIC_TYPE[theData[i].t];

        // Convert the data from a float to a string to push to MQTT
        auto data = floatToString(theData[i].d);

        // Publish this data point and move on to the next.
        mqtt_publish(topic.c_str(), (char *)data.c_str());
    }

}
#else
void sendMQTT()
{
    DBG("Sending JSON to MQTT.");
    JsonDocument doc;
    for (int i = 0; i < ln; i++)
    {
        doc[i]["id"] = theData[i].id;       //uint16_t
        doc[i]["type"] = theData[i].t;      //uint8_t
        doc[i]["data"] = theData[i].d;      // float
    }
    String outgoingString;
    serializeJson(doc, outgoingString);
    // Publish the entire JSON structure under the default FDRS data topic
    mqtt_publish(FDRS_TOPIC_DATA, (char *)outgoingString.c_str());
}
#endif
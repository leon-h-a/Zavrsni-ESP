#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// WiFi setup
const char WiFi_ssid[]= "TP-Link_2BC6";
const char WiFi_pass[] = "83911903";

// MQTT setup
const char MQTT_server[] = "172.105.76.166";
const int MQTT_port = 1883;

WiFiClient wifiClient;
PubSubClient pubSubCli;
String clientName;
void callback_fnc(const char* topic, const byte* payload, unsigned int length);
void WiFiSetup(const char* ssid, const char* pass);
void MQTTSetup(const char* mqtt_ip, int mqtt_port);
String macToStr(const uint8_t* mac);

__unused void setup(){
    delay(5000);
    Serial.begin(9600);
    Serial.setTimeout(100);
    WiFiSetup(WiFi_ssid, WiFi_pass);
    MQTTSetup(MQTT_server, MQTT_port);
}

void loop() {
    if (!pubSubCli.connected()){
        MQTTSetup(MQTT_server, MQTT_port);
    }
    else if (WiFi.status() != WL_CONNECTED){
        WiFiSetup(WiFi_ssid, WiFi_pass);
        MQTTSetup(MQTT_server, MQTT_port);
    }
    if (Serial.available()){
        String atmegaData = Serial.readString();
        String topic = "/" + clientName + "/data";
        pubSubCli.publish((char*) topic.c_str(), (char*) atmegaData.c_str());
    }
    pubSubCli.loop();
    delay(10);
}

void WiFiSetup(const char* ssid, const char* pass){
    Serial.println("Trying WiFi connection...");
    WiFi.begin(ssid, pass);
    while (WiFi.status() == WL_DISCONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    if (WiFi.status() == WL_NO_SSID_AVAIL){
        Serial.println("\nUnable to find AP with provided SSID");
    }
    else if (WiFi.status() == WL_CONNECT_FAILED){
        Serial.println("\nIncorrect password");
    }
    else if (WiFi.status() == WL_CONNECTED){
        Serial.println("\nConnection OK");
        Serial.print("\nConnected, IP address: ");
        Serial.println(WiFi.localIP());
    }
    else{
        Serial.println("\nStatus code 0:WL_IDLE_STATUS:\"in process of changing between statuses\" ");
    }
}

void MQTTSetup(const char* mqtt_ip, int mqtt_port){
    // MAC address setup
    clientName += "esp8266-";
    uint8_t mac[6];
    WiFi.macAddress(mac);
    clientName += macToStr(mac);

    Serial.println("Trying MQTT connection...");
    pubSubCli.setClient(wifiClient);
    pubSubCli.setServer(mqtt_ip, mqtt_port);
    pubSubCli.setCallback(callback_fnc);
    while (!pubSubCli.connected()){
        pubSubCli.connect((char*) clientName.c_str());
        delay(500);
    }
    pubSubCli.publish("/init", (char*) clientName.c_str());
}

String macToStr(const uint8_t* mac){
    String result;
    for (int i = 0; i < 6; ++i) {
        result += String(mac[i], HEX);
        if (i < 5){
            result += ':';
        }
    }
    return result;
}

void callback_fnc(const char* topic, const byte* payload, unsigned int length){
    Serial.println((char*) payload);
}
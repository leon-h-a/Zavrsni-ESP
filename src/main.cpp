#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// WiFi setup
const char WiFi_ssid[]= "TP-Link_2BC6";
const char WiFi_pass[] = "83911903";

// MQTT setup
const char MQTT_server[] = "172.105.76.166";
const int MQTT_port = 1883;

PubSubClient pubSubCli;
void WiFiSetup(const char* ssid, const char* pass);
void MQTTSetup(PubSubClient* subClient, const char* mqtt_ip, int mqtt_port);
void callback_fnc(const char* topic, const byte* payload, unsigned int length);

__unused void setup(){
    delay(5000);
    Serial.begin(9600);
    WiFiSetup(WiFi_ssid, WiFi_pass);
    MQTTSetup(&pubSubCli, MQTT_server, MQTT_port);
//    pubsubclient.setCallback(&callback_fnc);
}

void loop() {
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

void MQTTSetup(PubSubClient* subClient, const char* mqtt_ip, int mqtt_port){
//     MAC address setup
//    uint8_t mac[6];
//    WiFi.macAddress(mac);
//    Serial.println((char*) mac);
//    Serial.println(mac);


    Serial.println("Trying MQTT connection...");
    WiFiClient WiFiClient;
    pubSubCli.setClient(WiFiClient);
    pubSubCli.setServer(mqtt_ip, mqtt_port);
    while (!pubSubCli.connected()){
        pubSubCli.connect("TheCli");
        delay(500);
    }
    Serial.println("Yaaaaa0");
}

String macToStr(const uint8_t* mac){
    String result;
    for (int i = 0; i < 6; ++i) {
        result += String(mac[i], 16);

        if (i < 5){
            result += ':';
        }
    }
    return result;
}

void callback_fnc(const char* topic, const byte* payload, unsigned int length){
    Serial.println((char*) payload);
}


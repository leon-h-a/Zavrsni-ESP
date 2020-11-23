#ifndef ZAVRSNI_ESP_communicationPackets_H
#define ZAVRSNI_ESP_communicationPackets_H
#include <string>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
using namespace std;

//void WiFiSetup(const char* ssid, const char* pass){
//    Serial.println("Trying WiFi connection...");
//    WiFi.begin(ssid, pass);
//    while (WiFi.status() == WL_DISCONNECTED)
//    {
//        delay(500);
//        Serial.print(".");
//    }
//    if (WiFi.status() == WL_NO_SSID_AVAIL){
//        Serial.println("\nUnable to find AP with provided SSID");
//    }
//    else if (WiFi.status() == WL_CONNECT_FAILED){
//        Serial.println("\nIncorrect password");
//    }
//    else if (WiFi.status() == WL_CONNECTED){
//        Serial.println("\nConnection OK");
//        Serial.print("\nConnected, IP address: ");
//        Serial.println(WiFi.localIP());
//    }
//    else{
//        Serial.println("\nStatus code 0:WL_IDLE_STATUS:\"in process of changing between statuses\" ");
//    }
//}

//void MQTTSetup(PubSubClient* pubsubclient, const char* MQTT_ip, int MQTT_port){
////     MAC address setup
////    uint8_t mac[6];
////    WiFi.macAddress(mac);
////    Serial.println((char*) mac);
////    Serial.println(mac);
//
//
//    Serial.println("Trying MQTT connection...");
//    WiFiClient WiFiClient;
//    pubsubclient->setClient(WiFiClient);
//    pubsubclient->setServer(MQTT_ip, MQTT_port);
//    while (!pubsubclient->connected()){
//        pubsubclient->connect("TheCli");
//        delay(500);
//    }
//    Serial.println("Yaaaaa0");
//}

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
#endif //ZAVRSNI_ESP_communicationPackets_H
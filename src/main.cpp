#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

char ssid[] = "TP-Link_2BC6";
char pass[] = "83911903";
#define MQTT_srv "172.105.76.166"
int MQTT_port = 1883;

// Prototypes
void callback_fnc(const char* topic, byte* payload, unsigned int length);

WiFiClient WiFiClient;
PubSubClient client(MQTT_srv, 1883, callback_fnc, WiFiClient);

__unused void setup()
{
    delay(5000);
    Serial.begin(9600);

    // WiFi configuration
    Serial.println("Setting up WiFi");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, my IP address: ");
    Serial.println(WiFi.localIP());

    // MQTT configuration
    Serial.println("setting up MQTT");
    client.setClient(WiFiClient);
    client.setServer(MQTT_srv, MQTT_port);
    client.setCallback(callback_fnc);
    while (!client.connected()){
        client.connect("TheCli");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected to MQTT server @ ");
    Serial.println(MQTT_srv);
    if (client.subscribe("/sub")) {
        Serial.println("Subscribed to topic /sub");
    }
}

void callback_fnc(const char* topic, byte* payload, unsigned int length){
    Serial.println("Message received from broker");
    client.publish("/pub","hello back @ u!");
    Serial.println("Message sent back");
}

void loop() {
    client.loop();
    delay(10);
}
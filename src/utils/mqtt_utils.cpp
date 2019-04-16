/*
 * MQTT Library for publish/subscribe messaging with a server.
 * To know more - https://pubsubclient.knolleary.net/
 */

#include "../inc/mqtt_utils.h"

/*
 * Declare an uninitialised client instance
 */
static PubSubClient client;
static WiFiClient wifi_client;

void mqtt_init() {
    client.setClient(wifi_client);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    /*
     * Comment it out if you don't require callback functionality
     * Needed when you're subscribing to a topic
     */
    client.setCallback(mqtt_callback);
    
    // Connect to MQTT Server
    mqtt_connect();
}

void mqtt_connect() {
    client.connect(CLIENTID, MQTT_USER, MQTT_PASSWD);
    
    if (!client.connected()) {
        Serial.println("Failed, rc=");
        Serial.print(client.state());
        Serial.println("Trying again in 5 seconds..");
        // Wait 5 seconds before retrying
        delay(5000);
        mqtt_connect();
    } else {
        Serial.println("MQTT Client Connected");
    }
}

 void mqtt_publish(const char* topic, char* msg) {
    if (!client.publish(topic, msg)) {
        Serial.println("Error!! ");
        Serial.print("Publish Failed");
    } else {
        Serial.println("Message Published [");
        Serial.print(topic);
        Serial.print("]: ");
        Serial.print(msg);
    }
}

void mqtt_subscribe(const char* topic) {
    if (!client.subscribe(topic)) {
        Serial.println("Subscription to ");
        Serial.print(topic);
        Serial.print(" failed");
    } else {
        Serial.println("Subscribed to ");
        Serial.print(topic);
    }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.println("Message Arrived [");
    Serial.print(topic);
    Serial.print("]");

    for (int i=0; i<length; i++) {
        Serial.println((char)payload[i]);
    }
}

#include <Arduino.h>
#include "mqtt_credentials.h"
//#include "../../libs/PubSubClient/src/PubSubClient.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

void mqtt_init();

void mqtt_connect();

void mqtt_publish(const char* topic, char* msg);

void mqtt_subscribe(const char* topic);

void mqtt_callback(char* topic, byte* payload, unsigned int length);




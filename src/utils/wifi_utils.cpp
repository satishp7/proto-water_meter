#include "../inc/wifi_utils.h"

void wifi_setup() {
    Serial.println();
    Serial.print("Connecting to:");
    Serial.print(SSID_WIFI);

    WiFi.begin(SSID_WIFI, SSID_PASSWD);

    while (WiFi.status() != 3) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi Connected");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP());
}


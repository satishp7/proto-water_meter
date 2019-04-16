/* Author: Sumit Pundir
 *
 * Copyright (C) 2019-2020 HiveBriq Software Consultancy
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "src/inc/meter_utils.h"
#include "src/inc/wifi_utils.h"
#include "src/inc/mqtt_utils.h"

const int buttonPin = D2; // variable for D2 pin

const char* publish_topic = "sensor/watermeter";
const char* subscribe_topic = "";

char push_data[100];

void setup() {
  Serial.begin(115200); // Start the Serial communication send messages to the computer

  // Initialization of the variable "buttonPin" as INPUT(D2 pin)
  pinMode (buttonPin, INPUT);

  // WIFI Initialization 
  wifi_setup();

  // MQTT Initialization
  mqtt_init();

  meter_init();

  digitalWrite (buttonPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(buttonPin), pulseCounter, RISING);
}

void loop() {
  if ((millis() - lastTime()) > 1000) {
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt (sensorInterrupt);

    snprintf(push_data, sizeof(push_data), "Flow rate:%d.%d L/min, Current Liquid Flowing:%u mL/Sec, Output Liquid Quantity:%u mL", flowRateCalculater(), fracCalculater(), flowMilliLitresCalculater(), totalMilliLitresCalculater());

    mqtt_publish(publish_topic, push_data);

    // Reset the pulse counter so we can start incrementing again
    resetCounter();

    // Enable the interrupt again now that we've finished sending the output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
}

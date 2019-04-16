#include <Arduino.h>
#include <EEPROM.h>

const byte sensorInterrupt =  0 ; // 0 = digital pin 2 

void meter_init();

void pulseCounter();

int flowRateCalculater();

unsigned int flowMilliLitresCalculater();

unsigned int totalMilliLitresCalculater();

unsigned int fracCalculater();

unsigned int lastTime();

void resetCounter();

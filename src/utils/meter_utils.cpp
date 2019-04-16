#include "../inc/meter_utils.h"

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned int frac;
unsigned long oldTime;
float calibrationFactor = 4.5;
volatile byte pulseCount;

void meter_init() {
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;

  oldTime = 0;
}


int flowRateCalculater() {
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that has been passed since the last execution and use
    // that to scale the output. We also apply the calibration factor to scale the output
    // based on the number of pulses per second per units of measure (lit. / minute in
    // this case) coming from the sensor.
    flowRate = (( 1000.0 / ( millis () - oldTime)) * pulseCount) / calibrationFactor;

    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis () function will not actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis ();

    return (int)flowRate;        
}

/*
Routine Service Instance
 */
void pulseCounter () {
    // Increment the pulse counter
    pulseCount ++;
}

unsigned int flowMilliLitresCalculater() {
    // Divide the flow rate in litres / minute by 60 to determine how many liters have                     
    // passed through the sensor in this 1 second interval, then multiply by 1000 to                       
    // convert to millilitres.                                                                             
    flowMilliLitres = (flowRate / 60 ) * 1000 ; 

    return flowMilliLitres;
}

unsigned int totalMilliLitresCalculater() {
    // Add the milliliters passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
    return totalMilliLitres;
}

unsigned int fracCalculater() {
    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.                          
    frac = (flowRate - int (flowRate)) * 10 ;
    return frac;
}

unsigned int lastTime() {
    return oldTime;
}

void resetCounter() {
    pulseCount = 0;
}

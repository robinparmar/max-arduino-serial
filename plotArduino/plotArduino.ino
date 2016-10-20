/*
 * plotArduino
 * 
 * AUTHOR:
 * Robin Parmar
 * 
 * LICENSE
 * (c) 2015-6 Robin Parmar. GNU General Public License version 2.
 * 
 * DESCRIPTION:
 * Reads multiple analogue pins and sends data to serial port for graphing, etc.
 * 
 * CIRCUIT:
 * Sensors on analogue input pins 0, 1, 2.
 */

const int PINMAX = 3;       // total number of inputs
int reading = 0;            // sensor reading

void setup() {
    Serial.begin(57600);    // Max serial must be set to same value
    delay(2000);            // trick to avoid initial glitches
}

void loop() {
    // read all sensors in sequence
    for (int i=0; i<PINMAX; i++) {
        reading = analogRead(i);
        
        // output data to serial port
      	Serial.print(i+1);           // identify sensor
       	Serial.print(" ");           // delimiter
       	Serial.print(reading);       // data
       	Serial.println();            // line break bundles data
   }
}

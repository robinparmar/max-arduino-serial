/*
 * plotArduinoCalibrate
 * 
 * AUTHOR:
 * Robin Parmar
 * 
 * LICENSE
 * (c) 2015-6 Robin Parmar. GNU General Public License version 2.
 * 
 * DESCRIPTION:
 * Reads multiple analogue pins and sends data to serial port for graphing, etc.
 * Provides a calibration period of 10 seconds, within which sensors should
 * be given input over their expected opperational range of values.
 *
 * CIRCUIT:
 * Sensors on analogue input pins 0, 1, 2.
 * An LED on digital pin 13.
 * 
 */
 
const int PINMAX = 3;       // total number of inputs
const int LEDPIN = 13;		// pin for LED

int reading = 0;            // sensor reading

// initial values for calibration
int readMinimum[6] = {1023, 1023, 1023, 1023, 1023, 1023};   
int readMaximum[6] = {0, 0, 0, 0, 0, 0};   

void setup() {
    Serial.begin(57600);    // Max serial must be set to same value
    delay(2000);            // trick to avoid initial glitches
    calibrate();
}

void loop() {
    // read all sensors in sequence
    for (int i=0; i<PINMAX; i++) {
        reading = analogReadCalibrated(i);
        
        // output data to serial port
      	Serial.print(i+1);           // identify sensor
       	Serial.print(" ");           // delimiter
       	Serial.print(reading);       // data
       	Serial.println();            // line break bundles the data
   }
}

void calibrate() {
    // turn on LED to indicate calibration state
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, HIGH);

    // calibrate for 10 seconds
    long starter = millis();
    while (millis() - starter < 10000) {
        for (int i=0; i<PINMAX; i++) {
            reading = analogRead(i);
            
            if (reading > readMaximum[i]) { 
                readMaximum[i] = reading; 
            }
            if (reading < readMinimum[i]) { 
                readMinimum[i] = reading; 
            }
        }
    }

    // turn off LED
    digitalWrite(LEDPIN, LOW);
}

int analogReadCalibrated(int pin) {
    // read analogue pin and constrain to calibration limits
    reading = analogRead(pin);
    reading = map(reading, readMinimum[pin], readMaximum[pin], 0, 1023);
    reading = constrain(reading, 0, 1023);
    return reading;
}


/*
  pumpOn for 10 sec
  pumpOff for 60 sec

  sends a signal to a relais to turn on and off a vacuum pump
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.

  modified from 
  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay

  last update: BH 1807051500
*/

// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN; // the number of the LED pin //LED for control of function
const int signalPumpRelais = 13;  // output to the pump

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int defaultOff = 0;             // for start the programm initial wait for interval2 secs

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval1 = 10000;           // BH interval onTime
                    
const long interval2 = 60000;     // BH interval 60 sec offTime

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(signalPumpRelais, OUTPUT);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();
  if (defaultOff == 0) {
    //start process waiting for 60 interval2 secs
    if (currentMillis - previousMillis >= interval2) { 
      // after interval2 secs set defaultOff to 1
      previousMillis = currentMillis;
      defaultOff = 1;
    } else {
      if (ledState == LOW) { 
        // for the start set the led and the pump on for interval2 sec
        previousMillis = currentMillis;
        ledState = HIGH;
        digitalWrite(ledPin, ledState);
        digitalWrite(signalPumpRelais, ledState);
      }
    }
  } else { 
    //after the start interval2secs
    if (ledState == LOW) { 
      // wait interval2 sec and set ON
      if (currentMillis - previousMillis >= interval2) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        // if the LED is off turn it on and vice-versa:
        ledState = HIGH;
        digitalWrite(ledPin, ledState);
        digitalWrite(signalPumpRelais, ledState);
      }
    } else { 
      // wait interval1 secs and set OFF
      if (currentMillis - previousMillis >= interval1) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        // if the LED is off turn it on and vice-versa:
        ledState = LOW;
        digitalWrite(ledPin, ledState);
        digitalWrite(signalPumpRelais, ledState);}
      }
    }
  }

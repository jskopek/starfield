#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
#include <avr/power.h>
#endif


// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(2, dataPin, clockPin, WS2801_GRB);


// custom
uint32_t color;

void setup() {
  // setup code
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif

  // start listening on port 9600
  Serial.begin(9600);

  // initialize the first color
  color = Color(255, 0, 0);

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
}

void handleSerial() {
 while (Serial.available() > 0) {
   char incomingCharacter = Serial.read();
   switch (incomingCharacter) {
    case 'a':
      color = Color(255, 0, 0);
      break;
    case 'b':
      color = Color(0, 255, 0);
      break;
    case 'c':
      color = Color(0, 0, 255);
    }
 }
}

void loop() {
  colorWipe(color);
  handleSerial();
  Serial.println("completed a loop");
  delay(100);
}



/* Helper functions */

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
  }
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}


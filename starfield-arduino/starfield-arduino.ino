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
const byte numChars = 200;
char receivedChars[numChars];
boolean newData = false;
//char colorBuffer[300];
//int numLineChars;


void setup() {
// setup code
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

    // start listening on port
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
    
    // initialize the first color
    color = Color(0, 255, 255);

    strip.begin();

    // Update LED contents, to start they are all 'off'
    strip.show();

    // "I'm alive!" light sequence
    colorWipe(Color(255,0,0));
    delay(400);
    colorWipe(Color(0,255,0));
    delay(400);
    colorWipe(Color(0,0,255));
    delay(400);
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

void reactToData() {
    if (newData == true) {
      if(strcmp(receivedChars, "c") == 0) {
          color = Color(0, 0, 255);
          Serial.print("reactToData ... ");
          Serial.println(receivedChars);
      } else if(strcmp(receivedChars, "b") == 0) {
        color = Color(0, 255, 0);
      } else {
        color = Color(255, 0, 0);
      }
      
      
//      switch (receivedChars) {
//            case 'a':
//                color = Color(255, 0, 0);
//                break;
//            case 'b':
//                color = Color(0, 255, 0);
//                break;
//            case 'c':
//                color = Color(0, 0, 255);
//                Serial.print("Blablooopie ... ");
//        }
//        Serial.print("Blablooopie ... ");
//        Serial.println(receivedChars);
        newData = false;
    }
}

void loop() {
//    numLineChars = readline(Serial.read(), colorBuffer, 300);
//    if(numLineChars > 0) {
//      Serial.println(numLineChars);
//        Serial.print("You entered: >");
//        Serial.print(colorBuffer);
//        Serial.println("<");
//        Serial.print("Num Chars: >");
//        Serial.print(numLineChars);
//        Serial.println("<");
//    }


    recvWithStartEndMarkers();
    reactToData();
    //showNewData();



    colorWipe(color);
    //handleSerial();
    //Serial.println("completed a loop");
    //delay(10);
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


//int readline(int readch, char *buffer, int len) {
//    // source: https://majenko.co.uk/blog/reading-serial-arduino
//    static int pos = 0;
//    int rpos;
//
//    if (readch > 0) {
//        switch (readch) {
//            case '\r': // Ignore CR
//                break;
//            case '\n': // Return on new-line
//                rpos = pos;
//                pos = 0;  // Reset position index ready for next time
//                return rpos;
//            default:
//                if (pos < len-1) {
//                    buffer[pos++] = readch;
//                    buffer[pos] = 0;
//                }
//        }
//    }
//    return 0;
//}



void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        newData = false;
    }
}


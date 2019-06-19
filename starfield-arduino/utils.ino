void initializeEffect() {
    // "I'm alive!" light sequence
    colorWipe(Color(255,0,0));
    delay(400);
    colorWipe(Color(0,255,0));
    delay(400);
    colorWipe(Color(0,0,255));
    delay(400);
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
        newData = false;
    }
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


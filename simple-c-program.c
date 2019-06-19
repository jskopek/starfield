// C code to demonstrate practical application of 
// strtok 
#include <stdio.h> 
#include <string.h> 
#include <stdint.h>
#include <string.h>
#include <stdlib.h>



// Create a 24 bit color value from R,G,B
uint32_t Color(unsigned char r, unsigned char g, unsigned char b)
{
    uint32_t c;
    c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
    return c;
}



uint32_t stringToColor(char* red) {
    // takes a char* string with "int,int,int" format, where int is a number from 0-255
    // that represents red, green, and blue
    // returns a uint32_t color string
    const char ch = ',';
    char *green = strchr(red, ch);
    *green = 0; // split red from rest
    green++;


    char *blue = strchr(green, ch);
    *blue = 0; // split green from rest
    blue++;


    printf("Red: %s \n", red);
    printf("Green: %s \n", green);
    printf("Blue: %s \n", blue);
    printf("\n\n");

    uint32_t color = Color(atoi(red), atoi(green), atoi(blue)); 
}


  
// Driver function 
int main() 
{ 
    // Declaration of string 
    // Information to be converted into CSV file 
    char input[] = "100,200,40;99,98,97;1,2,3";
  
    // Declaration of delimeter 
    const char delimiter[4] = ";"; 
    char* lightData; 
  
    // Use of strtok 
    // get first token 
    lightData = strtok(input, delimiter); 
  
//    // Checks for delimeter 
//    while (lightData != 0) { 
//        printf("%s  \n", lightData); 
//        stringToColor(lightData);
//
//        // Use of strtok 
//        // go through other tokens 
//        lightData = strtok(0, delimiter); 
//    } 
  
    // Checks for delimeter 
        printf("%s  \n", lightData); 
        stringToColor(lightData);

        // Use of strtok 
        // go through other tokens 
 
    return (0); 
} 



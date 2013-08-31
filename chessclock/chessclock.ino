/*
Thanks to Rudi Imbrechts (http://arduinows.blogspot.nl/) for the initial example.
Aansturen FDS132 LED matrix bord m.b.v. SPI.  
*/  
#include <SPI.h>            // Om snelheid te winnen maken we gebruik van SPI.  
#include "fds132text.h"     

// Pinnen voor het aansturen van het FDS132 bord.  
int row;                    // int voor bijhouden welke rij we aansturen.  


fdsScreen mainScreen;

void setup() {   
   pinMode (strobePin, OUTPUT);                          // zet alle pinnen als output om de shift registers aan te sturen.  
   pinMode (clockPin, OUTPUT);  
   pinMode (dataPin, OUTPUT);  
   pinMode (row_c, OUTPUT);  
   pinMode (row_b, OUTPUT);  
   pinMode (row_a, OUTPUT);  
   pinMode (resredPin, OUTPUT);  
   digitalWrite (resredPin, HIGH);                       // resred werkt als een schakelaar. Hoog betekent display aan, laag is display uit.  
   digitalWrite (strobePin, LOW);                        // strobe pas hoog brengen als data naar het shiftregister is gestuurd.  
   SPI.begin();                                          // initialiseer de SPI library.  
   SPI.setBitOrder(MSBFIRST);                            // Most Significant Bit eerst (LSB geeft ieder karakter in spiegelbeeld weer). 
   initialiseLetters() ; // I haven't figured out the smart way to set all the letter variables to the value I want yet.
   mainScreen = fdsScreen("A BABBA RABBA I can't do all text", 0); // You can set this to any (C-style) string, but not all characters are defined
}  
void loop()  
{  
    fdsStringNode *maintext;
    
    maintext = mainScreen.first -> firstNode;
    for (row=0; row<7; row++)                            // rij teller.  
    {   
        digitalWrite(strobePin, LOW);                      // strobePin laag opdat de LEDs niet wijzigen als we de bits doorsturen.  
        digitalWrite (resredPin, LOW);                     // en we doven de display om ghosting te voorkomen.  
        setRow(row);                                       // we sturen alle zeven rijen aan.  
        //zeroDisplay();                                     // alle uitgangen van de shiftregisters op nul.  
        setDisplay(row, *maintext);                        // haal de te tonen data op.   
        digitalWrite(strobePin, HIGH);                     // update de shiftregisters.  
        digitalWrite (resredPin, HIGH);                    // en zet display terug aan.  
        delayMicroseconds(1000);                           // pauseren want de update gaat te vlug.   
    }
}  
void setRow (int row)                                  // deze functie kan gebruikt worden voor het multiplexen van de zeven rijen.  
{  
   digitalWrite (row_a, row & 1);                        // zet decimale waarden 0 tot 7 om naar binaire waarden (000 - 111)   
   digitalWrite (row_b, row & 2);                        // om de corresponderende rowpinnen die de matrixlijnen aansturen   
   digitalWrite (row_c, row & 4);                        // te activeren.  
}  
void zeroDisplay()                                     // deze functie zet alle uitgangen v/d shiftregisters op nul,  
{                                                      // waardoor alle LED's doven  
   int i;  
   for(i=0; i<34; i++)  
   {  
       SPI.transfer(0);                                     // door 34 keer een byte met waarde nul te sturen.  
   }  
}  


// Unpack the required row from the StringNode
void setDisplay(int row, fdsStringNode outputText)
{   
    int i = 0;
    int currentbit = 0; //The location (from 0 to 270) we are currently writing at.
    byte outputbytes[35]; //extra byte for safety, officially we only need 34, but I don't like buffer overflows
    for(i=0; i<34; i++)  
    {  
       outputbytes[i] = 0;
    }
    
    // unpack the fdsStringNode

    // first we create a pointer to the bit of the string we are converting into our output right now
    fdsStringNode *current = &outputText;
    // And we create a pointer to the Character object it is pointing to.
    fdsChar *currentValue = 0;
    byte b; //The bits that we are currently inserting into the array.
    while (true) {
        if (current == 0) {break;} // We should end if we have reached the end of the string (last stringnode)
        if (currentbit > fdsmaxlength) {break;} // We should end if we have reached the end of the screen

        // set b to the byte that cointains (at the end) the bits needed to display this part of the current character
        currentValue = (*current).value;
        b = currentValue -> character_map[row];

        // integer division in C always rounds down, so currentbit/8 gives us the right byte to write to
        // To this byte we want to add the bits in b, and not change the ones that are already there. 
        // Bitwise or "|" lets us do this
        // currentbit % 8 gives us a number from 0 to 7 indicating how many bits in the byte we have already used
        // So we want to shift b that many spaces to the left using <<
        outputbytes[currentbit/8] = outputbytes[currentbit/8] | (b << (currentbit % 8));

        // Now that last shift may have shifted some of the bits off the byte, so we need to put them on the next one.
        // if these bits exist, then shifting b to the right will give us exactly those bits, no more, and put them 
        // on the right side of the byte, just where we want them.
        outputbytes[(currentbit/8) + 1] = outputbytes[(currentbit/8) + 1] | (b >> (8 - (currentbit % 8)));
        // shift our address to the location for the next character
        currentbit += currentValue -> width;
        // and load our next character
        current = current -> next;
    }
    
    // Put the bytes on the display, last one first  (because the first one entered will be shifted to the end)
    for(i=34; i>=0; i--){
        SPI.transfer(outputbytes[i]);   
    };

}  

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
   initialiseLetters() ;
   mainScreen = fdsScreen("A BABBA RABBA", 0);
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
        zeroDisplay();                                     // alle uitgangen van de shiftregisters op nul.  
        setDisplay(row, *maintext);                                   // haal de te tonen data op.   
        digitalWrite(strobePin, HIGH);                     // update de shiftregisters.  
        digitalWrite (resredPin, HIGH);                    // en zet display terug aan.  
        delayMicroseconds(2000);                           // pauseren want de update gaat te vlug.   
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

void setDisplay(int row, fdsStringNode outputText)                               // haal de tekstdata uit de eerder gedefinieerde map met karakters.  
{   
    int i = 0;
    int currentbit = 0;
    byte outputbytes[35]; //extra byte for safety
    for(i=0; i<34; i++)  
    {  
       outputbytes[i] = 0;
    }
    
    // unpack the fdsStringNode
    fdsStringNode *current = &outputText;
    fdsChar *currentValue = 0;
    byte b;
    while (true) {
        if (current == 0) {break;}
        if (currentbit > fdsmaxlength) {break;}
        currentValue = (*current).value;
        b = currentValue -> character_map[row];
        b = b << (currentbit % 8);
        outputbytes[currentbit/8] = outputbytes[currentbit/8] | b;

        b = currentValue -> character_map[row];
        b = b >> (8 - (currentbit % 8));

        outputbytes[(currentbit/8) + 1] = outputbytes[(currentbit/8) + 1] | b;
        currentbit += currentValue -> width;
        current = current -> next;
    }
    
    for(i=34; i>=0; i--){
        SPI.transfer(outputbytes[i]);   
    };

}  

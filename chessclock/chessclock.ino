/*
Thanks to Rudi Imbrechts (http://arduinows.blogspot.nl/) for the initial example.
Aansturen FDS132 LED matrix bord m.b.v. SPI.  
*/  
#include <SPI.h>            // Om snelheid te winnen maken we gebruik van SPI.  
#include "fds132text.h"     



fdsScreen mainScreen = fdsScreen("abcdefghijklmnopq  rstuvwxyz123456 7890.,!:", 0);

void setup() {   
    pinMode (strobePin, OUTPUT); // zet alle pinnen als output om de shift registers aan te sturen.  
    pinMode (clockPin, OUTPUT);  
    pinMode (dataPin, OUTPUT);  
    pinMode (row_c, OUTPUT);  
    pinMode (row_b, OUTPUT);  
    pinMode (row_a, OUTPUT);  
    pinMode (resredPin, OUTPUT);  
    digitalWrite (resredPin, HIGH);// resred werkt als een schakelaar. Hoog betekent display aan, laag is display uit.  
    digitalWrite (strobePin, LOW); // strobe pas hoog brengen als data naar het shiftregister is gestuurd.  
    SPI.begin();  // start the SPI library
    SPI.setBitOrder(MSBFIRST);  //Code was written for this 
    initialiseLetters() ; // I haven't figured out the smart way to set all the letter variables to the value I want yet.
    mainScreen.update();
}  
void loop()  
{  
    for (int row=0; row<7; row++)                            // rij teller.  
    {   
        digitalWrite(strobePin, LOW);                      // strobePin laag opdat de LEDs niet wijzigen als we de bits doorsturen.  
        digitalWrite (resredPin, LOW);                     // en we doven de display om ghosting te voorkomen.  
        setRow(row);                                       // we sturen alle zeven rijen aan.  
        for(int i=34; i>=0; i--){
            SPI.transfer(mainScreen.output[row][i]);   
        };
        digitalWrite(strobePin, HIGH);                     // update de shiftregisters.  
        digitalWrite (resredPin, HIGH);                    // en zet display terug aan.  
        delayMicroseconds(2500);                           // pauseren want de update gaat te vlug.   
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


/*
Thanks to Rudi Imbrechts (http://arduinows.blogspot.nl/) for the initial example.
Aansturen FDS132 LED matrix bord m.b.v. SPI.  
Toont karakters op line 0.  
*/  
#include <SPI.h>            // Om snelheid te winnen maken we gebruik van SPI.  
#include "fds132text.h"     

// Pinnen voor het aansturen van het FDS132 bord.  
const int strobePin = 10;   // pin voor strobe signaal, ook wel latch genaamd.  
const int clockPin = 13;    // pin met clock signaal.  
const int dataPin = 11;     // pin voor het serieel sturen van data.  
const int resredPin = 9;    // resred, ook wel OutputEnable of OE genoemd.  
const int row_a = 5;        // ieder ledmatrix heeft 7 rijen. Hardwarematig   
const int row_b = 6;        // gebruiken we een 3-naar-8 decoder  
const int row_c = 7;        // type 74HC238 (U4 op het schema).  
int row;                    // int voor bijhouden welke rij we aansturen.  

const int maxlength = 270;

fdsChar letterA;
fdsChar letterB;
fdsChar letterR;
fdsChar fdsColon;
fdsChar fdsSpace;
fdsString maintext;

void initialiseLetters(){
    letterA.character_map[0]=B00001100;
    letterA.character_map[1]=B00010010; 
    letterA.character_map[2]=B00010010; 
    letterA.character_map[3]=B00011110; 
    letterA.character_map[4]=B00010010; 
    letterA.character_map[5]=B00100001; 
    letterA.character_map[6]=B00100001;
    letterA.width=6;

    letterB.character_map[0]=B00000111;
    letterB.character_map[1]=B00001001; 
    letterB.character_map[2]=B00001001; 
    letterB.character_map[3]=B00000111; 
    letterB.character_map[4]=B00001001; 
    letterB.character_map[5]=B00001001; 
    letterB.character_map[6]=B00000111;
    letterB.width=4;

    letterR.character_map[0]=B00000111;
    letterR.character_map[1]=B00001001; 
    letterR.character_map[2]=B00001001; 
    letterR.character_map[3]=B00000111; 
    letterR.character_map[4]=B00001001; 
    letterR.character_map[5]=B00010001; 
    letterR.character_map[6]=B00100001;
    letterR.width=6;

    fdsColon.character_map[0]=B00000000;
    fdsColon.character_map[1]=B00000000;
    fdsColon.character_map[2]=B00000001;
    fdsColon.character_map[3]=B00000000;
    fdsColon.character_map[4]=B00000001;
    fdsColon.character_map[5]=B00000000;
    fdsColon.character_map[6]=B00000000;
    fdsColon.width=1;

    fdsSpace.width=1;
    
    maintext.value = &letterB;
    maintext.rest = 0;
    
    addToStringNoSpace(&maintext, &fdsSpace);
    addToString(&maintext, &letterA);
    addToString(&maintext, &letterR);
    addToString(&maintext, &fdsColon);
    addToString(&maintext, &letterA);
}

void addToStringNoSpace(fdsString *string, fdsChar *addition){
    //find end of string
    while(string -> rest != 0) {
        string = string -> rest; 
    }
    //add the new character
    string -> rest = (fdsString *) malloc(sizeof(struct fdsString));
    string = string -> rest;
    string -> value = addition;
    string -> rest = 0;
}

void addToString(fdsString *string, fdsChar *addition){
    addToStringNoSpace(string, addition);
    addToStringNoSpace(string, &fdsSpace);
}

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
}  
void loop()  
{  
    for (row=0; row<7; row++)                            // rij teller.  
    {   
        digitalWrite(strobePin, LOW);                      // strobePin laag opdat de LEDs niet wijzigen als we de bits doorsturen.  
        digitalWrite (resredPin, LOW);                     // en we doven de display om ghosting te voorkomen.  
        setRow(row);                                       // we sturen alle zeven rijen aan.  
        zeroDisplay();                                     // alle uitgangen van de shiftregisters op nul.  
        setDisplay(row, maintext);                                   // haal de te tonen data op.   
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
void setDisplay(int row, fdsString outputText)                               // haal de tekstdata uit de eerder gedefinieerde map met karakters.  
{   
    int i = 0;
    int currentbit = 0;
    byte outputbytes[35]; //extra byte for safety
    for(i=0; i<34; i++)  
    {  
       outputbytes[i] = 0;
    }
    
    // unpack the fdsString
    fdsString *current = &outputText;
    fdsChar *currentValue = 0;
    byte b;
    while (true) {
        if (current == 0) {break;}
        if (currentbit > maxlength) {break;}
        currentValue = (*current).value;
        b = currentValue -> character_map[row];
        b = b << (currentbit % 8);
        outputbytes[currentbit/8] = outputbytes[currentbit/8] | b;

        b = currentValue -> character_map[row];
        b = b >> (8 - (currentbit % 8));

        outputbytes[(currentbit/8) + 1] = outputbytes[(currentbit/8) + 1] | b;
        currentbit += currentValue -> width;
        current = current -> rest;
    }
    
    for(i=34; i>=0; i--){
        SPI.transfer(outputbytes[i]);   
    };

}  

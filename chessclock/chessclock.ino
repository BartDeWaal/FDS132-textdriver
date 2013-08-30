/*
Thanks to Rudi Imbrechts (http://arduinows.blogspot.nl/) for the initial example.
Aansturen FDS132 LED matrix bord m.b.v. SPI.  
Toont karakters op line 0.  
*/  
#include <SPI.h>                                       // Om snelheid te winnen maken we gebruik van SPI.  
                                                       // Daarom halen we de SPI library erbij.  
                                                       // Pinnen voor het aansturen van het FDS132 bord.  
const int strobePin = 10;                              // pin voor strobe signaal, ook wel latch genaamd.  
const int clockPin = 13;                               // pin met clock signaal.  
const int dataPin = 11;                                // pin voor het serieel sturen van data.  
const int resredPin = 9;                               // resred, ook wel OutputEnable of OE genoemd.  
const int row_a = 5;                                   // ieder ledmatrix heeft 7 rijen. Hardwarematig   
const int row_b = 6;                                   // gebruiken we een 3-naar-8 decoder  
const int row_c = 7;                                   // type 74HC238 (U4 op het schema).  
const int zero = 0;                                    // nul, zero, nada.  
int row;                                               // int voor bijhouden welke rij we aansturen.  
unsigned char character_map[8][7] = {                  // map met de letters die we gaan gebruiken. 8 karakters, zeven rijen elks  
0x0E,0x11,0x11,0x1F,0x11,0x11,0x11,                    // geef me een A
0x0F,0x11,0x11,0x0F,0x05,0x09,0x11,                    // en een R , enzovoort
0x07,0x09,0x11,0x11,0x11,0x11,0x0F,                    // D  
0x11,0x11,0x11,0x11,0x11,0x11,0x0E,                    // U  
0x1F,0x04,0x04,0x04,0x04,0x04,0x1F,                    // I  
0x11,0x13,0x15,0x19,0x11,0x11,0x11,                    // N  
0x0E,0x11,0x11,0x11,0x11,0x11,0x0E,                    // O  
0x04,0x04,0x04,0x04,0x04,0x00,0x04,                    // !  
};  
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
}  
void loop()  
{  
    for (row=0; row<7; row++)                            // rij teller.  
    {   
        digitalWrite(strobePin, LOW);                      // strobePin laag opdat de LEDs niet wijzigen als we de bits doorsturen.  
        digitalWrite (resredPin, LOW);                     // en we doven de display om ghosting te voorkomen.  
        setRow(row);                                       // we sturen alle zeven rijen aan.  
        zeroDisplay();                                     // alle uitgangen van de shiftregisters op nul.  
        setDisplay(row);                                   // haal de te tonen data op.   
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
void setDisplay(int row)                               // haal de tekstdata uit de eerder gedefinieerde map met karakters.  
{  
    SPI.transfer(character_map[7][row]<<1);               // '!'  
    SPI.transfer(character_map[6][row]<<1);               // 'O'  
    SPI.transfer(character_map[5][row]<<1);               // 'N'  
    SPI.transfer(character_map[4][row]<<1);               // 'I'  
    SPI.transfer(character_map[3][row]<<1);               // 'U'  
    SPI.transfer(character_map[2][row]<<1);               // 'D'  
    SPI.transfer(character_map[1][row]<<1);               // 'R'  
    SPI.transfer(character_map[0][row]<<1);               // 'A'  
}  
 /*  Over het FDS132 LED matrixbord:
 Het bord bestaat uit 3 lijnen van 18 LED matrixes met elk 5*7 LEDs.  
  █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ line 0  
  █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ line 1  
  █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ line 2  
 De 7 rijen (row 0 t/m 6) kunnen individueel worden aan/uit gestuurd.  
     █ = 1 LEDMATRIX.   
     oooooooo <- row 0  
     oooooooo <- row 1  
     oooooooo <- row 2  
     oooooooo <- row 3  
     oooooooo <- row 4  
     oooooooo <- row 5  
     oooooooo <- row 6  
     ^......^  
     |      |___ deze LED correspondeert met Least Significant Bit, LSB  
     |__________ deze met Most Significant Bit, MSB  
 De 3*18*5 = 270 kolommen worden door 34 shiftregisters type 74HC4094 aangestuurd (8 bits per register).  
 Het laatste shifregister stuurt slechts 6 ipv 8 kolommen (33 shiftregisters*8) + 6 = 270.  
 */  

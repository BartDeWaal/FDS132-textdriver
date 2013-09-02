/*
Thanks to Rudi Imbrechts (http://arduinows.blogspot.nl/) for the initial example.
Aansturen FDS132 LED matrix bord m.b.v. SPI.  
*/  
#include <SPI.h>            // Om snelheid te winnen maken we gebruik van SPI.  
#include "fds132text.h"     

fdsScreen mainScreen;
fdsString *changeThisString;

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
    mainScreen.addString("I love the arduino",0);
    changeThisString = mainScreen.addString("a lot",90);
    mainScreen.addString("-- Bart",225);
    mainScreen.update();
}  
void loop()  
{  
    mainScreen.display();
    if (millis()>10000){
        changeThisString -> set("More then ever");
        mainScreen.update();

    }   
}  


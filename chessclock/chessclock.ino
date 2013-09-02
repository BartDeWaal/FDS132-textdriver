/*
Thanks to Rudi Imbrechts (http://arduinows.blogspot.nl/) for the initial example.
*/  
#include "fds132text.h"     
#include <SPI.h>  //for some reason it only works if you include it here

fdsScreen mainScreen;
fdsString *changeThisString;

fdsChar mySmiley;
void setup() {   
    mainScreen.setPins(); // Uses the default from Rudi Imbrechts guide on how to set up the pins.
                          // You can set diffent pins, see fds132text.h for the arguments
    initialiseLetters() ; // I haven't figured out the smart way to set all the letter variables to the value I want yet.

    mainScreen.addString("I love the arduino",0); // Add a string beginning at address 0 (the start of the screen)
    changeThisString = mainScreen.addString("a lot",90); // This one will start at the start of line 2
    mainScreen.addString("-- Bart",225); // And this halfway through the third line

    //We also want a smiley
    // We already declared mySmiley globally, so it wouldn't cease to exist after the setup is gone
    // We can define it visually, and it helps if your editor lets you highlight 1
    // Note that the character starts at the left, you have to enter the mirror image
    mySmiley.character_map[0]=B00000000;
    mySmiley.character_map[1]=B00100010; 
    mySmiley.character_map[2]=B00000000; 
    mySmiley.character_map[3]=B01001001; 
    mySmiley.character_map[4]=B00100010; 
    mySmiley.character_map[5]=B00011100; 
    mySmiley.character_map[6]=B00000000;
    mySmiley.width=7;


    mainScreen.addString(&mySmiley,155); //We have to pass the address of mySmiley

    mainScreen.update();
}  
void loop()  
{  
    mainScreen.display();
    if (millis()>10000){
        changeThisString -> set("More then ever");
        mainScreen.update(); // if you don't update no new output buffer is calculated

    }   
}  


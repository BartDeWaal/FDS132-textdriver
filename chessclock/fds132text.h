#ifndef __FDS132_text_class__
#define __FDS132_text_class__
#include <SPI.h> 

const int strobePin = 10;   // pin voor strobe signaal, ook wel latch genaamd.  
const int clockPin = 13;    // pin met clock signaal.  
const int dataPin = 11;     // pin voor het serieel sturen van data.  
const int resredPin = 9;    // resred, ook wel OutputEnable of OE genoemd.  
const int row_a = 5;        // ieder ledmatrix heeft 7 rijen. Hardwarematig   
const int row_b = 6;        // gebruiken we een 3-naar-8 decoder  
const int row_c = 7;        // type 74HC238 (U4 op het schema).  

// This is a character that our output function can use to write.
// It has every row encoded in a byte, and we record the width of the byte
// The width is inluding a space
// This class class can not only be used for characters, but for all images 
// you want to display on the FDS132
class fdsChar {
    public:
        byte character_map[7];
        int width; //up to 8
        // If you want characters wider than 8 you should combine two differnt characters
};


// This is the building block for our strings
// If you don't understand look up a linked list
class fdsStringNode {
    public:
        fdsStringNode* set(char *value);
        void setEnd(); // Use this function to make this node the last
        // It will free all further nodes
        fdsChar *value;
        fdsStringNode *next;
};

// This is the container for the stringNodes, allowing us faster access to the last node
// and in the future to position multiple strings at different points on the board
class fdsString {
    public:
        void set(char value[]); // this will write/overwrite the string contained in this holder
        fdsStringNode *firstNode;
        fdsStringNode *lastNode;
        int startLocation; // The starting address on the board
        fdsString * next;
};


const int fdsmaxlength = 270;

// Holds the whole screen. In the future it will also manage output to the screen
class fdsScreen {
    public:
        fdsScreen(char initialValue[], int position);
        void update();
        int maxlength;
        fdsString *first;
        byte output[7][35];

};

// Helper functions that don't have a better place yet.
void initialiseLetters();
fdsChar* charTofdsChar(char value);

#endif

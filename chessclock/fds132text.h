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

class fdsChar {
    public:
    byte character_map[7];
    int width; //up to 8
};

class fdsStringNode {
    public:
        fdsStringNode* set(char *value);
        void setEnd();
    fdsChar *value;
    fdsStringNode *next;
};

class fdsString {
    public:
        void set(char value[]);
        fdsStringNode *firstNode;
        fdsStringNode *lastNode;
        int startLocation;
        fdsString * next;
};


const int fdsmaxlength = 270;

class fdsScreen {
    public:
        fdsScreen();
        fdsScreen(char initialValue[], int position);
        int maxlength;
        fdsString *first;
        byte output[35];

};

void initialiseLetters();
fdsChar* charTofdsChar(char value);

#endif

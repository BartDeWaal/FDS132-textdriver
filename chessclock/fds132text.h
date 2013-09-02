#ifndef __FDS132_text_class__
#define __FDS132_text_class__
#include <SPI.h> 
#include "font.h"

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
        int nextStart(); // Return the startpoint of the next string, if applicable
        fdsStringNode *firstNode;
        fdsStringNode *lastNode;
        int startLocation; // The starting address on the board
        fdsString * next;
};


// Holds the whole screen, and manages the output
class fdsScreen {
    private:
        fdsString *first; // The first string, it has a pointer to the next one
        void setRow(int row);
        void updateFromfdsStringNode(fdsStringNode *current, int currentbit, int endbit);
        int strobePin;   
        int clockPin;    
        int dataPin;     
        int resredPin;    // resred, AKA OutputEnable or OE.  
        int row_a;        // Every ledmatrix has 7 rows. 
        int row_b;        // The hardware used a 3-to-8 encoder
        int row_c;        // type 74HC238 (U4 in the scematics).  
        int delay;
    public:
        fdsScreen(); //constructor
        // Add a string at position. initialValue is a C-type string that
        //will be set
        fdsString* addString(char initialValue[], int position); 
        fdsString* addString(fdsChar * value, int position); 
        // Set the pins using the default values (and do some other initialisation stuff)
        void setPins();
        // Set the pins using custom values
        void setPins(int p_strobePin, int p_clockPin, int p_dataPin, int p_row_c, int p_row_b, int p_row_a, int p_resredPin, int p_delay);
        // If you have changed the text of one of the strings, you need to update it before it will get displayed
        void update();
        // Make the display empty. This does not empty the strings and will be undone as soon as update() is called
        void zeroDisplay(); 
        // output to the physical display
        void display();
        // The output that will be displayed
        byte output[7][35];

};
#endif

#include "fds132text.h"

fdsScreen::fdsScreen(){
    first = NULL; //make sure it's a null pointer
}

void fdsScreen::setPins(){
    // using the defaults from the example setup
    setPins(10,13,11,7,6,5,9,2000);
}

void fdsScreen::setPins(int p_strobePin, int p_clockPin, int p_dataPin, int p_row_c, int p_row_b, int p_row_a, int p_resredPin, int p_delay){
    strobePin = p_strobePin;
    clockPin  = p_clockPin;
    dataPin = p_dataPin;  
    resredPin = p_resredPin;
    row_a = p_row_a;
    row_b = p_row_b;
    row_c = p_row_c;
    delay = p_delay;
    pinMode (strobePin, OUTPUT); 
    pinMode (clockPin, OUTPUT);  
    pinMode (dataPin, OUTPUT);  
    pinMode (row_c, OUTPUT);  
    pinMode (row_b, OUTPUT);  
    pinMode (row_a, OUTPUT);  
    pinMode (resredPin, OUTPUT);  
    digitalWrite (resredPin, HIGH);
    digitalWrite (strobePin, LOW); 
    SPI.begin();  // start the SPI library
    SPI.setBitOrder(MSBFIRST);  //Code was written for this bit Order
}

// Takes a C-style string and puts it in the list of fdsStrings
fdsString* fdsScreen::addString(char initialValue[], int position) {
    fdsString* newString;
    newString = (fdsString*) malloc(sizeof(class fdsString));
    newString -> startLocation = position;

    placeString(newString);

    newString -> firstNode = 0;
    newString -> set(initialValue);
    return newString;
}

// Takes a fdsChar and puts it in the list of fdsStrings
fdsString* fdsScreen::addString(fdsChar *value, int position) {
    fdsString* newString;
    newString = (fdsString*) malloc(sizeof(class fdsString));
    newString -> startLocation = position;

    placeString(newString);

    newString -> firstNode = 0;
    newString -> set(value);
    return newString;
}

// Place the string in the right location
void fdsScreen::placeString(fdsString* theString) {
    int position = theString -> startLocation;

    if (first == 0){ //if there is no string yet
        first = theString;
        theString -> next = 0;
    }
    else { // If there is already a string
        fdsString* stringNavigator = first;

        // Find the place where the string should be, as the strings should be ordered by position
        while((stringNavigator -> next != 0)  //The loop should quit if there is no next item, in which case theString should be last
                && (((stringNavigator -> next) -> startLocation) < position)) // also if the next item has a bigger start position, 
                                                                              // so we found the right position
        { 
            stringNavigator = stringNavigator -> next;
        }

        theString -> next = stringNavigator -> next;
        stringNavigator -> next = theString;
    }
}

// Set this string to the C-style string supplied
// If there is already a string it will be overwritten
void fdsString::set(char value[]){
    if (firstNode == 0) { // If there is no string make a node for the fist character
        firstNode = (fdsStringNode*) malloc(sizeof(fdsStringNode));
        firstNode -> next = 0;
    }

    lastNode = firstNode -> set(value);

}

// Set a string to a character
void fdsString::set(fdsChar *value){
    if (firstNode == 0) { // If there is no string make a node for the fist character
        firstNode = (fdsStringNode*) malloc(sizeof(fdsStringNode));
        firstNode -> next = 0;
    }

    lastNode = firstNode -> set(value);

}

// Outputs the point where this string should stop displaying.
// Either the end of the screen or the start of the next string
int fdsString::nextStart(){
    if (next == 0){
        return 271;
    }

    return (next -> startLocation);

}

// Chage the output array to what's currently in the strings
void fdsScreen::update() {
    fdsString *current = first; // pointer to the string we are converting into our output right now

    //clear the output
    memset(output, 0, sizeof(output[0][0]) * 35 * 7);

    while (current != 0){ // if we still have at least one string to go
        // put it on the buffer starting at it's start
        updateFromfdsStringNode(current -> firstNode, current -> startLocation, current -> nextStart());
        current = current -> next;
    }


}

void fdsScreen::updateFromfdsStringNode(fdsStringNode *current, int currentbit, int endbit){
    fdsChar *currentValue = 0; // Pointer to the Character object current is pointing to.
    byte b; //The bits that we are currently inserting into the array.
    while (true) {
        if (current == 0) {break;} // We should end if we have reached the end of the string (last stringnode)
        if (currentbit > endbit) {break;} // We should end if we have reached the end of the bit

        // set b to the byte that cointains (at the end) the bits needed to display this part of the current character
        currentValue = (*current).value;
        for (int row = 0; row < 7; row++){
            b = currentValue -> character_map[row];

            // integer division in C always rounds down, so currentbit/8 gives us the right byte to write to
            // To this byte we want to add the bits in b, and not change the ones that are already there. 
            // Bitwise or "|" lets us do this
            // currentbit % 8 gives us a number from 0 to 7 indicating how many bits in the byte we have already used
            // So we want to shift b that many spaces to the left using <<
            output[row][currentbit/8] = output[row][currentbit/8] | (b << (currentbit % 8));

            // Now that last shift may have shifted some of the bits off the byte, so we need to put them on the next one.
            // if these bits exist, then shifting b to the right will give us exactly those bits, no more, and put them 
            // on the right side of the byte, just where we want them.
            output[row][(currentbit/8) + 1] = output[row][(currentbit/8) + 1] | (b >> (8 - (currentbit % 8)));
        }
        // shift our address to the location for the next character
        currentbit += currentValue -> width;
        // and load our next character
        current = current -> next;
    }
    // clean up what is left over after the endbit
    for (int row = 0; row < 7; row++){
        // Make sure the byte after the endbit is empty
        output[row][(endbit/8)+1] = 0;
        output[row][endbit/8] = output[row][endbit/8] & (B11111111 >> (8 - (endbit % 8)));
    
    }


}

void fdsScreen::zeroDisplay() //Clear the display
{                           
    for(int i=0; i<34; i++)  
    {  
        SPI.transfer(0);    
    }  
}  

void fdsScreen::display() //Display the current fdsScreen::output array
{                           
    for (int row=0; row<7; row++) // The screen can only display one line at a time,
                                  // We can make it look like it can write them all by writing quickly
                 
    {   
        digitalWrite(strobePin, LOW);    // strobePin LOW so the LEDs don't change when we send the bits.
        digitalWrite (resredPin, LOW);   // dim the display to prevent ghosting.  
        setRow(row);
        for(int i=34; i>=0; i--){
            SPI.transfer(output[row][i]);
        };
        digitalWrite(strobePin, HIGH);   // update the shiftregisters.  
        digitalWrite (resredPin, HIGH);  // turn the display back on.  
        delayMicroseconds(delay);         // pause, because otherwise it will update too quickly
    }

}  

// The LED screen only shows 1 (out of 7) rows at a time. This activates the row
// (The full screen is shown by quickly alternating between these)
void fdsScreen::setRow (int row)
{  
    digitalWrite (row_a, row & 1);
    digitalWrite (row_b, row & 2);
    digitalWrite (row_c, row & 4);
}  

// Set the value of this node to the first character in the array
// Then do the rest of the nodes recursively
fdsStringNode* fdsStringNode::set(char *newValue){
    value = charTofdsChar(*newValue);

    if (*(newValue + sizeof(char))==0) { // C-strings are null teminated. If the next character is 0 this
                                         // is the end of the string.
        setEnd();
        return this;
    }
    if (next == NULL){ // make more memory availible for the next bit of the string
        next = (fdsStringNode*) malloc(sizeof(fdsStringNode));
        next -> next = NULL;
    }
    return next -> set(newValue + sizeof(char));
}

// Set a node to a character, and make that node the last one
fdsStringNode* fdsStringNode::set(fdsChar *newValue){
    value = newValue;

    //We know it's only one value long, so we can just end it here
    setEnd();
    return this;
}

// Free the memory used by the rest of the string and NULL the pointer
void fdsStringNode::setEnd(){
    if (next == NULL){
        return;
    }

    next -> setEnd();
    free(next);
    next = NULL;

}


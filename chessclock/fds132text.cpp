#include "fds132text.h"

// Takes a C-style string and puts it in a first string
fdsScreen::fdsScreen(char initialValue[], int position) {
    maxlength = 270;
    first = (fdsString*) malloc(sizeof(class fdsString));
    first -> startLocation = position;
    first -> firstNode = 0;
    first -> set(initialValue);
    update();
}

// Set this string to the C-style string supplied
void fdsString::set(char value[]){
    if (firstNode == 0) {
        firstNode = (fdsStringNode*) malloc(sizeof(fdsStringNode));
        firstNode -> next = 0;
    }

    lastNode = firstNode -> set(value);

}

void fdsScreen::update() {
    int currentbit = 0; //The location (from 0 to 270) we are currently writing at.
    int row; //The row we are currently writing at
    fdsStringNode *current = first -> firstNode; // pointer to the bit of the string we are converting into our output right now
    fdsChar *currentValue = 0; // Pointer to the Character object current is pointing to.
    byte b; //The bits that we are currently inserting into the array.


    //clear the output
    memset(output, 0, sizeof(output[0][0]) * 35 * 7);

    while (true) {
        if (current == 0) {break;} // We should end if we have reached the end of the string (last stringnode)
        if (currentbit > fdsmaxlength) {break;} // We should end if we have reached the end of the screen

        // set b to the byte that cointains (at the end) the bits needed to display this part of the current character
        currentValue = (*current).value;
        for (row = 0; row < 7; row++){
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
}
void fdsScreen::zeroDisplay() //Clear the display
{                           
    for(int i=0; i<34; i++)  
    {  
        SPI.transfer(0);    
    }  
}  

void fdsScreen::display() //Display the current string
{                           
    for (int row=0; row<7; row++)                            // rij teller.  
    {   
        digitalWrite(strobePin, LOW);                      // strobePin laag opdat de LEDs niet wijzigen als we de bits doorsturen.  
        digitalWrite (resredPin, LOW);                     // en we doven de display om ghosting te voorkomen.  
        setRow(row);                                       // we sturen alle zeven rijen aan.  
        for(int i=34; i>=0; i--){
            SPI.transfer(output[row][i]);   
        };
        digitalWrite(strobePin, HIGH);                     // update de shiftregisters.  
        digitalWrite (resredPin, HIGH);                    // en zet display terug aan.  
        delayMicroseconds(2500);                           // pauseren want de update gaat te vlug.   
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

// Set the value of this nodo to the first character in the arrayy
// Then do the rest of the nodes recursively
fdsStringNode* fdsStringNode::set(char *newValue){
    value = charTofdsChar(*newValue);

    if (*(newValue + sizeof(char))==0) {
        setEnd();
        return this;
    }
    if (next == 0){
        next = (fdsStringNode*) malloc(sizeof(fdsStringNode));
        next -> next = 0;
    }
    return next -> set(newValue + sizeof(char));
}

void fdsStringNode::setEnd(){

}


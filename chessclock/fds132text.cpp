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

fdsChar fdsCharA;
fdsChar fdsCharB;
fdsChar fdsCharC;
fdsChar fdsCharE;
fdsChar fdsCharF;
fdsChar fdsCharH;
fdsChar fdsCharI;
fdsChar fdsCharK;
fdsChar fdsCharL;
fdsChar fdsCharM;
fdsChar fdsCharP;
fdsChar fdsCharR;
fdsChar fdsCharS;
fdsChar fdsCharT;
fdsChar fdsCharU;
fdsChar fdsCharColon;
fdsChar fdsCharBang;
fdsChar fdsCharSpace;
fdsChar fdsCharComma;
fdsChar fdsCharSingleQuote;
fdsChar fdsCharUnknown;

void initialiseLetters(){
    //include the seperating space
    // These things are easy to edit if you set your editor to highlight 1
    // In vim I do "/1" to search for 1 and ":set hlsearch" to highlight it
    fdsCharA.character_map[0]=B00000110;
    fdsCharA.character_map[1]=B00001001; 
    fdsCharA.character_map[2]=B00001001; 
    fdsCharA.character_map[3]=B00001111; 
    fdsCharA.character_map[4]=B00001001; 
    fdsCharA.character_map[5]=B00001001; 
    fdsCharA.character_map[6]=B00001001;
    fdsCharA.width=5;

    fdsCharB.character_map[0]=B00000111;
    fdsCharB.character_map[1]=B00001001; 
    fdsCharB.character_map[2]=B00001001; 
    fdsCharB.character_map[3]=B00000111; 
    fdsCharB.character_map[4]=B00001001; 
    fdsCharB.character_map[5]=B00001001; 
    fdsCharB.character_map[6]=B00000111;
    fdsCharB.width=5;

    fdsCharC.character_map[0]=B00000110;
    fdsCharC.character_map[1]=B00001001; 
    fdsCharC.character_map[2]=B00000001; 
    fdsCharC.character_map[3]=B00000001; 
    fdsCharC.character_map[4]=B00000001; 
    fdsCharC.character_map[5]=B00001001; 
    fdsCharC.character_map[6]=B00000110;
    fdsCharC.width=5;

    fdsCharE.character_map[0]=B00000111;
    fdsCharE.character_map[1]=B00000001; 
    fdsCharE.character_map[2]=B00000001; 
    fdsCharE.character_map[3]=B00000111; 
    fdsCharE.character_map[4]=B00000001; 
    fdsCharE.character_map[5]=B00000001; 
    fdsCharE.character_map[6]=B00000111;
    fdsCharE.width=4;

    fdsCharF.character_map[0]=B00000111;
    fdsCharF.character_map[1]=B00000001; 
    fdsCharF.character_map[2]=B00000001; 
    fdsCharF.character_map[3]=B00000111; 
    fdsCharF.character_map[4]=B00000001; 
    fdsCharF.character_map[5]=B00000001; 
    fdsCharF.character_map[6]=B00000001;
    fdsCharF.width=4;

    fdsCharH.character_map[0]=B00001001;
    fdsCharH.character_map[1]=B00001001; 
    fdsCharH.character_map[2]=B00001001; 
    fdsCharH.character_map[3]=B00001111; 
    fdsCharH.character_map[4]=B00001001; 
    fdsCharH.character_map[5]=B00001001; 
    fdsCharH.character_map[6]=B00001001;
    fdsCharH.width=5;

    fdsCharI.character_map[0]=B00000111;
    fdsCharI.character_map[1]=B00000010; 
    fdsCharI.character_map[2]=B00000010; 
    fdsCharI.character_map[3]=B00000010; 
    fdsCharI.character_map[4]=B00000010; 
    fdsCharI.character_map[5]=B00000010; 
    fdsCharI.character_map[6]=B00000111;
    fdsCharI.width=4;

    fdsCharK.character_map[0]=B00001001;
    fdsCharK.character_map[1]=B00001001; 
    fdsCharK.character_map[2]=B00000101; 
    fdsCharK.character_map[3]=B00000011; 
    fdsCharK.character_map[4]=B00000101; 
    fdsCharK.character_map[5]=B00001001; 
    fdsCharK.character_map[6]=B00001001;
    fdsCharK.width=5;

    fdsCharL.character_map[0]=B00000001;
    fdsCharL.character_map[1]=B00000001; 
    fdsCharL.character_map[2]=B00000001; 
    fdsCharL.character_map[3]=B00000001; 
    fdsCharL.character_map[4]=B00000001; 
    fdsCharL.character_map[5]=B00000001; 
    fdsCharL.character_map[6]=B00000111;
    fdsCharL.width=4;

    fdsCharM.character_map[0]=B00010001;
    fdsCharM.character_map[1]=B00011011; 
    fdsCharM.character_map[2]=B00010101; 
    fdsCharM.character_map[3]=B00010101; 
    fdsCharM.character_map[4]=B00010001; 
    fdsCharM.character_map[5]=B00010001; 
    fdsCharM.character_map[6]=B00010001;
    fdsCharM.width=6;

    fdsCharP.character_map[0]=B00000111;
    fdsCharP.character_map[1]=B00001001; 
    fdsCharP.character_map[2]=B00001001; 
    fdsCharP.character_map[3]=B00000111; 
    fdsCharP.character_map[4]=B00000001; 
    fdsCharP.character_map[5]=B00000001; 
    fdsCharP.character_map[6]=B00000001;
    fdsCharP.width=5;

    fdsCharR.character_map[0]=B00000111;
    fdsCharR.character_map[1]=B00001001; 
    fdsCharR.character_map[2]=B00001001; 
    fdsCharR.character_map[3]=B00000111; 
    fdsCharR.character_map[4]=B00001001; 
    fdsCharR.character_map[5]=B00001001; 
    fdsCharR.character_map[6]=B00001001;
    fdsCharR.width=5;

    fdsCharS.character_map[0]=B00000110;
    fdsCharS.character_map[1]=B00001001; 
    fdsCharS.character_map[2]=B00000001; 
    fdsCharS.character_map[3]=B00000110; 
    fdsCharS.character_map[4]=B00001000; 
    fdsCharS.character_map[5]=B00001001; 
    fdsCharS.character_map[6]=B00000110;
    fdsCharS.width=5;

    fdsCharT.character_map[0]=B00011111;
    fdsCharT.character_map[1]=B00000100; 
    fdsCharT.character_map[2]=B00000100; 
    fdsCharT.character_map[3]=B00000100; 
    fdsCharT.character_map[4]=B00000100; 
    fdsCharT.character_map[5]=B00000100; 
    fdsCharT.character_map[6]=B00000100;
    fdsCharT.width=6;

    fdsCharU.character_map[0]=B00010001;
    fdsCharU.character_map[1]=B00010001; 
    fdsCharU.character_map[2]=B00010001; 
    fdsCharU.character_map[3]=B00010001; 
    fdsCharU.character_map[4]=B00010001; 
    fdsCharU.character_map[5]=B00010001; 
    fdsCharU.character_map[6]=B00001110;
    fdsCharU.width=6;

    fdsCharColon.character_map[0]=B00000000;
    fdsCharColon.character_map[1]=B00000000;
    fdsCharColon.character_map[2]=B00000001;
    fdsCharColon.character_map[3]=B00000000;
    fdsCharColon.character_map[4]=B00000001;
    fdsCharColon.character_map[5]=B00000000;
    fdsCharColon.character_map[6]=B00000000;
    fdsCharColon.width=2;

    fdsCharSingleQuote.character_map[0]=B00000001;
    fdsCharSingleQuote.character_map[1]=B00000001;
    fdsCharSingleQuote.character_map[2]=B00000000;
    fdsCharSingleQuote.character_map[3]=B00000000;
    fdsCharSingleQuote.character_map[4]=B00000000;
    fdsCharSingleQuote.character_map[5]=B00000000;
    fdsCharSingleQuote.character_map[6]=B00000000;
    fdsCharSingleQuote.width=2;
    
    fdsCharComma.character_map[0]=B00000000;
    fdsCharComma.character_map[1]=B00000000;
    fdsCharComma.character_map[2]=B00000000;
    fdsCharComma.character_map[3]=B00000000;
    fdsCharComma.character_map[4]=B00000000;
    fdsCharComma.character_map[5]=B00000001;
    fdsCharComma.character_map[6]=B00000001;
    fdsCharComma.width=2;

    fdsCharBang.character_map[0]=B00000001;
    fdsCharBang.character_map[1]=B00000001;
    fdsCharBang.character_map[2]=B00000001;
    fdsCharBang.character_map[3]=B00000001;
    fdsCharBang.character_map[4]=B00000001;
    fdsCharBang.character_map[5]=B00000000;
    fdsCharBang.character_map[6]=B00000001;
    fdsCharBang.width=2;

    fdsCharUnknown.character_map[0]=B00000111;
    fdsCharUnknown.character_map[1]=B00000111;
    fdsCharUnknown.character_map[2]=B00000111;
    fdsCharUnknown.character_map[3]=B00000111;
    fdsCharUnknown.character_map[4]=B00000111;
    fdsCharUnknown.character_map[5]=B00000111;
    fdsCharUnknown.character_map[6]=B00000111;
    fdsCharUnknown.width=4;

    fdsCharSpace.width=2;
}

fdsChar* charTofdsChar(char value){
    switch (value){
        case 'a':
        case 'A':
            return &fdsCharA;
        case 'b':
        case 'B':
            return &fdsCharB;
        case 'c':
        case 'C':
            return &fdsCharC;
        case 'e':
        case 'E':
            return &fdsCharE;
        case 'f':
        case 'F':
            return &fdsCharF;
        case 'h':
        case 'H':
            return &fdsCharH;
        case 'i':
        case 'I':
            return &fdsCharI;
        case 'k':
        case 'K':
            return &fdsCharK;
        case 'l':
        case 'L':
            return &fdsCharL;
        case 'm':
        case 'M':
            return &fdsCharM;
        case 'p':
        case 'P':
            return &fdsCharP;
        case 'r':
        case 'R':
            return &fdsCharR;
        case 's':
        case 'S':
            return &fdsCharS;
        case 't':
        case 'T':
            return &fdsCharT;
        case 'u':
        case 'U':
            return &fdsCharU;
        case ':':
            return &fdsCharColon;
        case '\'':
            return &fdsCharSingleQuote;
        case ',':
            return &fdsCharComma;
        case '!':
            return &fdsCharBang;
        case ' ':
            return &fdsCharSpace;
        default:
            return &fdsCharUnknown;
    }
}

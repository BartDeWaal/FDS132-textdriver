#include "font.h"

fdsChar fdsCharA;
fdsChar fdsCharB;
fdsChar fdsCharC;
fdsChar fdsCharD;
fdsChar fdsCharE;
fdsChar fdsCharF;
fdsChar fdsCharG;
fdsChar fdsCharH;
fdsChar fdsCharI;
fdsChar fdsCharJ;
fdsChar fdsCharK;
fdsChar fdsCharL;
fdsChar fdsCharM;
fdsChar fdsCharN;
fdsChar fdsCharO;
fdsChar fdsCharP;
fdsChar fdsCharQ;
fdsChar fdsCharR;
fdsChar fdsCharS;
fdsChar fdsCharT;
fdsChar fdsCharU;
fdsChar fdsCharV;
fdsChar fdsCharW;
fdsChar fdsCharX;
fdsChar fdsCharY;
fdsChar fdsCharZ;

fdsChar fdsChar0;
fdsChar fdsChar1;
fdsChar fdsChar2;
fdsChar fdsChar3;
fdsChar fdsChar4;
fdsChar fdsChar5;
fdsChar fdsChar6;
fdsChar fdsChar7;
fdsChar fdsChar8;
fdsChar fdsChar9;

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

    fdsCharD.character_map[0]=B00000111;
    fdsCharD.character_map[1]=B00001001; 
    fdsCharD.character_map[2]=B00010001; 
    fdsCharD.character_map[3]=B00010001; 
    fdsCharD.character_map[4]=B00010001; 
    fdsCharD.character_map[5]=B00001001; 
    fdsCharD.character_map[6]=B00000111;
    fdsCharD.width=6;

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

    fdsCharG.character_map[0]=B00001110;
    fdsCharG.character_map[1]=B00010001; 
    fdsCharG.character_map[2]=B00000001; 
    fdsCharG.character_map[3]=B00000001; 
    fdsCharG.character_map[4]=B00011101; 
    fdsCharG.character_map[5]=B00010001; 
    fdsCharG.character_map[6]=B00001110;
    fdsCharG.width=6;

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

    fdsCharJ.character_map[0]=B00001110;
    fdsCharJ.character_map[1]=B00000100; 
    fdsCharJ.character_map[2]=B00000100; 
    fdsCharJ.character_map[3]=B00000100; 
    fdsCharJ.character_map[4]=B00000100; 
    fdsCharJ.character_map[5]=B00000101; 
    fdsCharJ.character_map[6]=B00000010;
    fdsCharJ.width=5;

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

    fdsCharN.character_map[0]=B00010001;
    fdsCharN.character_map[1]=B00010001; 
    fdsCharN.character_map[2]=B00010011; 
    fdsCharN.character_map[3]=B00010101; 
    fdsCharN.character_map[4]=B00011001; 
    fdsCharN.character_map[5]=B00010001; 
    fdsCharN.character_map[6]=B00010001;
    fdsCharN.width=6;

    fdsCharO.character_map[0]=B00001110;
    fdsCharO.character_map[1]=B00010001; 
    fdsCharO.character_map[2]=B00010001; 
    fdsCharO.character_map[3]=B00010001; 
    fdsCharO.character_map[4]=B00010001; 
    fdsCharO.character_map[5]=B00010001; 
    fdsCharO.character_map[6]=B00001110;
    fdsCharO.width=6;

    fdsCharP.character_map[0]=B00000111;
    fdsCharP.character_map[1]=B00001001; 
    fdsCharP.character_map[2]=B00001001; 
    fdsCharP.character_map[3]=B00000111; 
    fdsCharP.character_map[4]=B00000001; 
    fdsCharP.character_map[5]=B00000001; 
    fdsCharP.character_map[6]=B00000001;
    fdsCharP.width=5;

    fdsCharQ.character_map[0]=B00001110;
    fdsCharQ.character_map[1]=B00010001; 
    fdsCharQ.character_map[2]=B00010001; 
    fdsCharQ.character_map[3]=B00010001; 
    fdsCharQ.character_map[4]=B00010001; 
    fdsCharQ.character_map[5]=B00001001; 
    fdsCharQ.character_map[6]=B00010110;
    fdsCharQ.width=6;

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

    fdsCharU.character_map[0]=B00001001;
    fdsCharU.character_map[1]=B00001001; 
    fdsCharU.character_map[2]=B00001001; 
    fdsCharU.character_map[3]=B00001001; 
    fdsCharU.character_map[4]=B00001001; 
    fdsCharU.character_map[5]=B00001001; 
    fdsCharU.character_map[6]=B00000110;
    fdsCharU.width=5;

    fdsCharV.character_map[0]=B00010001;
    fdsCharV.character_map[1]=B00010001; 
    fdsCharV.character_map[2]=B00010001; 
    fdsCharV.character_map[3]=B00001010; 
    fdsCharV.character_map[4]=B00001010; 
    fdsCharV.character_map[5]=B00001010; 
    fdsCharV.character_map[6]=B00000100;
    fdsCharV.width=6;

    fdsCharW.character_map[0]=B00010001;
    fdsCharW.character_map[1]=B00010101; 
    fdsCharW.character_map[2]=B00010101; 
    fdsCharW.character_map[3]=B00010101; 
    fdsCharW.character_map[4]=B00001010; 
    fdsCharW.character_map[5]=B00001010; 
    fdsCharW.character_map[6]=B00001010;
    fdsCharW.width=6;

    fdsCharX.character_map[0]=B00010001;
    fdsCharX.character_map[1]=B00010001; 
    fdsCharX.character_map[2]=B00001010; 
    fdsCharX.character_map[3]=B00000100; 
    fdsCharX.character_map[4]=B00001010; 
    fdsCharX.character_map[5]=B00010001; 
    fdsCharX.character_map[6]=B00010001;
    fdsCharX.width=6;

    fdsCharY.character_map[0]=B00010001;
    fdsCharY.character_map[1]=B00010001; 
    fdsCharY.character_map[2]=B00001010; 
    fdsCharY.character_map[3]=B00000100; 
    fdsCharY.character_map[4]=B00000100; 
    fdsCharY.character_map[5]=B00000100; 
    fdsCharY.character_map[6]=B00000100;
    fdsCharY.width=6;

    fdsCharZ.character_map[0]=B00011111;
    fdsCharZ.character_map[1]=B00010000; 
    fdsCharZ.character_map[2]=B00001000; 
    fdsCharZ.character_map[3]=B00000100; 
    fdsCharZ.character_map[4]=B00000010; 
    fdsCharZ.character_map[5]=B00000001; 
    fdsCharZ.character_map[6]=B00011111;
    fdsCharZ.width=6;

    fdsChar0.character_map[0]=B00001110;
    fdsChar0.character_map[1]=B00010001; 
    fdsChar0.character_map[2]=B00011001; 
    fdsChar0.character_map[3]=B00010101; 
    fdsChar0.character_map[4]=B00010011; 
    fdsChar0.character_map[5]=B00010001; 
    fdsChar0.character_map[6]=B00001110;
    fdsChar0.width=6;

    fdsChar1.character_map[0]=B00000100;
    fdsChar1.character_map[1]=B00000110; 
    fdsChar1.character_map[2]=B00000101; 
    fdsChar1.character_map[3]=B00000100; 
    fdsChar1.character_map[4]=B00000100; 
    fdsChar1.character_map[5]=B00000100; 
    fdsChar1.character_map[6]=B00011111;
    fdsChar1.width=6;

    fdsChar2.character_map[0]=B00001110;
    fdsChar2.character_map[1]=B00010001; 
    fdsChar2.character_map[2]=B00010000; 
    fdsChar2.character_map[3]=B00001000; 
    fdsChar2.character_map[4]=B00000100; 
    fdsChar2.character_map[5]=B00000010; 
    fdsChar2.character_map[6]=B00011111;
    fdsChar2.width=6;

    fdsChar3.character_map[0]=B00001110;
    fdsChar3.character_map[1]=B00010001; 
    fdsChar3.character_map[2]=B00010000; 
    fdsChar3.character_map[3]=B00001100; 
    fdsChar3.character_map[4]=B00010000; 
    fdsChar3.character_map[5]=B00010001; 
    fdsChar3.character_map[6]=B00001110;
    fdsChar3.width=6;

    fdsChar4.character_map[0]=B00001000;
    fdsChar4.character_map[1]=B00001100; 
    fdsChar4.character_map[2]=B00001010; 
    fdsChar4.character_map[3]=B00001001; 
    fdsChar4.character_map[4]=B00011111; 
    fdsChar4.character_map[5]=B00001000; 
    fdsChar4.character_map[6]=B00001000;
    fdsChar4.width=6;

    fdsChar5.character_map[0]=B00011111;
    fdsChar5.character_map[1]=B00000001; 
    fdsChar5.character_map[2]=B00000001; 
    fdsChar5.character_map[3]=B00001110; 
    fdsChar5.character_map[4]=B00010000; 
    fdsChar5.character_map[5]=B00010001; 
    fdsChar5.character_map[6]=B00001110;
    fdsChar5.width=6;

    fdsChar6.character_map[0]=B00001110;
    fdsChar6.character_map[1]=B00000001; 
    fdsChar6.character_map[2]=B00000001; 
    fdsChar6.character_map[3]=B00001111; 
    fdsChar6.character_map[4]=B00010001; 
    fdsChar6.character_map[5]=B00010001; 
    fdsChar6.character_map[6]=B00001110;
    fdsChar6.width=6;

    fdsChar7.character_map[0]=B00011111;
    fdsChar7.character_map[1]=B00010000; 
    fdsChar7.character_map[2]=B00010000; 
    fdsChar7.character_map[3]=B00001000; 
    fdsChar7.character_map[4]=B00000100; 
    fdsChar7.character_map[5]=B00000010; 
    fdsChar7.character_map[6]=B00000001;
    fdsChar7.width=6;

    fdsChar8.character_map[0]=B00001110;
    fdsChar8.character_map[1]=B00010001; 
    fdsChar8.character_map[2]=B00010001; 
    fdsChar8.character_map[3]=B00001110; 
    fdsChar8.character_map[4]=B00010001; 
    fdsChar8.character_map[5]=B00010001; 
    fdsChar8.character_map[6]=B00001110;
    fdsChar8.width=6;

    fdsChar9.character_map[0]=B00001110;
    fdsChar9.character_map[1]=B00010001; 
    fdsChar9.character_map[2]=B00010001; 
    fdsChar9.character_map[3]=B00011110; 
    fdsChar9.character_map[4]=B00010000; 
    fdsChar9.character_map[5]=B00010001; 
    fdsChar9.character_map[6]=B00001110;
    fdsChar9.width=6;

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
        case 'd':
        case 'D':
            return &fdsCharD;
        case 'e':
        case 'E':
            return &fdsCharE;
        case 'f':
        case 'F':
            return &fdsCharF;
        case 'g':
        case 'G':
            return &fdsCharG;
        case 'h':
        case 'H':
            return &fdsCharH;
        case 'i':
        case 'I':
            return &fdsCharI;
        case 'j':
        case 'J':
            return &fdsCharJ;
        case 'k':
        case 'K':
            return &fdsCharK;
        case 'l':
        case 'L':
            return &fdsCharL;
        case 'm':
        case 'M':
            return &fdsCharM;
        case 'n':
        case 'N':
            return &fdsCharN;
        case 'o':
        case 'O':
            return &fdsCharO;
        case 'p':
        case 'P':
            return &fdsCharP;
        case 'q':
        case 'Q':
            return &fdsCharQ;
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
        case 'v':
        case 'V':
            return &fdsCharV;
        case 'w':
        case 'W':
            return &fdsCharW;
        case 'x':
        case 'X':
            return &fdsCharX;
        case 'y':
        case 'Y':
            return &fdsCharY;
        case 'z':
        case 'Z':
            return &fdsCharZ;
        case '0':
            return &fdsChar0;
        case '1':
            return &fdsChar1;
        case '2':
            return &fdsChar2;
        case '3':
            return &fdsChar3;
        case '4':
            return &fdsChar4;
        case '5':
            return &fdsChar5;
        case '6':
            return &fdsChar6;
        case '7':
            return &fdsChar7;
        case '8':
            return &fdsChar8;
        case '9':
            return &fdsChar9;
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

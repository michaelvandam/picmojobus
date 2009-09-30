#include "asciiConvert.h"

int asciiHexToNibble(char nibble)
{
    int returnValue=0;
    
    switch(nibble)
    {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            returnValue = nibble - 48;
            break;
        }        
    
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        {
            returnValue = nibble - 87;
            break;
        }
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        {
            returnValue = nibble - 55;
            break;
        }
        default:
        {
            returnValue = -1;
            break;
        }       
    }
    
    return returnValue;
}
  

int asciiHexToBtye(char upperNibble, char lowerNibble) {
    int upperVal;
    int lowerVal;
    int retVal;

    upperVal = asciiHexToNibble(upperNibble);
    lowerVal = asciiHexToNibble(lowerNibble);
    
    if((upperVal>-1)&&(lowerVal>-1)) {
        return (upperVal<<4) + lowerVal;
    } else return -1;
}         


char * byteToAsciiHex(unsigned char value, char * hexStr) {
    char upperNibble;
    char lowerNibble;
    
    upperNibble = (value & 0xF0) >> 4;
    lowerNibble = (value & 0x0F);
    
    if((upperNibble>=0)&&(upperNibble<=9))
        upperNibble+=48;
    else upperNibble+=87;
    
   if((lowerNibble>=0)&&(lowerNibble<=9))
        lowerNibble+=48;
    else lowerNibble+=87;
    
    hexStr[0] = upperNibble;
    hexStr[1] = lowerNibble;
    hexStr[2] = '\0';
    
    return hexStr;
}

#ifndef asciiconvert_H
	#define asciiconvert_H
    int asciiHexToNibble(char nibble);
    int asciiHexToBtye(char upperNibble, char lowerNibble);
    char * byteToAsciiHex(unsigned char value, char * hexStr);
#endif

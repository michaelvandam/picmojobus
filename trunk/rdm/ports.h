#ifndef ports_H
	#define ports_h   
	#include <p18cxxx.h>
	
    volatile unsigned char * getPort(char portid);
    volatile unsigned char * getTris(char portid);
   int setBitFromSParam(unsigned char val, char* sparam);
    int setBitHigh(int val, char bitid);
    int setBitLow(int val, char bitid);
    int setBitToggle(int val, char bitid);

#endif

#include "ports.h"
#include <string.h>
#include "strtok_r.h"
#include <ctype.h>
#include <stdlib.h>
#include <usart.h>
/**********************************************
Helper Functions
**********************************************/
volatile unsigned char * getPort(char portid) {
    volatile unsigned char *port;
    switch(portid){
        case 'A':
            port = &PORTA;
            break;
        case 'B':
            port = &PORTB;
            break;
        case 'E':
            port = &PORTE;
            break;
        case 'F':
            port = &PORTF;
            break;
        case 'D':
            port = &PORTD;
            break;
        case 'J':
            port = &PORTJ;
            break;
        default:
            port = 0;
            break;
    }
    return port;
}
    

volatile unsigned char * getTris(char portid) {
    volatile unsigned char *tris;
    switch(portid){
        case 'A':
            tris = &TRISA;
            break;
        case 'B':
            tris = &TRISB;
            break;
        case 'E':
            tris = &TRISE;
            break;
        case 'F':
            tris = &TRISF;
            break;
        case 'D':
            tris = &TRISD;
            break;
        case 'J':
            tris = &TRISJ;
            break;
        default:
            return 0;
            break;
    }
    return tris;
}




int setBitHigh(int val, char bitid) {       
        if(bitid>7) return -1;
        val|=(1<<bitid);
        return val;
    }   


int setBitLow(int val, char bitid) {
        if(bitid>7) return -1;
        val&=~(1<<bitid);
        return val;
    }
    
int setBitToggle(int val, char bitid) {
        if(bitid>7) return -1;
        val^=(1<<bitid);
        return val;
}


/*****************************************
Read in string set bit values return Byte or -1 if error
Example -> 0H1L2T3L
*****************************************/
int setBitFromSParam(unsigned char val, char* sparam) {
    char * c;
    char bitN;
    //char test[10];
    c=sparam;
    //strcpypgm2ram(test,"");
    
    
    while(c!='\0') {
        
        if (isdigit(*c)==0) break;
        else {
            //putc1USART(*c); 
            bitN = *c-'0';
            if(bitN>7) return -1;
        }
        
        ++c;  //Look at next character
        //putc1USART(*c);
        switch(*c) {
            case 'H':
                //putrs1USART("HOK:");
                val = setBitHigh(val, bitN);
                break;
            case 'L':
                //putrs1USART("LOK:");
                val = setBitLow(val, bitN);
                break;
            case 'T':
                //putrs1USART("TOK:");
                val = setBitToggle(val, bitN);
                break;
            default:
                return -1;
                break;
        }
        c++;
        //itoa(val,test);
        //puts1USART(test);
                   
    }  
    //putrs1USART("RETURN:");
    //itoa(val,test);
    //puts1USART(test);
    return val;                  
}
    


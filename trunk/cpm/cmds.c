#include "cmds.h"
#include "mojomsg.h"
#include "mojocmd.h"
#include "mojoerror.h"
#include "asciiConvert.h"
#include "ports.h"  //Helper fxns for accessing ports
#include <usart.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


ram char cmdRespBuf[MAXPARAMLEN];


void setErrResp(ram char * buf, const rom char * serr){
    strcpypgm2ram(buf,serr);
}

/************************************************
Callback functions
************************************************/           
char* setport(char *sparam, char * callname) {
    int val;
    char portid;
    int i;
    char buf[10];
    volatile unsigned char * port;
    
    portid = callname[4];  //Get port ID from commandname
    i = strlen(sparam);
    if(strlen(sparam)==0) {  //If no param, get value and return
        //putrs1USART("Test\n");
        port = getPort(portid);
        byteToAsciiHex(*port, cmdRespBuf);
        return cmdRespBuf;
    }
    
    if(!(strlen(sparam)==2)) {  //Check to see if parameter length is correct
        setErrResp(cmdRespBuf, SBADPARAM); //Respond with badparam error
        return cmdRespBuf;
    }

    
    val = asciiHexToBtye(sparam[0],sparam[1]); //Convert from hex to byte
    
    if(val>-1) {  //If value is not error
        port = getPort(portid);
        *port = val;
        byteToAsciiHex(*port, cmdRespBuf);
        //itoa(val,cmdRespBuf);
        return cmdRespBuf;
    }
    
    //Else we are in error
    setErrResp(cmdRespBuf, SBADPARAM);
    return cmdRespBuf;
}


char* settris(char *sparam, char * callname) {
    int val;
    char portid;
    volatile unsigned char * tris;
    
    portid = callname[4];  //Get port ID from commandname
    
    if(strlen(sparam)==0) {  //If no param, get value and return
        tris = getTris(portid);
        byteToAsciiHex(*tris, cmdRespBuf);
        return cmdRespBuf;
    }
    
    if(!(strlen(sparam)==2)) {  //Check to see if parameter length is correct
        setErrResp(cmdRespBuf, SBADPARAM); //Respond with badparam error
        return cmdRespBuf;
    }

    
    val = asciiHexToBtye(sparam[0],sparam[1]); //Convert from hex to byte
    
    if(val>-1) {  //If value is not error
        tris = getTris(portid);
        *tris = val;
        byteToAsciiHex(*tris, cmdRespBuf);
        return cmdRespBuf;
    }
    
    //Else we are in error
    setErrResp(cmdRespBuf, SBADPARAM);
    return cmdRespBuf;
}



char* Hello(char *sparam, char * callname) {    
    strcpypgm2ram(cmdRespBuf,"WORLD!");
    return cmdRespBuf; 
}


char* Blink(char *sparam, char * callname) {
    PORTA=~LATA;    
    PORTE=~LATE;
    PORTB=~LATB;
    PORTD=~LATD;
    PORTJ=~LATJ;
    PORTF=~LATF;
    strcpy(cmdRespBuf, sparam);
    return cmdRespBuf; 
}



char* openAll(char *sparam, char *callname) {
    if(!(strlen(sparam)==0)) {
        setErrResp(cmdRespBuf,SBADPARAM);
        return cmdRespBuf;
    }
    
    TRISA=0;TRISB=0;TRISD=0;TRISE=0;TRISF=0;TRISJ=0;
    PORTA=0xFF;PORTB=0xFF;PORTD=0xFF;PORTE=0xFF;PORTF=0xFF;PORTJ=0xFF;
    strcpypgm2ram(cmdRespBuf,SCOMPLETE);
    return cmdRespBuf;
}

char* closeAll(char *sparam, char *callname) {
    if(!(strlen(sparam)==0)) {
        setErrResp(cmdRespBuf,SBADPARAM);
        return cmdRespBuf;
    }
    
    TRISA=0;TRISB=0;TRISD=0;TRISE=0;TRISF=0;TRISJ=0;
    PORTA=0x00;PORTB=0x00;PORTD=0x00;PORTE=0x00;PORTF=0x00;PORTJ=0x00;
    strcpypgm2ram(cmdRespBuf,SCOMPLETE);
    return cmdRespBuf;
}

char* setR(char * sparam, char * callname) {
    int val=0;
    char newVal;
    char portid;
    //char buf[10];
    volatile unsigned char * port;
    
    portid = callname[1];  //Get port ID from commandname
    //putc1USART(portid);
    port = getPort(portid); //Get Port
    val = (char)*port;
    val = setBitFromSParam((unsigned char)val, sparam);
    
    if (val>-1) {
        *port = (unsigned char)val;
        byteToAsciiHex(*port, cmdRespBuf);
        return cmdRespBuf;
    }
    
    strcpypgm2ram(cmdRespBuf,SBADPARAM);
    return cmdRespBuf;

} 


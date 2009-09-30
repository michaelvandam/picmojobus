#include "mojomsg.h"
#include "mojocmd.h"
#include "mojoerror.h"
#include "cmds.h"
#include "RDMcmds.h"
#include <usart.h>
#include <stdio.h>
#include <string.h>
#include <EEP.h>
#include <delays.h>
#include <ctype.h>


#pragma udata execcmds
EXECCMD execmds[NUMOFCMDS];
#pragma udata

void addFxn(const rom char *name,int index,CMDFXN f){
    //strcpypgm2ram(execmds[index].cmdname, "WOW");
    strcpypgm2ram(execmds[index].cmdname, name);
    execmds[index].fxn = f;
}

CMDFXN findFxn(char *fxnname) {
    int i=0;
    
    //MojoWriteRamStr(fxnname);
    
    if (*fxnname=='\0'){
        return &NotFound; 
    }
    
    for(i=0;i<NUMOFCMDS;i++){
        if(strcmp(execmds[i].cmdname, fxnname)==0) {//Match         
            return execmds[i].fxn;
        }
    }
    
    return &NotFound;  
}

void initializeMojocmds(void) {
    int i;
    for(i=0;i<NUMOFCMDS;i++){
        strcpypgm2ram(execmds[i].cmdname,"NA");
    }
    addFxn("ID",0,&setid);
    addFxn("WHO",1,&who);
    addFxn("ANNC",2,&annc);
    addFxn("BLINK",3,&Blink);
    addFxn("HELLO",4,&Hello);
    addFxn("PORTA",5,&setport);
    addFxn("PORTB",6,&setport);
    addFxn("PORTD",7,&setport);
    addFxn("PORTE",8,&setport);
    addFxn("PORTF",9,&setport);
    addFxn("PORTJ",10,&setport);
    addFxn("TRISA",11,&settris);
    addFxn("TRISB",12,&settris);
    addFxn("TRISD",13,&settris);
    addFxn("TRISE",14,&settris);
    addFxn("TRISF",15,&settris);
    addFxn("TRISJ",16,&settris);
    addFxn("OPALL",18,&openAll);     
    addFxn("CLSALL",19,&closeAll);
    addFxn("RA",20,&setR);
    addFxn("RB",21,&setR);
    addFxn("RD",22,&setR);
    addFxn("RE",23,&setR);
    addFxn("RF",24,&setR);
    addFxn("RJ",25,&setR);
    addFxn("LOAD",26,&load);
    addFxn("STDBY",27,&standby);
    addFxn("DELVR",28,&deliver);

}



char* NotFound(char *sparam, char * callname) {
    //putrs1USART("Oops Not found\n");
    strcpypgm2ram(cmdRespBuf,SBADCOMMAND);
    return cmdRespBuf;
}


char* who(char *sparam, char * callname) {
    strcpypgm2ram(cmdRespBuf,MODULETYPE);
    strcatpgm2ram(cmdRespBuf,"-V");
    strcatpgm2ram(cmdRespBuf,VERSION);
    return cmdRespBuf;
}

char* annc(char *sparam, char * callname) {
    int t; //Delay duration
    t = addy*100;
    strcpypgm2ram(cmdRespBuf,MODULETYPE);
    strcatpgm2ram(cmdRespBuf,"-V");
    strcatpgm2ram(cmdRespBuf,VERSION);
    Delay10KTCYx(t);
    return cmdRespBuf;
}
     
  

char* setid(char *sparam, char * callname) {
    //write to EEPROM ADDR check to see if valid ascii character!
    if (!(strlen(sparam)==1)) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else if(!(isprint(sparam[0]))) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else if (sparam[0]=='0') {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        Write_b_eep(ADDR_EEPROM, sparam[0]);
        Busy_eep();
        addy = sparam[0];
        strcpy(cmdRespBuf, sparam);    
    }
    
    
    return cmdRespBuf; 
}


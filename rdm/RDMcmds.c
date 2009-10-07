#include "RDMcmds.h"
#include "mojoerror.h"
#include <string.h>
#include <p18cxxx.h>
#include "asciiConvert.h"
#include "ports.h"
#include <usart.h>
#include "strtok_r.h"
#include <string.h>
#include <stdlib.h>
#include "isNumeric.h"

MODULE rdm; //Structure holds current state of module		
char MAXREAGENT = REAGENT4;

//Callback fxns

char* load(char * sparam, char * callname) {
    RDM2Load();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}    

char* standby(char *sparam, char *callname) {
    RDM2Standby();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}
char* deliver(char *sparam, char *callname){
    int reagent=0;
    char buf[10];  
    if (strlen(sparam)==0) {
        reagent = rdm.selectReagent;
        itoa(reagent,buf);
        strcpy(cmdRespBuf,buf);
    } else if (!(isNumeric(sparam))) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        reagent = atoi(sparam);
        if (reagent>MAXREAGENT)
            strcpypgm2ram(cmdRespBuf,"?BADREAGENT");
        else {
            RDMSetReagent((char)reagent); 
            RDM2Deliver();
            strcpy(cmdRespBuf,sparam);
        }
    }
    return cmdRespBuf;
}   

//RDM functions

void RDMSetup(void) {
    rdm.state=STARTUP;
    rdm.selectReagent=REAGENT1;
}

void RDM2Standby(void) {
    rdm.state=STANDBY;
}

void RDM2Load(void){
    rdm.state=LOADING;
}

void RDM2Manual(void) {
    rdm.state=MANUAL;
}
void RDMSetReagent(unsigned char reagent) {
    rdm.selectReagent=reagent;
}
void RDM2Deliver(void) {
    rdm.state=DELIVER;
}

void RDMDeliver(void) {
    switch (rdm.selectReagent) {
        case REAGENT1:
            RDMVALVES=0x01;
            break;
        case REAGENT2:
            RDMVALVES=0x02;
            break;
        case REAGENT3:
            RDMVALVES=0x03;
            break;
        case REAGENT4:
            RDMVALVES=0x04;
            break;
        default:
            break;
    }

}

void RDMRun(void) {
    
    switch(rdm.state) {
        case STARTUP:
            RDMVALVES=0xFF;
            RDM2Standby();
            break;
        case STANDBY: //Waiting for command put maintaince routines here
            break;
        case LOADING:
            RDMVALVES=0x00;
            break;
        case MANUAL: //Accepting other commands (Probably unnecessary)
            break;
        case DELIVER: //
            RDMDeliver();
            break;
        default:
            RDM2Standby();
            break;
    }

}

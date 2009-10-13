#include "CPMcmds.h"
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

MODULE cpm; //Structure holds current state of module		


//Callback fxns

char* loadSample(char * sparam, char * callname) {
    CPM2LoadSample();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}    

char* loadReagents(char * sparam, char * callname) {
    CPM2LoadReagents();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}  

char* standby(char *sparam, char *callname) {
    CPM2Standby();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}

char* trap(char *sparam, char *callname){
    CPM2Trap();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}

char* wash(char *sparam, char *callname){
    CPM2Wash();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}

char* elute(char *sparam, char *callname){
    CPM2Elute();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}

char* manual(char *sparam, char *callname){
    CPM2Manual();    
    if (strlen(sparam)>0) {
        strcpypgm2ram(cmdRespBuf,SBADPARAM);
    } else {
        strcpypgm2ram(cmdRespBuf,"DONE");
    }
    return cmdRespBuf;
}

//CPM functions
//Fxns for changing CPM states
void CPM2Standby(void) {
    CPMVALVES=0x00;
    cpm.state=STANDBY;
}

void CPM2LoadReagents(void){
    cpm.state=LOADINGREAGENTS;
}

void CPM2LoadSample(void){
    cpm.state=LOADINGSAMPLE;
}

void CPM2Manual(void) {
    cpm.state=MANUAL;
}

void CPM2Trap(void) {
    cpm.state=TRAP;
}

void CPM2Wash(void) {
    cpm.state=WASH;
}

void CPM2Elute(void) {
    cpm.state=ELUTE;
}


//Fxn to setup CPM

void CPMSetup(void) {
    cpm.state=STARTUP;
}

//Maintains CPM state
void CPMRun(void) {
    
    switch(cpm.state) {
        case STARTUP: // Put initialization routines here
            CPM2Standby();
            break;
        case STANDBY: //Waiting for command put maintaince routines here
            break;
        case LOADINGREAGENTS:
            CPMLoadReagents();
            break;
        case LOADINGSAMPLE:
            CPMLoadSample();
            break;
        case TRAP: 
            CPMTrap();
            break;
        case WASH:
            CPMWash();
            break;
        case ELUTE:
            CPMElute();
            break;
        case MANUAL:
            break;
        default:
            CPM2Standby();
            break;
    }

}

void CPMLoadReagents(void) {
    CPMVALVES = 0b00000000;
}

void CPMLoadSample(void) {
    CPMVALVES = 0xb00000000;
} 

void CPMTrap(void) {
    CPMVALVES = 0b01000010;
}

void CPMWash(void) {
    CPMVALVES = 0b10000001;
}

void CPMElute(void) {
    CPMVALVES = 0b00111100;
}

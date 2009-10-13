#include "ports.h"
#include <timers.h>
#include "pumps.h"
#include <string.h>
    
//pumps = PUMP[NUMPUMPS];
PUMP pumps[NUMPUMPS];

void initializePump(PUMP* p, char * portid, char pin1, char pin2, char pin3) {
    int i;
    
    p->port = getPort(portid);
    p->tick = 0;
    p->cycles=0;
    p->cyclethreshold=0;
    p->tickthreshold=4;
    p->pin1=pin1;
    p->pin2=pin2;
    p->pin3=pin3;
    p->pumpState=PUMPSTATE1;
    
    pumpForward(p);
    turnOffPump(p);
}


void pumpForward(PUMP *p) {
    p->direction=FORWARD;
}

void pumpReverse(PUMP *p) {
    p->direction=REVERSE;
}

void turnOnPump(PUMP * p) {
    p->pumpStatus=PUMPON;   
}

void turnOffPump(PUMP * p) {
    p->pumpStatus=PUMPOFF;   
}

void pmpSetSpeed(PUMP * p,unsigned int speed) {
    p->tickthreshold = speed;
}


void pmpSetCycles(PUMP *p, int cycles) {
    p->cyclethreshold=cycles;
}

void pmpSetPort(PUMP *p, char portid) {
    p->portid = portid;
    p->port = getPort(p->portid);
}

void pmpSetPin1(PUMP *p, char pin1) {
    p->pin1 = pin1;
}


void pmpSetPin2(PUMP *p, char pin2) {
    p->pin2 = pin2;
}


void pmpSetPin3(PUMP *p, char pin3){
    p->pin3 = pin3;
}    

char pumpIsOn(PUMP* p) {
if (p->pumpStatus == PUMPON) return 1;
else return 0;
}


void pumpIncCylces(PUMP *p) {
    p->cycles++;
}

void stepPump(PUMP *p) {
    int val;
    val = *(p->port);
    
    switch(p->pumpState) {
     case PUMPSTATE1:
        val = setBitLow(val,p->pin1);
        val = setBitLow(val,p->pin2);
        val = setBitHigh(val,p->pin3);
        *(p->port) = val;
        if (p->direction==FORWARD) p->pumpState=PUMPSTATE2;
        else p->pumpState=PUMPSTATE4;         
         break;
     case PUMPSTATE2:
        val = setBitHigh(val,p->pin1);
        val = setBitLow(val,p->pin2);
        val = setBitHigh(val,p->pin3);
        *(p->port) = val;
        if (p->direction==FORWARD) p->pumpState=PUMPSTATE3;
        else p->pumpState=PUMPSTATE1; 
        break;
     case PUMPSTATE3:
        val = setBitHigh(val,p->pin1);
        val = setBitHigh(val,p->pin2);
        val = setBitLow(val,p->pin3);
        *(p->port) = val;
        if (p->direction==FORWARD) p->pumpState=PUMPSTATE4;
        else p->pumpState=PUMPSTATE2; 
         break;
     case PUMPSTATE4:
        val = setBitLow(val,p->pin1);
        val = setBitHigh(val,p->pin2);
        val = setBitHigh(val,p->pin3);
        *(p->port) = val;
        pumpIncCylces(p);
        if (p->direction==FORWARD) p->pumpState=PUMPSTATE1;
        else p->pumpState=PUMPSTATE3; 
        break;
        
      default:
        p->pumpState=PUMPSTATE1;
        val = setBitLow(val,p->pin1);
        val = setBitLow(val,p->pin2);
        val = setBitLow(val,p->pin3);
        *(p->port) = val;
        pumpIncCylces(p);  //Inc pump when cycle complete
        if (p->direction==FORWARD) p->pumpState=PUMPSTATE2;
        else p->pumpState=PUMPSTATE4; 
        break;
    }
}


char pumpIsReadyToStep(PUMP * p) {
    if (p->tick >= p->tickthreshold){
        p->tick=0;
        return 1;
    } else {
        return 0;
    }
}

char pumpCyclesLeft(PUMP *p) {
    
     if(p->cyclethreshold==0) return 1;
     
     if (p->cycles >= p->cyclethreshold){
        p->cycles=0;
        return 0;
    } else {
        return 1;
    }   
}

PUMP * getPump(char pumpid) {
    return &pumps[pumpid];
}

void RunPump(void) {
    char i;
    PUMP *p;
    for(i=0;i<NUMPUMPS;i++){
        p=getPump(i);
        if (!(pumpCyclesLeft(p))) turnOffPump(p);
    
        if (pumpIsOn(p) &&    //Check to see if pump is on
            pumpIsReadyToStep(p)) //Check to see if step scaler is expired
            stepPump(p);  //If so step pump

    }
}

void StartPumpTimer(void) {
    OpenTimer0(TIMER_INT_ON & 
                T0_16BIT & 
                T0_SOURCE_INT & 
                T0_PS_1_1 );
     INTCON2bits.TMR0IP=0;
}

void StopPumpTimer(void) {
    CloseTimer0();
}


char PumpIsOn(char pumpid) {
    PUMP *p;
    p = getPump(pumpid);
    pumpIsOn(p);
}

void PumpReverse(char pumpid) {
    PUMP *p;
    p = getPump(pumpid);
    pumpReverse(p);
}

void PumpForward(char pumpid) {
    PUMP *p;
    p = getPump(pumpid);
    pumpForward(p);
}


void AddPumpTick(void) {
    int i;
    for(i=0;i<NUMPUMPS;i++) {
        pumps[i].tick++;
    }
}

void SetPumpSpeed(char pumpid,unsigned int speed) {
    PUMP *p;
    p = getPump(pumpid);
    pmpSetSpeed(p, speed);
}

void SetPumpCycles(char pumpid,unsigned int speed) {
    PUMP *p;
    p = getPump(pumpid);
    pmpSetCycles(p, speed);
}

int SetPumpPins(char pumpid,char pinNum,char pinVal) {
    PUMP *p;
    p = getPump(pumpid);
    if ((pinVal < 0) || (pinVal > 7)) return -1;
    if ((pinNum < 0) || (pinNum > 2)) return -1;
    if (pinNum==0) pmpSetPin1(p, pinVal);
    if (pinNum==1) pmpSetPin2(p, pinVal);
    if (pinNum==2) pmpSetPin3(p, pinVal);
    return 1;    
}

void SetPumpPort(char pumpid,char portid) {
    PUMP *p;
    p = getPump(pumpid);
    pmpSetPort(p,portid);
}

void SetupPump(char pumpid) {
    PUMP *p;
    p = getPump(pumpid);
    initializePump(p, 'B',0,1,2);
}

void StartPump(char pumpid) {
    PUMP *p;
    p = getPump(pumpid);
    turnOnPump(p);
    StartPumpTimer();
}

void StopPump(char pumpid) {
    PUMP *p;
    p = getPump(pumpid);
    turnOffPump(p);
    //StopPumpTimer();
}

char ValidPumpId(char pumpid) {
    if ((pumpid>-1)&&(pumpid<NUMPUMPS))
        return 1;
    else return 0;
}

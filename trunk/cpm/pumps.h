#ifndef PUMPS_H
#define PUMPS_H
#define PUMPTMRFLAG INTCONbits.TMR0IF    
#define PUMPPORTS "ABDEFJ" 
#define NUMPUMPS 3
        
typedef struct pump_settings{
    char portid;
    volatile unsigned char * port;
    char pin1; char pin2; char pin3;
    volatile char direction; 
    volatile unsigned int tickthreshold;
    volatile unsigned int tick;
    volatile unsigned int cycles;
    volatile unsigned int cyclethreshold;
    volatile char pumpStatus;
    volatile char pumpState;
    
} PUMP;



enum {NOTCONF,PUMPON, PUMPOFF};

enum {PUMPSTATE1,PUMPSTATE2,PUMPSTATE3,PUMPSTATE4};

enum {FORWARD, REVERSE};
extern PUMP pumps[NUMPUMPS];

void initializePump(PUMP* p, char * portid, char pin1, char pin2, char pin3);
void pumpForward(PUMP *p);
void pumpReverse(PUMP *p);
void turnOnPump(PUMP * p);
void turnOffPump(PUMP * p);
void pmpSetSpeed(PUMP * p,unsigned int speed);
void pmpSetCycles(PUMP *p, int cycles);
void pmpSetPort(PUMP *p, char portid);
void pmpSetPin1(PUMP *p, char pin1);
void pmpSetPin2(PUMP *p, char pin2);
void pmpSetPin3(PUMP *p, char pin3);
char pumpIsOn(PUMP* p);
void pumpIncCount(PUMP *p);
void pumpIncCylces(PUMP *p);
void stepPump(PUMP *p);
char pumpIsReadyToStep(PUMP * p);
void SetPumpSpeed(char pumpid,unsigned int speed);
void SetPumpCycles(char pumpid,unsigned int speed);
void RunPump(void);
void SetupPump(char pumpid);
void CreatePump(char portid, char pin1, char pin2, char pin3);
void StartPump(char pumpid);
void StopPump(char pumpid);
char PumpIsOn(char pumpid);
void StartPumpTimer(void);
void StopPumpTimer(void);
void PumpForward(char pumpid);
void PumpReverse(char pumpid);
void AddPumpTick(void);
int SetPumpPins(char pumpid,char pinNum,char pinVal);
void SetPumpPort(char pumpid,char portid);
PUMP * getPump(char pumpid);
char ValidPumpId(char pumpid);

#endif

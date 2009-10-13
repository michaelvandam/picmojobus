#ifndef RDMcmds_H
	#define RDMcmds_h   
	
	#include "mojocmd.h"
    #include "cmds.h"
	#define MODULETYPE "CPM"
	#define VERSION "0.1"			
    #define CPMVALVES  PORTB
    
	enum {
	STARTUP, // Startup state
	STANDBY, // Standby state
	LOADINGREAGENTS, // Loading reagents state
	LOADINGSAMPLE,  // Loading sample state
	TRAP,  // Traping Diluent
	WASH, // Wash state
	ELUTE, //Elute State
	MANUAL  // Manual state
    };	

    

    typedef struct CPMmodule{
		volatile char state; //State of message
	} MODULE;

			
	extern MODULE cpm; //Structure holds current state of module		
    
    
    extern ram char cmdRespBuf[MAXPARAMLEN];
    extern void setErrResp(ram char * buf, const rom char * serr);
   
   
   
    //Callback fxns
    char* standby(char *sparam, char *callname);
    char* loadSample(char *sparam, char *callname);
    char* loadReagents(char *sparam, char *callname);
    char* trap(char *sparam, char *callname);
    char* wash(char *sparam, char *callname);
    char* elute(char *sparam, char *callname);
    char* manual(char *sparam, char *callname);
    //Update Mojocmd.h with number of commands!!!!!
    
    
    //RDM Functions

    void CPMSetup(void);
    void CPMRun(void);
    void CPM2Standby(void);
    void CPM2LoadReagents(void);
    void CPM2LoadSample(void);
    void CPM2Trap(void);
    void CPM2Wash(void);
    void CPM2Elute(void);
    void CPM2Manual(void);

    void CPMLoadReagents(void);
    void CPMLoadSample(void);
    void CPMTrap(void);
    void CPMWash(void);
    void CPMElute(void);




#endif

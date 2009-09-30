#ifndef RDMcmds_H
	#define RDMcmds_h   
	
	#include "mojocmd.h"
    #include "cmds.h"
	#define MODULETYPE "RDM"
	#define VERSION "0.1"			
    #define RDMVALVES  PORTB
    
	enum {
	STARTUP, // Startup state
	STANDBY, // Standby state
	LOADING, // Loading state
	MANUAL,  // Manual state
	DELIVER  // Deliver state
    };	

    enum {
    REAGENT1,
    REAGENT2,
    REAGENT3,
    REAGENT4
    };   
    
    extern char MAXREAGENT;

    typedef struct RDMmodule{
		volatile char state; //State of message
		volatile char selectReagent;
	} MODULE;

			
	extern MODULE rdm; //Structure holds current state of module		
    
    
    extern ram char cmdRespBuf[MAXPARAMLEN];
    extern void setErrResp(ram char * buf, const rom char * serr);
   
   
   
    //Callback fxns
    char* load(char *sparam, char *callname);
    char* standby(char *sparam, char *callname);
    char* deliver(char *sparam, char *callname);
    //Update Mojocmd.h with number of commands!!!!!
    
    
    //RDM Functions

    void RDMSetup(void);
    void RDMRun(void);
    void RDM2Standby(void);
    void RDM2Load(void);
    void RDM2Manual(void);
    void RDMSetReagent(unsigned char reagent);
    void RDM2Deliver(void);
#endif

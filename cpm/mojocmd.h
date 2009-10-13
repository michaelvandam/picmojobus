#ifndef mojocmd_H
    #include "mojomsg.h"
	#define mojocmd_H
    #define NUMOFCMDS 33
    
    
    typedef char* (*CMDFXN)(char * sparam, char * callname);
    
    typedef struct execcmd{
        ram char cmdname[MAXCOMMANDLEN];
        CMDFXN fxn;    
    }EXECCMD;
    extern 
    
    void initializeMojocmds(void);
    CMDFXN findFxn(char *fxnname);
    
    char* setid(char *sparam, char * callname);
    char* who(char *sparam, char * callname);
    char* annc(char *sparam, char * callname);
    char* NotFound(char *sparam, char * callname);
#endif

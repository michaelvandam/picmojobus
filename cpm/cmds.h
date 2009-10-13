#ifndef cmds_H
	#define cmds_h   	
            
    #include "mojocmd.h"
    
    extern ram char cmdRespBuf[MAXPARAMLEN];
    void setErrResp(ram char * buf, const rom char * serr);
    void test1(char * port, char val); 
    //Callback fxns
    char* setport(char *sparam, char * callname);
    char* settris(char *sparam, char * callname);
    char* Blink(char *sparam, char * callname);
    char* Hello(char * sparam, char * callname);
    char* state1(char * sparam, char * callname);
    char* test(char * sparam, char * callname);
    char* setR(char *sparam, char * callname);
    char* openAll(char *sparam, char *callname);
    char* closeAll(char *sparam, char *callname);
    
    //Update Mojocmd.h with number of commands!!!!!
#endif

#line 1 "mojoparse.c"
#line 1 "mojoparse.c"
#line 1 "./mojoparse.h"

#line 3 "./mojoparse.h"

#line 1 "./mojomsg.h"

#line 3 "./mojomsg.h"
#line 4 "./mojomsg.h"
#line 5 "./mojomsg.h"
#line 6 "./mojomsg.h"
#line 7 "./mojomsg.h"
#line 8 "./mojomsg.h"
#line 9 "./mojomsg.h"
#line 10 "./mojomsg.h"
#line 11 "./mojomsg.h"
#line 12 "./mojomsg.h"
#line 13 "./mojomsg.h"
#line 14 "./mojomsg.h"
			
#line 16 "./mojomsg.h"
            
            
#line 19 "./mojomsg.h"
#line 20 "./mojomsg.h"
#line 21 "./mojomsg.h"
#line 22 "./mojomsg.h"
 
 

			
			enum {
				WAITING, 
				FIRSTSTRT, 
				SECSTRT, 
				NEWMSG, 
				CMPLTMSG 
			};	

			volatile extern char addy;

			typedef struct command{
				char text[8 ];  
				char param[16 ]; 
				char resp[16 ]; 
			} COMMAND;
			
			typedef struct message{
				volatile char * cmdptr; 
				volatile char * rbuf;  
				volatile char * sbuf;  
				volatile char * ibuf;  
			 	volatile char * cmpltmsg; 
				volatile char msg_state; 
				volatile int err;
				ram char rec_addr; 
				ram char send_addr; 
				volatile int icmds; 
				COMMAND * commands; 
			} MESSAGE;

			
			
			 
			void MojoWriteByte(char c);
			void MojoWriteRamStr(ram char *data);
			void MojoWriteRomStr(const rom char *data);
			char MojoReadByte(void);
			
			void msgReadAddrEEPROM(void); 
			void msgInit(MESSAGE *m); 
			void msgReset(MESSAGE *m); 
			void msgStoreRxByte(MESSAGE *m); 
			void msgIncPtr(MESSAGE *m); 
			void msgState2Waiting(MESSAGE *m); 
			void msgState2RecFirst(MESSAGE *m); 
			void msgState2Rec2nd(MESSAGE *m); 
			void msgState2New(MESSAGE *m); 
			void msgState2Complete(MESSAGE *m); 
			void msgCheck(MESSAGE *m); 
			void msgCpyFinal(MESSAGE *m); 
			void cmds_init(MESSAGE *m);
			void cmd_init(COMMAND *c); 
			void initializeUsart(void);  
			
			char msgRecStart(MESSAGE *m); 
			char msgRecEnd(MESSAGE *m); 
			char msgForMe(MESSAGE *m); 
			char msgIsWaiting(MESSAGE *m); 
			char msgIsFirst(MESSAGE *m); 
			char msgIs2nd(MESSAGE *m); 
			char msgIsNew(MESSAGE *m); 
			char msgIsComplete(MESSAGE *m); 
			void msgParseForCmds(MESSAGE *m); 
			void msgParseAddr(MESSAGE *m); 
			char msgAddCommand(MESSAGE * m, char * scommand, char * sparam);
			void msgSetRespParam(MESSAGE *m); 
			
			 
			void initializeMojobus(void); 
			void MsgRx(void); 
			MESSAGE * GetMsg(void); 
			void ExecCommands(void);
			void PrintCommands(void); 
			void writeFromRom(const far rom char * str); 
			void writeFromRam(ram char * str); 
			char MessageReady(void); 
			void Respond(void); 
			void ReadyForNextMsg(void); 
			void PrintCurrentMsg(void); 
			

#line 108 "./mojomsg.h"
#line 4 "./mojoparse.h"



#line 8 "./mojoparse.h"
#line 9 "./mojoparse.h"
#line 10 "./mojoparse.h"

typedef struct command{
	char text[8 ];
	char parameter[16 ];
	char response[16 ];
} COMMAND;

typedef struct message{
	char  * msg;
 	char rec_addr;
	char send_addr;
	COMMAND commands[10 ];
} MESSAGE;


extern MESSAGE * pmsg;  

#line 28 "./mojoparse.h"

#line 1 "mojoparse.c"

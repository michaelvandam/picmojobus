#ifndef mojomsg_H
	#define mojomsg_H
	        #define ENDMSG '\r'       // character signifies end of message
	        #define STARTMSG '>'          // message starts with 2 of these
	        #define CMDSEP ";"
			#define ADDRSEP2 ":"
			#define ADDRSEP1 ","
	        #define PARAMSEP "="
			#define BROADCASTADDR '0'
			#define BUFFSIZE 256
			#define MAXCOMMANDS 10
			#define MAXCOMMANDLEN 8
			#define MAXPARAMLEN 16
			
            #define ADDR_EEPROM 0x0000
            
            
            #define SETTRISDRIVER() TRISCbits.TRISC2=0
            #define DRIVEENABLE() PORTCbits.RC2=1
            #define DRIVEDISABLE() PORTCbits.RC2=0
            #define WAITFORUSART() while(Busy1USART())
 
 

			//States of message receive state machine
			enum {
				WAITING, //Waiting for new message
				FIRSTSTRT, //Received first start char wait for next
				SECSTRT, //Received 2nd start char wait for address
				NEWMSG, //Received Correct Address store message wait for end char
				CMPLTMSG //Received End char wait for message processing
			};	

			volatile extern char addy;

			typedef struct command{
				char text[MAXCOMMANDLEN];  //Text of command
				char param[MAXPARAMLEN]; //Parameter for command
				char resp[MAXPARAMLEN]; //Response for command, may be different than parameter
			} COMMAND;
			
			typedef struct message{
				volatile char * cmdptr; //Pointer to commands in message
				volatile char * rbuf;  //receive Buffer ptr
				volatile char * sbuf;  //send buffer ptr
				volatile char * ibuf;  //pointer to receiver buffer with last received byte
			 	volatile char * cmpltmsg; // Complete Message
				volatile char msg_state; //State of message
				volatile int err;
				ram char rec_addr; //Receiver address (should be me)
				ram char send_addr; //Send address should be master controller
				volatile int icmds; //Command index in command array (should not exceed MAXCOMMANDS)
				COMMAND * commands; //Pointer to array of commands with length MAXCOMMANDS
			} MESSAGE;

			
			
			/*These are private and should be used sparingly*/
			void MojoWriteByte(char c);
			void MojoWriteRamStr(ram char *data);
			void MojoWriteRomStr(const rom char *data);
			char MojoReadByte(void);
			
			void msgReadAddrEEPROM(void); //Retrieve Address from EEPROM
			void msgInit(MESSAGE *m); //Initialize Message
			void msgReset(MESSAGE *m); //Reset Message
			void msgStoreRxByte(MESSAGE *m); //Store next Byte from USART
			void msgIncPtr(MESSAGE *m); // Increment Msg Buffer pointer when necessary
			void msgState2Waiting(MESSAGE *m); // Change message state to WAITING
			void msgState2RecFirst(MESSAGE *m); //Change message state to FIRSTSTRT
			void msgState2Rec2nd(MESSAGE *m); //Change message state to SECSTRT
			void msgState2New(MESSAGE *m); //Change message state to NEWMSG
			void msgState2Complete(MESSAGE *m); //Change message state complete
			void msgCheck(MESSAGE *m); //Check character and decide state
			void msgCpyFinal(MESSAGE *m); //Copy message from RXbuffer to Complete message buffer
			void cmds_init(MESSAGE *m);
			void cmd_init(COMMAND *c); //Initialize commands in message
			void initializeUsart(void);  //Initialize USART
			
			char msgRecStart(MESSAGE *m); //Check if received char is startchar
			char msgRecEnd(MESSAGE *m); //Check if received char is endchar
			char msgForMe(MESSAGE *m); //Check is message for me	
			char msgIsWaiting(MESSAGE *m); //Check if state is waiting
			char msgIsFirst(MESSAGE *m); //Check if state is first
			char msgIs2nd(MESSAGE *m); // Check if state is 2nd
			char msgIsNew(MESSAGE *m); // Check if in new msg
			char msgIsComplete(MESSAGE *m); //Check if msg is complete
			void msgParseForCmds(MESSAGE *m); //Parse complete message for commands and params should be called after msgCpyFinal
			void msgParseAddr(MESSAGE *m); //Parse message and store sender address if applicable
			char msgAddCommand(MESSAGE * m, char * scommand, char * sparam);
			void msgSetRespParam(MESSAGE *m); //For Debuging copy command param to resp
			
			/*Implementation Functions*/
			void initializeMojobus(void); //Initilize MojoBus
			void MsgRx(void); //Read next char off usart
			MESSAGE * GetMsg(void); // Get message when message ready
			void ExecCommands(void);
			void PrintCommands(void); //For debugging
			void writeFromRom(const far rom char * str); //Write to USART For debugging
			void writeFromRam(ram char * str); //Write to USART For debugging
			char MessageReady(void); //Check is message ready for processing
			void Respond(void); // Called after executing commands, responds to sender
			void ReadyForNextMsg(void); //Reset state and wait for next message
			void PrintCurrentMsg(void); //Print For debugging
			

#endif

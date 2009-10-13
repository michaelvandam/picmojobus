/*******************************
MojoBus Implementation
*******************************/
#include "mojomsg.h"
#include "mojocmd.h"
#include "strtok_r.h"
#include "EEP.h"
#include <usart.h>
#include <string.h>
#include <delays.h>
#include <stdio.h>

volatile char addy;
volatile char msgstate = WAITING;

#pragma udata message_sec
MESSAGE msg;
#pragma udata

#pragma udata message_ptr
MESSAGE * pmsg=&msg; /* Pointer to message */
#pragma udata

#pragma udata commands
COMMAND commands[MAXCOMMANDS];
#pragma udata

COMMAND *pcmd=commands;

#pragma udata cmptbuf
volatile char cmpltmsgbuf[BUFFSIZE];
#pragma udata

#pragma udata msgbufs
volatile char msgBuffer[BUFFSIZE];

#pragma udata

#pragma udata sendbufs
volatile char sendBuffer[BUFFSIZE];
char *sendPtr= sendBuffer;
#pragma udata



void MojoWriteByte(char c) {
DRIVEENABLE();
Write1USART(c);
DRIVEDISABLE();
}

void MojoWriteRomStr(const rom char *data) {
DRIVEENABLE();
while(*data!='\0'){
    //MojoWriteByte((char)*data);
    Write1USART((char)*data);
    WAITFORUSART();
    data++;
}
DRIVEDISABLE();
}

void MojoWriteRamStr(ram char *data){
DRIVEENABLE();
Delay10KTCYx(100);
while(*data!='\0'){
    //MojoWriteByte((char)*data);
    Write1USART((char)*data);
    WAITFORUSART();
    data++;
}
DRIVEDISABLE();
}

char MojoReadByte(void) {
    char c;
    c = Read1USART();
    return c;
}



void msgReadAddrEEPROM(void) {
    Busy_eep ();
    addy = Read_b_eep(ADDR_EEPROM);
}

void msgInit(MESSAGE *m) {
	char i;
	m->err = 0;
	m->rec_addr=addy;  //Received addy is me
	m->send_addr=0;   //Sender address is null
	msgState2Waiting(m); //Set message to waiting state
	m->rbuf=msgBuffer;  //Set recieve buffer pointer to msgBuffer char array
	m->sbuf=sendBuffer; //Set send buffer pointer to sendBuffer char array
	m->cmpltmsg=cmpltmsgbuf; //Set complete message ptr to cmpltmsgbuf array
	m->commands=pcmd; //Point commands to array pointing to command array
	m->cmdptr = 0; //Set parsed command ptr to null 
	m->icmds = 0; // Set command index to 0
	//m->icmdptr=m->commands; //
	msgReset(m);  //Reset message empty string in receive buffer
	cmds_init(m); //Initialize commands
}




void msgReset(MESSAGE *m) {
	strcpypgm2ram(m->rbuf,""); //Copy empty string into messagebuffer
	strcpypgm2ram(m->sbuf,""); //Copy empty string into messagebuffer
	m->ibuf=m->rbuf; //Reset index msg pointer to begining of messagebuffer	
}

void msgStoreRxByte(MESSAGE *m) {
	*(m->ibuf) = MojoReadByte();
	//MojoWriteRamStr(m->rbuf);
	*((pmsg->ibuf)+1)='\0';
	
}

void msgRemoveTrailingCR(MESSAGE *m) {
	m->ibuf='\0';
}

void msgIncPtr(MESSAGE *m) {
	if(msgIsNew(m)) {
		m->ibuf++ ;	
	}
}

void msgState2Waiting(MESSAGE *m) {
	m->msg_state=WAITING;
}

void msgState2RecFirst(MESSAGE *m) {
	m->msg_state=FIRSTSTRT;
}

void msgState2Rec2nd(MESSAGE *m) {
	m->msg_state=SECSTRT;
}

void msgState2New(MESSAGE *m) {
	m->msg_state=NEWMSG;
}

void msgState2Complete(MESSAGE *m) {
	m->msg_state=CMPLTMSG;
}


void msgCpyFinal(MESSAGE *m) {
	strcpy(m->cmpltmsg, m->rbuf);
}


void cmds_init(MESSAGE *m) {
	int i;
	for(i=0;i<MAXCOMMANDS;i++)
		cmd_init(&(m->commands[i]));
}

void cmd_init(COMMAND *c) {
    *(c->text)='\0';
    *(c->param)='\0';
    *(c->resp)='\0';	
}



void initializeUsart(void) {
	Open1USART(USART_TX_INT_OFF &
				USART_RX_INT_ON &
				USART_ASYNCH_MODE &
				USART_EIGHT_BIT &
				USART_CONT_RX &
				USART_BRGH_LOW, 64);
    SETTRISDRIVER();
    DRIVEDISABLE();
}




char msgRecStart(MESSAGE *m) {
	if(*(m->ibuf)==STARTMSG) {
		//writeFromRom("Is Start!");
		return 1;
	} else  {
		//writeFromRom("Not Start!");
		return 0;
	}
}



char msgRecEnd(MESSAGE *m) {
	if(*(m->ibuf)==ENDMSG) {
		*(m->ibuf)='\0';
		return 1;	
	}else return 0;
}


char msgForMe(MESSAGE *m) { 
	if (*(m->ibuf) == addy || *(m->ibuf) == BROADCASTADDR) return 1;
	else return 0;
}



char msgIsWaiting(MESSAGE *m) {
	if (m->msg_state==WAITING) return 1;
	else return 0;
}


char msgIsFirst(MESSAGE *m) {
	if (m->msg_state==FIRSTSTRT) return 1;
	else return 0;
}


char msgIs2nd(MESSAGE *m) {
	if (m->msg_state==SECSTRT) return 1;
	else return 0;
}


char msgIsNew(MESSAGE *m) {
	if (m->msg_state==NEWMSG) return 1;
	else return 0;
}


char msgIsComplete(MESSAGE *m) {
	if (m->msg_state==CMPLTMSG) return 1;
	else return 0;
}





void msgCheck(MESSAGE *m) {
	switch (m->msg_state) {
		case WAITING:
			//writeFromRom("Waiting");
			if(msgRecStart(m)) {
				//writeFromRom("FIRST");
				msgState2RecFirst(m);
			}
			break;

		case FIRSTSTRT:
			
			if(msgRecStart(m)){
				//writeFromRom("Second");
				msgState2Rec2nd(m);
			} else {
				msgState2Waiting(m);
				msgReset(m);
			}
			break;
	
		case SECSTRT:
			if (msgForMe(m)) {
				//writeFromRom("New");
				msgState2New(m);
			} else {
				msgState2Waiting(m);
				msgReset(m);
			}
			//break;  //Oops

		case NEWMSG:
			if(msgRecEnd(m)) {
				//writeFromRom("Complete");
				msgState2Complete(m);
			}
			msgIncPtr(m);
			break;
			
		case CMPLTMSG:
			//Do complete message stuff here!
			//Mainloop should recognize message is complete
			//Parse it
			//Obey commands
			//Respond
			//Then return state to WAITING
			break;
			
		default: //SHOULD NOT HAPPEN! UNKNOWN STATE!
			msgState2Waiting(m);
			msgReset(m);
			break;	
	
		}
}


void msgParseAddr(MESSAGE *m) {
	int buflen;
	char * addrptr;

	addrptr = strtokpgmram( m->cmpltmsg, ADDRSEP2);
	m->cmdptr = strtokpgmram( 0, ADDRSEP2);
	buflen = strlen(addrptr);
 	if (buflen==3) {  //Received Sender and Recipient
		m->rec_addr=addrptr[0];
		m->send_addr=addrptr[2];
	} else if (buflen<3 && buflen>=1) { // ??? Only recipient, acknowledge, no response
		m->rec_addr=addrptr[0];
		m->send_addr='\0';
	} else {  //?? Unknown Malformed address.  There will be not response.
			m->rec_addr='\0';
		m->send_addr='\0';
		
	}
		
}

void msgParseForCmds(MESSAGE *m) {
	char * sparamptr;  //Ptr to parameter string
	char * scmdptr;  //Ptr to command string
	char * contxt1; //Used in strtok_r to remember context
	char * contxt2;

	int cmdCount=0;
	//MojoWriteRamStr(m->cmdptr);
	//MojoWriteRomStr("\r\n");
	m->cmdptr = strtok_r(m->cmdptr,CMDSEP, &contxt1);
	
    while(m->cmdptr) {
		scmdptr = strtok_r(m->cmdptr,PARAMSEP,&contxt2);
		
		sparamptr = strtok_r(0,PARAMSEP,&contxt2);
		
		m->cmdptr = strtok_r(0,CMDSEP, &contxt1);  //Move cmdptr to next command!
 		
 		//Uncomment to print commands as they are parsed!
 		/*
 		MojoWriteRomStr("CMD:");
 		MojoWriteRamStr(scmdptr);
 		MojoWriteRomStr("\r\n");
 		if(sparamptr!=0) {
 		MojoWriteRomStr("PARAM: ");
 		MojoWriteRamStr(sparamptr);
 		MojoWriteRomStr("\r\n");
 		}
 		*/
 		if(!(msgAddCommand(m, scmdptr, sparamptr))) break;
	}
}

char msgAddCommand(MESSAGE * m, char * scommand, char * sparam) {
	if (m->icmds >= MAXCOMMANDS) return 0; //Check to see if there is room for commands
	
	if (strlen(scommand)>MAXCOMMANDLEN) return 0;  // Check to see if command len is valid
	
	if (strlen(sparam)>MAXPARAMLEN) return 0; // Check to see if parameter len is valid
	
	//Everything checks out! Lets add the commands to the message to be executed

    
    if(scommand==0)
	   strcpypgm2ram(m->commands[m->icmds].text, "");
	else 
	    strcpy(m->commands[m->icmds].text, scommand);
	
	if (sparam==0)
	    strcpypgm2ram(m->commands[m->icmds].param, "");
	else
	    strcpy(m->commands[m->icmds].param, sparam);

	m->icmds++; //Increment command index
	return 1;
}




char * msgGetsResponse(MESSAGE *m) {
    int i = 0;  //Index for looping over commands
    
    sprintf(m->sbuf,">>%c,%c:", m->send_addr, addy); // Add address to send buffer
    
    for(i=0;i<MAXCOMMANDS;i++){   //Loop through commands
        if (!(*(m->commands[i].text)=='\0')){
            strcatpgm2ram(m->sbuf, "*");  
            strcat(m->sbuf,m->commands[i].text);
        
            if (!(*(m->commands[i].resp)=='\0')){
                strcatpgm2ram(m->sbuf,"=");
                strcat(m->sbuf,m->commands[i].resp);
            }
            
            strcatpgm2ram(m->sbuf,";");          
        }
    }
    
    strcatpgm2ram(m->sbuf, "\r");     
}

void msgSetRespParam(MESSAGE *m) {
    int i = 0;  //Index for looping over commands
    for(i=0;i<MAXCOMMANDS;i++){
        strcat(m->commands[i].resp,m->commands[i].param);
    }    
}



void initializeMojobus(void) {
	msgInit(pmsg);
	initializeUsart();
	//To do!!! Read address from EEPROM!!!!
	msgReadAddrEEPROM();
	//addy='a';  //Set address
}



/*******************************
Check Flag to see if a new message
is available! Returns 1 or 0
*******************************/
char MessageReady(void) {
	if (msgIsComplete(pmsg)) return 1;
	else return 0;
}

/*******************************
Receive Char from USART and 
decide what to do with it
*******************************/
void MsgRx(void)  
{
	msgStoreRxByte(pmsg); //Get byte from USART
	msgCheck(pmsg); //Check to see if message is for me and valid
	//PORTB = pmsg->msg_state;  //Uncomment to show state on portB
}

/*******************************
Get New Message
	Called after MessageReady
*******************************/
MESSAGE * GetMsg(void) {  //
	msgCpyFinal(pmsg); //Copy messagebuffer to msg var
	msgReset(pmsg);
	msgParseAddr(pmsg);
	msgParseForCmds(pmsg);
	return pmsg;
}

/*******************************
For DEBUGGING
After receiving message Print
commands
*******************************/
void PrintCommands(void) {
	int i;
	COMMAND *cmd;

	
	MojoWriteRomStr("\nRec:\t");
	MojoWriteByte(pmsg->rec_addr);
	MojoWriteRomStr("\nSend:\t");
	MojoWriteByte(pmsg->send_addr);
	MojoWriteRomStr("\n\n");
	
	
	for(i=0;i<MAXCOMMANDS;i++){
		MojoWriteRomStr("\n***************************\n");
		cmd = &(pmsg->commands[i]);
		MojoWriteRomStr("\nCMD:\t");
		MojoWriteRamStr(cmd->text);
		MojoWriteRomStr("\n");
		MojoWriteRomStr("\nParam:\t");
		MojoWriteRamStr(cmd->param);
	}	
}


/*******************************
For DEBUGGING
After receiving message Print
commands
*******************************/
void ExecCommands(void) {
	int i;
	char *temp; //Hold function response
	MESSAGE *msg;
	COMMAND *cmd;
	CMDFXN cmdFxn;
	
	msg = GetMsg();  //Get msg
	//PrintCommands();
	
    for(i=0;i<MAXCOMMANDS;i++){
        cmdFxn = findFxn(msg->commands[i].text);
        temp = (*cmdFxn)(msg->commands[i].param, msg->commands[i].text);
        strcpy(msg->commands[i].resp, temp);
    }    

}

/*******************************
Respond to commands
*******************************/
void Respond(void) {
    char * response;  
    response = msgGetsResponse(pmsg);
    MojoWriteRamStr(response);
}

/*******************************
Set state so we can wait for next message
	Call after processed current message
*******************************/
void ReadyForNextMsg(void) {
    DRIVEDISABLE(); //Diable rs485 driver
	msgState2Waiting(pmsg);	// Since message is stored return state to WAITING and wait for next message
	msgReset(pmsg);
	pmsg->cmdptr = pmsg->rbuf;
	pmsg->icmds=0;
	cmds_init(pmsg);
}


/************************************
Used for debugging 
Print out the current receiving buffer
************************************/
void PrintCurrentMsg(void) {
	MojoWriteRamStr(pmsg->rbuf);
}


/************************************
Write to USART and display to PORTB 
for troubleshooting
************************************/
void writeFromRom(const far rom char * str) {
	do {
		while(Busy1USART())
			;
		MojoWriteByte(*str);
		PORTBbits.RB7=~PORTBbits.RB7;
		Delay10KTCYx(5);
		str++;
		
	} while(!(*str=='\0'));
	
} //~ End writeFromRom
void writeFromRam(char * str) {
	do {
		while(Busy1USART())
			;
		MojoWriteByte(str);
		PORTBbits.RB7=~PORTBbits.RB7;
		Delay10KTCYx(50);
		str++;
		
	} while(!(*str=='\0'));
}

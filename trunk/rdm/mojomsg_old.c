/*******************************
MojoBus Implementation
*******************************/
#include "mojomsg.h"
#include <usart.h>
#include <string.h>
#include <delays.h>

char addy;
volatile char msgstate = WAITING;

#pragma udata message_sec
MESSAGE msg;
MESSAGE * pmsg=&msg; /* Pointer to message */

#pragma udata messagebufs
volatile char cmpltmsg[BUFFSIZE];
volatile char msgBuffer[BUFFSIZE];
char *msgPtr = msgBuffer;

#pragma udata sendbufs
volatile char sendBuffer[BUFFSIZE];
char *sendPtr= sendBuffer;
#pragma udata

void msg_init(MESSAGE *m) {
	char i;
	m->rec_addr=0;
	m->send_addr=0;
	msgState2Waiting(m);
	m->rbuf=msgBuffer;
	m->sbuf=sendBuffer;
	m->cmpltmsg=cmpltmsg;
	reset_msg(m);
	cmd_init(&(m->commands[0]));
	//for(i=0;i<MAXCOMMANDS;i++){
	//	cmd_init(m->commands[i]);
	//}

}

void reset_msg(MESSAGE *m) {
	strcpypgm2ram(m->rbuf,""); //Copy empty string into messagebuffer
	m->ibuf=m->rbuf; //Reset index pointer to begining of messagebuffer	
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
	strcpy(m->rbuf, m->cmpltmsg);
}


void cmd_init(COMMAND *c) {
	strcpypgm2ram(c->text,"");
	strcpypgm2ram(c->param,"");
	strcpypgm2ram(c->resp,"");	
}


/***************************************
Setup code for USART
***************************************/
void initializeUsart(void) {
	Open1USART(USART_TX_INT_OFF &
				USART_RX_INT_ON &
				USART_ASYNCH_MODE &
				USART_EIGHT_BIT &
				USART_CONT_RX &
				USART_BRGH_HIGH, 64);
}

/***************************************
Setup code for mojo bus
***************************************/
void initializeMojobus(void) {
	msg_init(pmsg);
	initializeUsart();
	//To do!!! Read address from EEPROM!!!!
	addy='a';  //Set address
}



/***************************************
Functions to check message status
***************************************/

/***************************************
Received Correct Start char
***************************************/
char msgRecStart(MESSAGE *m) {
	if(*(m->ibuf)==STARTMSG) return 1;
	else return 0;
}


/***************************************
Received End Character
***************************************/
char msgRecEnd(MESSAGE *m) {
	if(*(m->ibuf)==ENDMSG) return 1;
	else return 0;
}

/***************************************
Check if msg for me
***************************************/

char msgForMe(MESSAGE *m) { 
	if (*(m->ibuf) == addy) return 1;
	else return 0;
}


/***************************************
Check if status is waiting
***************************************/
char msgIsWaiting(MESSAGE *m) {
	if (m->msg_state==WAITING) return 1;
	else return 0;
}

/***************************************
Check if status if first
***************************************/
char msgIsFirst(MESSAGE *m) {
	if (m->msg_state==FIRSTSTRT) return 1;
	else return 0;
}

/***************************************
Check if status is second
***************************************/
char msgIs2nd(MESSAGE *m) {
	if (m->msg_state==SECSTRT) return 1;
	else return 0;
}

/***************************************
Check if status new message and recording
***************************************/
char msgIsNew(MESSAGE *m) {
	if (m->msg_state==NEWMSG) return 1;
	else return 0;
}

/***************************************
Check if msg is complete
***************************************/
char msgIsComplete(MESSAGE *m) {
	if (m->msg_state==CMPLTMSG) return 1;
	else return 0;
}


/***************************************
Received New Message
***************************************/
char MessageReady(void) {
	if (msgIsComplete(pmsg)) return 1;
	else return 0;
}


/***************************************
Check buffer to see of new message is being recieved
Move to State as necessary
***************************************/
void msgCheck(MESSAGE *m) {

	if(!(msgIsNew(m))) {  //If not a New Message
		if ( msgRecStart(m) && msgIsWaiting(m)){ //Check to see if recieve start character and in default state
			msgState2RecFirst(m);	// If we do change state to First Start char state
			
		}
		else if (msgRecStart(m) &&  msgIsFirst(m)) { //Check to see if recieve start character and in 1st state 
			msgState2Rec2nd(m);	// Change to second state
			
		}
		else if (msgForMe(m) && msgIs2nd(m)) { // Check if address is right
			msgState2New(m);	// Move to new msg state
			
		}
		else { // Else not for me or not new message go back to default state
			msgState2Waiting(m); //Set waiting state
			reset_msg(m); //Reset message buffer and pointer
		}
	}

	else { // In New Message! 
		if (msgRecEnd(m)) {  //Check to see if we recieve a end char
			msgState2Complete(m); // If we do move to complete message state
		}
		
	}	
	
}



/*******************************
Character from USART check to see if new message has arrived
*******************************/
void MsgRx(void)  
{
	static char tmp;
	if (!(msgIsComplete(pmsg))) { // Message still being processed ignore
		if (!(msgIsWaiting(pmsg))) pmsg->ibuf++ ;  // Increment pointer if start char received
		*(pmsg->ibuf) = Read1USART();  //Read byte from USART
		*((pmsg->ibuf)+1)='\0'; //Terminate message buffer
		msgCheck(pmsg); //Check to see if message is for me and valid
		PORTB=pmsg->msg_state; // Display state on portB <for debug>	
	} else { // Ignore character until message has been processed
		tmp = Read1USART(); //Discard!
	}

	if (msgIsComplete(pmsg))
		PrintCurrentMsg();
}

/*******************************
Get New Message
	Called after MessageReady
*******************************/
char * GetMsg(void) {  //
	msgCpyFinal(pmsg); //Copy messagebuffer to msg var
	reset_msg(pmsg); // 
	return pmsg->cmpltmsg;
}

/*******************************
Set state so we can wait for next message
	Call after processed current message
*******************************/
void ReadyForNextMsg(void) {
	msgState2Waiting(pmsg);	// Since message is stored return state to WAITING and wait for next message
}


void PrintCurrentMsg(void) {
writeFromRam(pmsg->rbuf);
}


/************************************
Write to USART and display to PORTB 
for troubleshooting
************************************/
void writeFromRom(const far rom char * str) {
	do {
		while(Busy1USART())
			;
		putc1USART(*str);
		PORTBbits.RB7=~PORTBbits.RB7;
		Delay10KTCYx(5);
		str++;
		
	} while(!(*str=='\0'));
	
} //~ End writeFromRom


void writeFromRam(char * str) {
	do {
		while(Busy1USART())
			;
		putc1USART(*str);
		PORTBbits.RB7=~PORTBbits.RB7;
		Delay10KTCYx(50);
		str++;
		
	} while(!(*str=='\0'));
}
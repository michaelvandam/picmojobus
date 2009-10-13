#include <p18cxxx.h>
#include <stdio.h>
#include <delays.h>
#include <usart.h>
#include <timers.h>
#include "mojomsg.h"
#include "mojocmd.h"
#include "CPMcmds.h"

/************************************
Set Config Registers
************************************/
#pragma config OSC = HSPLL //High speed osc >4Mhz (10MHz)
#pragma config WDT = OFF //Turn off Watch dog timer
#pragma config LVP = OFF // Turn off Low volatge programming
#pragma config DEBUG = ON //Turn on debug

/************************************
Function Prototypes
************************************/
void setup(void); //Setup fxn
void rx_handler(void); //High Priority Receive handler
//void int_handler(void); //Low Priority Handler
/************************************
Main
************************************/
void main(void)
{
	setup();
	MojoWriteRomStr("Initializing...\r\n");
	
	//Mainloop
	while(1) {
		if (MessageReady()) { //Wait for message to become available
			ExecCommands(); //Execute Commands
			Respond(); // Respond to controller
			ReadyForNextMsg(); // Set device ready for new message					
        //Dont hangout in here or we will not see next message
   		}
        CPMRun();	
	}		
} //~ End Main


/************************************
Setup code for high level interrupts
************************************/

#pragma code rx_interrupt = 0x8
void rx_int(void)
{
	_asm GOTO rx_handler _endasm
}
#pragma code //~ End setup code for interrupt


/************************************
Interrupt Handler on USART receive
************************************/
#pragma interrupt rx_handler
void rx_handler(void)
{
	MsgRx();  // Attempt to read mojo message
	PIR1bits.RCIF = 0; //Reset receive flag
} //~ End interrupt handler


/*
#pragma code low_vector_section=0x18
void low_int(void) {
    _asm GOTO int_handler  _endasm
}

#pragma code 

#pragma interruptlow int_handler
void int_handler(void) {
    
    if(PUMPTMRFLAG==1) {
        AddPumpTick(); //Step forward pump timers
        RunPump(); //Look through pumps and conduct required actions
        PUMPTMRFLAG=0; //Reset pump timer flag
    }
}
*/


/************************************
Setup Code For MOJO Example
************************************/
void setup(void)
{
	initializeMojobus(); //Initialise Mojobus and USART
	initializeMojocmds(); //Initialize Mojocmds
    CPMSetup();
    	
	TRISB=0;TRISE=0;TRISD=0;TRISJ=0;TRISA=0;  //Set ports to output
	PORTB=0;PORTE=0;PORTD=0;PORTJ=0;PORTA=0; //Set default value to low
	
	RCONbits.IPEN=1; //Enable interrupt priorities
	IPR1bits.RCIP=1; //Enable receive interrupts
	//INTCONbits.GIEH=1; //Enable high priority interrupts
	INTCONbits.GIE=1;
	//INTCONbits.GIEL=1; //Enable low priority interrupts, required for running pumps
//	INTCONbits.TMR0IE=1; //Enable timer 0 interrupt, also required for running pumps
	//StartPumpTimer(); //Required for pumps to function correctly
} // End Setup for mojo example



#ifndef mojoparse_H
#define mojoparse_H

#include "mojomsg.h"


#define MAXCOMMANDS 15
#define MAXCOMMANDLEN 10
#define MAXPARAMLEN 10

typedef struct command{
	char text[MAXCOMMANDLEN];
	char parameter[MAXPARAMLEN];
	char response[MAXPARAMLEN];
} COMMAND;

typedef struct message{
	char  * msg;
 	char rec_addr;
	char send_addr;
	COMMAND commands[MAXCOMMANDS];
} MESSAGE;


extern MESSAGE * pmsg; /* Parsed message */

#endif


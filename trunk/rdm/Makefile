# MPLAB IDE generated this makefile for use with GNU make.
# Project: RDM-mojo-rs485.mcp
# Date: Sun Sep 20 23:39:39 2009

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

RDM-mojo-rs485.cof : asciiConvert.o cmds.o isNumeric.o main.o mojocmd.o mojoerror.o mojomsg.o ports.o strtok_r.o RDMcmds.o
	$(LD) /l"C:\MCC18\lib" /k"C:\MCC18\lkr" "18f8722.lkr" "asciiConvert.o" "cmds.o" "isNumeric.o" "main.o" "mojocmd.o" "mojoerror.o" "mojomsg.o" "ports.o" "strtok_r.o" "RDMcmds.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\RDM-mojo-rs485.cof" /M"C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\RDM-mojo-rs485.map" /W

asciiConvert.o : asciiConvert.c asciiConvert.h asciiConvert.c
	$(CC) -p=18F8722 /i"C:\MCC18\h" "asciiConvert.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\asciiConvert.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

cmds.o : cmds.c mojomsg.h mojocmd.h cmds.h asciiConvert.h ports.h ../../../../../MCC18/h/usart.h ../../../../../MCC18/h/stdio.h ../../../../../MCC18/h/string.h ../../../../../MCC18/h/stdlib.h cmds.c mojoerror.h ../../../../../MCC18/h/p18cxxx.h ../../../../../MCC18/h/p18f8722.h ../../../../../MCC18/h/pconfig.h ../../../../../MCC18/h/stdarg.h ../../../../../MCC18/h/stddef.h
	$(CC) -p=18F8722 /i"C:\MCC18\h" "cmds.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\cmds.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

isNumeric.o : isNumeric.c ../../../../../MCC18/h/ctype.h isNumeric.c
	$(CC) -p=18F8722 /i"C:\MCC18\h" "isNumeric.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\isNumeric.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

main.o : main.c ../../../../../MCC18/h/stdio.h ../../../../../MCC18/h/delays.h ../../../../../MCC18/h/usart.h ../../../../../MCC18/h/timers.h mojomsg.h mojocmd.h cmds.h RDMcmds.h main.c ../../../../../MCC18/h/p18cxxx.h ../../../../../MCC18/h/p18f8722.h ../../../../../MCC18/h/stdarg.h ../../../../../MCC18/h/stddef.h ../../../../../MCC18/h/pconfig.h
	$(CC) -p=18F8722 /i"C:\MCC18\h" "main.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\main.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

mojocmd.o : mojocmd.c mojomsg.h mojocmd.h cmds.h RDMcmds.h ../../../../../MCC18/h/usart.h ../../../../../MCC18/h/stdio.h ../../../../../MCC18/h/string.h ../../../../../MCC18/h/EEP.h ../../../../../MCC18/h/delays.h ../../../../../MCC18/h/ctype.h mojocmd.c mojoerror.h ../../../../../MCC18/h/pconfig.h ../../../../../MCC18/h/p18cxxx.h ../../../../../MCC18/h/p18f8722.h ../../../../../MCC18/h/stdarg.h ../../../../../MCC18/h/stddef.h
	$(CC) -p=18F8722 /i"C:\MCC18\h" "mojocmd.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\mojocmd.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

mojoerror.o : mojoerror.c mojomsg.h mojoerror.h
	$(CC) -p=18F8722 /i"C:\MCC18\h" "mojoerror.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\mojoerror.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

mojomsg.o : mojomsg.c mojomsg.h mojocmd.h ../../../../../MCC18/h/string.h strtok_r.h ../../../../../MCC18/h/EEP.h ../../../../../MCC18/h/usart.h ../../../../../MCC18/h/delays.h ../../../../../MCC18/h/stdio.h mojomsg.c ../../../../../MCC18/h/stddef.h ../../../../../MCC18/h/pconfig.h ../../../../../MCC18/h/p18cxxx.h ../../../../../MCC18/h/p18f8722.h ../../../../../MCC18/h/stdarg.h
	$(CC) -p=18F8722 /i"C:\MCC18\h" "mojomsg.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\mojomsg.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

ports.o : ports.c ports.h ../../../../../MCC18/h/string.h strtok_r.h ../../../../../MCC18/h/ctype.h ../../../../../MCC18/h/stdlib.h ../../../../../MCC18/h/usart.h ports.c ../../../../../MCC18/h/p18cxxx.h ../../../../../MCC18/h/p18f8722.h ../../../../../MCC18/h/stddef.h ../../../../../MCC18/h/pconfig.h
	$(CC) -p=18F8722 /i"C:\MCC18\h" "ports.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\ports.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

strtok_r.o : strtok_r.c ../../../../../MCC18/h/string.h strtok_r.h ../../../../../MCC18/h/usart.h strtok_r.c ../../../../../MCC18/h/stddef.h ../../../../../MCC18/h/pconfig.h ../../../../../MCC18/h/p18cxxx.h ../../../../../MCC18/h/p18f8722.h
	$(CC) -p=18F8722 /i"C:\MCC18\h" "strtok_r.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\strtok_r.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

RDMcmds.o : RDMcmds.c mojomsg.h mojocmd.h cmds.h RDMcmds.h ../../../../../MCC18/h/string.h asciiConvert.h ports.h ../../../../../MCC18/h/usart.h strtok_r.h RDMcmds.c mojoerror.h ../../../../../MCC18/h/stddef.h ../../../../../MCC18/h/p18cxxx.h ../../../../../MCC18/h/p18f8722.h ../../../../../MCC18/h/pconfig.h
	$(CC) -p=18F8722 /i"C:\MCC18\h" "RDMcmds.c" -fo="C:\Documents and Settings\hherman\My Documents\PIC\RDM-mojo-rs485\RDMcmds.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "asciiConvert.o" "cmds.o" "isNumeric.o" "main.o" "mojocmd.o" "mojoerror.o" "mojomsg.o" "ports.o" "strtok_r.o" "RDMcmds.o" "RDM-mojo-rs485.cof" "RDM-mojo-rs485.hex"


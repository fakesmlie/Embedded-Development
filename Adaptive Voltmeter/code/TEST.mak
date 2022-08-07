CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -D_EE_EXTIO -DATMega1280  -l -g -MLongJump -MHasMul -MEnhanced -Wf-use_elpm 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x20000 -ucrtatmega.o -bfunc_lit:0xe4.0x20000 -dram_end:0x21ff -bdata:0x200.0x21ff -dhwstk_size:30 -beeprom:0.4096 -fihx_coff -S2
FILES = main.o led.o key.o Nixie.o ADC.o UART.o 

TEST:	$(FILES)
	$(CC) -o TEST $(LFLAGS) @TEST.lk   -lcatm128
main.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\AVRdef.h .\led.h .\key.h .\Nixie.h .\adc.h .\uart.h
main.o:	main.c
	$(CC) -c $(CFLAGS) main.c
led.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\led.h
led.o:	led.c
	$(CC) -c $(CFLAGS) led.c
key.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\key.h
key.o:	key.c
	$(CC) -c $(CFLAGS) key.c
Nixie.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\Nixie.h .\key.h
Nixie.o:	Nixie.c
	$(CC) -c $(CFLAGS) Nixie.c
ADC.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\adc.h .\Nixie.h
ADC.o:	ADC.c
	$(CC) -c $(CFLAGS) ADC.c
UART.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\UART.h
UART.o:	UART.c
	$(CC) -c $(CFLAGS) UART.c

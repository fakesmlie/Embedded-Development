/*
  isp.c - part of USBasp

  Autor..........: Thomas Fischl <tfischl@gmx.de> 
  Description....: Provides functions for communication/programming
                   over ISP interface
  Licence........: GNU GPL v2 (see Readme.txt)
  Creation Date..: 2005-02-23
  Last change....: 2007-07-23
*/

#include <avr/io.h>
#include "isp.h"
#include "clock.h"

#define spiHWdisable() SPCR = 0

extern uchar prog_speed;
extern uchar chip_type;

void spiHWenable() {
	switch(prog_speed){	
		case 5 :
		  /* enable SPI, master, 1.5MHz SCK */
		  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
		  SPSR = (1 << SPI2X);
		  break;
		case 4 :
		  /* enable SPI, master, 750kHz SCK */
		  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
		  SPSR = 0;
		  break;
		case 3 :
		  /* enable SPI, master, 375kHz SCK */
		  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1);
		  SPSR = (1 << SPI2X);
		  break;
		default :
	  	/* enable SPI, master, 98.75kHz SCK */
	  	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
	  	SPSR = 0;
	}
}

void ispSetSCKOption() {
	
  if (prog_speed == 1) {

    /* use software spi */
    spiHWdisable();
    ispTransmit = ispTransmit_sw;
    
  } else {

    /* use hardware spi */
    ispTransmit = ispTransmit_hw;
  }  
}
  
void ispDelay() {

  uint8_t starttime = TIMERVALUE;
  while ((uint8_t) (TIMERVALUE - starttime) < 12) { }
}

void ispConnect() {

  /* all ISP pins are inputs before */
  /* now set output pins */
  ISP_DDR |= (1 << ISP_RST) | (1 << ISP_SCK) | (1 << ISP_MOSI);

	if(chip_type == 0){
	  /* reset device */
	  ISP_OUT &= ~(1 << ISP_RST);   /* RST low */
	  ISP_OUT &= ~(1 << ISP_SCK);   /* SCK low */
	
	  /* positive reset pulse > 2 SCK (target) */
	  clockWait(30);
	  ISP_OUT |= (1 << ISP_RST);    /* RST high */
	  clockWait(30);                
	  ISP_OUT &= ~(1 << ISP_RST);   /* RST low */
	}else{
	  /* reset device */
	  ISP_OUT |= (1 << ISP_RST);   /* RST high */
	  ISP_OUT &= ~(1 << ISP_SCK);   /* SCK low */
	
	  /* positive reset pulse > 2 SCK (target) */
	  clockWait(30);
	  ISP_OUT &= ~(1 << ISP_RST);    /* RST low */
	  clockWait(30);                
	  ISP_OUT |= (1 << ISP_RST);   /* RST high */
	}
	
  if (ispTransmit == ispTransmit_hw) {
    spiHWenable();
  }
}

void ispDisconnect() {
  
  /* set all ISP pins inputs */
  ISP_DDR &= ~((1 << ISP_RST) | (1 << ISP_SCK) | (1 << ISP_MOSI));
  /* switch pullups off */
  ISP_OUT &= ~((1 << ISP_RST) | (1 << ISP_SCK) | (1 << ISP_MOSI));

  /* disable hardware SPI */
  spiHWdisable();
}

uchar ispTransmit_sw(uchar send_byte) {

  uchar rec_byte = 0;
  uchar i;
  for (i = 0; i < 8; i++) {

    /* set MSB to MOSI-pin */
    if ((send_byte & 0x80) != 0) {
      ISP_OUT |= (1 << ISP_MOSI);  /* MOSI high */
    } else {
      ISP_OUT &= ~(1 << ISP_MOSI); /* MOSI low */
    }
    /* shift to next bit */
    send_byte  = send_byte << 1;

    /* receive data */
    rec_byte = rec_byte << 1;
    if ((ISP_IN & (1 << ISP_MISO)) != 0) {
      rec_byte++;
    }

    /* pulse SCK */
    ISP_OUT |= (1 << ISP_SCK);     /* SCK high */
    ispDelay();
    ISP_OUT &= ~(1 << ISP_SCK);    /* SCK low */
    ispDelay();
  }
    
  return rec_byte;
}

uchar ispTransmit_hw(uchar send_byte) {
  SPDR = send_byte;
  
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}
    
uchar ispEnterProgrammingMode() {
  uchar check;
  uchar count = 32;

  while (count--) {
    ispTransmit(0xAC);
    ispTransmit(0x53);
    if(chip_type == 0){
	    check = ispTransmit(0);
	    ispTransmit(0);	    
	    if (check == 0x53) {
	      return 0;
	    }
	  }else{
	  	ispTransmit(0);
	    check = ispTransmit(0);        
	    if (check == 0x69) {
	      return 0;
	    }	  
	  }

    spiHWdisable();
    
    /* pulse SCK */
    ISP_OUT |= (1 << ISP_SCK);     /* SCK high */
    ispDelay();
    ISP_OUT &= ~(1 << ISP_SCK);    /* SCK low */
    ispDelay();

    if (ispTransmit == ispTransmit_hw) {
      spiHWenable();
    }
  
  }
  
  return 1;  /* error: device dosn't answer */
}

uchar ispReadFlash(unsigned long address) {
	if(chip_type == 0){
	  ispTransmit(0x20 | ((address & 1) << 3));
	  ispTransmit(address >> 9);
	  ispTransmit(address >> 1);
	}else{
	  ispTransmit(0x20);
	  ispTransmit(address >> 8);
	  ispTransmit(address);
	}
  return ispTransmit(0);
}


uchar ispWriteFlash(unsigned long address, uchar data, uchar pollmode) {

  /* 0xFF is value after chip erase, so skip programming 
  if (data == 0xFF) {
    return 0;
  }
  */
  uint8_t starttime;
  
	if(chip_type == 1){
	  ispTransmit(0x40);
	  ispTransmit(address >> 8);
	  ispTransmit(address);
	  ispTransmit(data);
	  starttime = TIMERVALUE;
  	while ((uint8_t) (TIMERVALUE - starttime) < 84) { }
	  return 0;
	}

  ispTransmit(0x40 | ((address & 1) << 3));
  ispTransmit(address >> 9);
  ispTransmit(address >> 1);
  ispTransmit(data);

  if (pollmode == 0)
    return 0;

  if (data == 0x7F) {
    clockWait(15); /* wait 4,8 ms */
    return 0;
  } else {

    /* polling flash */
    uchar retries = 30;
    starttime = TIMERVALUE;
    while (retries != 0) {
      if (ispReadFlash(address) != 0x7F) {
	return 0;
      };
      
      if ((uint8_t) (TIMERVALUE - starttime) > CLOCK_T_320us) {
	starttime = TIMERVALUE;
	retries --;
      }

    }
    return 1; /* error */
  }

}


uchar ispFlushPage(unsigned long address, uchar pollvalue) {  
  
  if(chip_type == 1)return 0;
  	  	
	ispTransmit(0x4C);
	ispTransmit(address >> 9);
	ispTransmit(address >> 1);
	ispTransmit(0);

  if (pollvalue == 0xFF) {
    clockWait(15);
    return 0;
  } else {

    /* polling flash */
    uchar retries = 30;
    uint8_t starttime = TIMERVALUE;

    while (retries != 0) {
      if (ispReadFlash(address) != 0xFF) {
	return 0;
      };

      if ((uint8_t) (TIMERVALUE - starttime) > CLOCK_T_320us) {
	starttime = TIMERVALUE;
	retries --;
      }

    }

    return 1; /* error */
  }
    
}


uchar ispReadEEPROM(unsigned int address) {
	
	if(chip_type == 1)return 0;
		
  ispTransmit(0xA0);
  ispTransmit(address >> 8);
  ispTransmit(address);
  return ispTransmit(0);
}


uchar ispWriteEEPROM(unsigned int address, uchar data) {
	
	if(chip_type == 1)return 0;
		
  ispTransmit(0xC0);
  ispTransmit(address >> 8);
  ispTransmit(address);
  ispTransmit(data);

  clockWait(30); // wait 9,6 ms 

  return 0;
  /* 
  if (data == 0xFF) {
    clockWait(30); // wait 9,6 ms 
    return 0;
  } else {

    // polling eeprom 
    uchar retries = 30; // about 9,6 ms 
    uint8_t starttime = TIMERVALUE;

    while (retries != 0) {
      if (ispReadEEPROM(address) != 0xFF) {
	return 0;
      };

      if ((uint8_t) (TIMERVALUE - starttime) > CLOCK_T_320us) {
	starttime = TIMERVALUE;
	retries --;
      }

    }
    return 1; // error 
  }
  */

}

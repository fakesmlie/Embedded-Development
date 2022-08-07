#include"iom16v.h"
#include"macros.h"
#include"led.h"



/*** LED��ʼ������ ***/
/******************************************************************************/
void LED_Init(void)
{ 
 	DDRB|=BIT(PB2);    //PB2�˿ڽ�����Ϊ����˿�   1
	DDRB|=BIT(PB3);    //PB3�˿ڽ�����Ϊ����˿�   1
	DDRB|=BIT(PB4);    //PB4�˿ڽ�����Ϊ����˿�   1
	PORTB|=BIT(PB2);  // 1���1
	PORTB|=BIT(PB3);  // 1
	PORTB|=BIT(PB4);  // 1
//	DDRB=0x1c;   //0001 1100
//	PORTB=0x1c;  //0001 1100
/*
    PORTB&=~BIT(2);   //����LED�ƴ��� LED1 LED2 LED3
	PORTB&=~BIT(3);   
	PORTB&=~BIT(4);
	PORTB|=BIT(4);   //��LED����   
*/
}

void LED_open(unsigned char sw)
{
switch(sw)		//λ�����
	{
		case 1:PORTB&=~BIT(2);PORTB|=BIT(3);PORTB|=BIT(4);break;
		case 2:PORTB|=BIT(2);PORTB&=~BIT(3);PORTB|=BIT(4);break;
		case 3:PORTB|=BIT(2);PORTB|=BIT(3);PORTB&=~BIT(4);break;
	}

}

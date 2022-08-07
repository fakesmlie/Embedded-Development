#include"iom16v.h"
#include"macros.h"
#include"led.h"



/*** LED初始化函数 ***/
/******************************************************************************/
void LED_Init(void)
{ 
 	DDRB|=BIT(PB2);    //PB2端口皆设置为输出端口   1
	DDRB|=BIT(PB3);    //PB3端口皆设置为输出端口   1
	DDRB|=BIT(PB4);    //PB4端口皆设置为输出端口   1
	PORTB|=BIT(PB2);  // 1输出1
	PORTB|=BIT(PB3);  // 1
	PORTB|=BIT(PB4);  // 1
//	DDRB=0x1c;   //0001 1100
//	PORTB=0x1c;  //0001 1100
/*
    PORTB&=~BIT(2);   //电亮LED灯代码 LED1 LED2 LED3
	PORTB&=~BIT(3);   
	PORTB&=~BIT(4);
	PORTB|=BIT(4);   //关LED代码   
*/
}

void LED_open(unsigned char sw)
{
switch(sw)		//位码输出
	{
		case 1:PORTB&=~BIT(2);PORTB|=BIT(3);PORTB|=BIT(4);break;
		case 2:PORTB|=BIT(2);PORTB&=~BIT(3);PORTB|=BIT(4);break;
		case 3:PORTB|=BIT(2);PORTB|=BIT(3);PORTB&=~BIT(4);break;
	}

}

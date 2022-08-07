#include"iom16v.h"
#include"macros.h"
#include"Nixie.h"
#include"key.h"



//数码管段码表  //共阳极数码管
const unsigned char  NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};// 0~9
//unsigned char const NixieTable[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00};// 0~9

//extern unsigned char NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};// 0~9

void Nixie_Init(void)
{


 	MCUCSR|=(1<<7);
    MCUCSR|=(1<<7);
    DDRC=0xff;       // 配置PC为输出   1111 1111
    PORTC=0xff;      //配置PC输出低电平    1111 1111  //低电平进行段选
	DDRA|=BIT(PA4);  //配置PA4为输出
	DDRA|=BIT(PA5);
	DDRA|=BIT(PA6);
	DDRA|=BIT(PA7); 
	//DDRA=0xf0;    // 配置PA为输出   1111 0000
	//PORTA=0x00;
	PORTA&=~BIT(PA4);  //  0
	PORTA&=~BIT(PA5);  //  0
	PORTA&=~BIT(PA6);  //  0
	PORTA&=~BIT(PA7);  //  0
 //   PORTA=0x00;   //配置PA输出高电平       0000 0000  高电平选中，所以我们要配置为低电平

}



void Nixie(unsigned char Location,unsigned char Number)
{
	switch(Location)		//位码输出
	{
		case 1:PORTA|=BIT(4);PORTC=NixieTable[Number]+0x80;break;
		case 2:PORTA|=BIT(5);PORTC=NixieTable[Number];break;
		case 3:PORTA|=BIT(6);PORTC=NixieTable[Number];break;
		case 4:PORTA|=BIT(7);PORTC=NixieTable[Number];break;
	}
	//PORTC=NixieTable[Number]+0x80;	//段码输出+0x80
	delay_ms(1);   //显示一会
	//PORTC=0xff;   //消影
	//PORTA=0x00;
	PORTA&=~BIT(PA4);  //  0
	PORTA&=~BIT(PA5);  //  0
	PORTA&=~BIT(PA6);  //  0
	PORTA&=~BIT(PA7);  //  0
	
}





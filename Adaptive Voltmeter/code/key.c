#include"iom16v.h"
#include"macros.h"
#include"key.h"



//#define FSOC 8
/*** 按键初始化函数 ***/
/******************************************************************************/
void Key_Init(void)
{

 //   DDRB=0x1c;   //k1 k2 配置为输入   0001 1100
 //   PORTB=0x1f;   //使能上拉电阻   0001 1111
	DDRB&=~BIT(PB0);
	DDRB&=~BIT(PB1);
	PORTB|=BIT(PB0);
	PORTB|=BIT(PB1);  
}


void Key_1(void)
{
    if((PINB&(1<<PB1))==0)//检验PB0的电平状态是否为低电平
    {
	     delay_ms(20);//延时消抖
         if((PINB&(1<<PB1))==0)
         {
		   PORTB&=~BIT(2);   //此处放处理函数  
         }
    }
    while((PINB&(1<<PB1))==0);//判断按键是否松开
}

void Key_2(void)
{
    if((PINB&(1<<PB0))==0)//检验PB0的电平状态是否为低电平
    {
	     delay_ms(20);//延时消抖
         if((PINB&(1<<PB0))==0)
         {
		   PORTB|=BIT(2);   //此处放处理函数  
         }
    }
    while((PINB&(1<<PB0))==0);//判断按键是否松开
}

//延时函数

void delay_ms(unsigned int a)	    
{
         unsigned int x,y;
         for(x=a;x>0;x--)
                  for(y=316;y>0;y--);
}



void Delay_1ms(void)
{
	unsigned int i;
	//for(i=1;i<(unsigned int)(FSOC*124);i++)
	for(i=1;i<(unsigned int)(3*16);i++)
		{
			;
		}
		
}

/*
void delay_ms(unsigned int n)  //延时n*1ms
{
	unsigned int i=0;
	while(i<n)
		{
			Delay_1ms();
			i++;
		}
}
*/
#include"iom16v.h"
#include"macros.h"
#include"key.h"



//#define FSOC 8
/*** ������ʼ������ ***/
/******************************************************************************/
void Key_Init(void)
{

 //   DDRB=0x1c;   //k1 k2 ����Ϊ����   0001 1100
 //   PORTB=0x1f;   //ʹ����������   0001 1111
	DDRB&=~BIT(PB0);
	DDRB&=~BIT(PB1);
	PORTB|=BIT(PB0);
	PORTB|=BIT(PB1);  
}


void Key_1(void)
{
    if((PINB&(1<<PB1))==0)//����PB0�ĵ�ƽ״̬�Ƿ�Ϊ�͵�ƽ
    {
	     delay_ms(20);//��ʱ����
         if((PINB&(1<<PB1))==0)
         {
		   PORTB&=~BIT(2);   //�˴��Ŵ�������  
         }
    }
    while((PINB&(1<<PB1))==0);//�жϰ����Ƿ��ɿ�
}

void Key_2(void)
{
    if((PINB&(1<<PB0))==0)//����PB0�ĵ�ƽ״̬�Ƿ�Ϊ�͵�ƽ
    {
	     delay_ms(20);//��ʱ����
         if((PINB&(1<<PB0))==0)
         {
		   PORTB|=BIT(2);   //�˴��Ŵ�������  
         }
    }
    while((PINB&(1<<PB0))==0);//�жϰ����Ƿ��ɿ�
}

//��ʱ����

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
void delay_ms(unsigned int n)  //��ʱn*1ms
{
	unsigned int i=0;
	while(i<n)
		{
			Delay_1ms();
			i++;
		}
}
*/
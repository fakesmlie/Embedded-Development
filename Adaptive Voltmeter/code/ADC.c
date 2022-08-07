#include"iom16v.h"
#include"macros.h"
#include"adc.h"
#include"Nixie.h"



/*** ��ʼ������ ***/
/******************************************************************************/

void ADC_Init(void)
{  //���ض˿ڵ�����PA1~3
    DDRA|=BIT(PA1);                    // PA1��Ϊ���
	PORTA|=BIT(PA1);                   //  PA1����ߵ�ƽ       CD4501A
                  
	DDRA|=BIT(PA2);                    // PA2��Ϊ���
	PORTA|=BIT(PA2);                   //PA2����ߵ�ƽ         CD4501B
                 
	DDRA|=BIT(PA3);                    // PA3��Ϊ���
	PORTA|=BIT(PA3);                   //PA3����ߵ�ƽ         CD4501c
	//ADC0 �˿ڵ�����
    PORTA&=~BIT(PA0); 
    DDRA&=~BIT(PA0);//����
    SFIOR = 0; //����ת��ģʽ 
    ADMUX = 0x00; // ADC0�������� AVER�ο���ѹ 2.503V


}





//��·�������ô�����
void switch_open(unsigned int TEM)
{

    switch(TEM)		//λ�����
	{
		case 1:PORTA|=BIT(PA1);PORTA|=BIT(PA2);PORTA&=~BIT(PA3);break;
		case 2:PORTA&=~BIT(PA1);PORTA&=~BIT(PA2);PORTA&=~BIT(PA3);break;
		case 3:PORTA|=BIT(PA1);PORTA&=~BIT(PA2);PORTA&=~BIT(PA3);break;
	}
	

}

//ADC���ô���

unsigned int voltage_AD(void)
{

    unsigned int addata;
    ADCSRA = 0xC0; //����ADת��, ����ʼת��
    while ((ADCSRA & 0x10) == 0); //�ȵ�ת������
    addata = ADCL; //��ȡADC���� ��λ
    addata = addata + ADCH * 256; //��ȡADC���� ��λ + ��λ
    ADCSRA |= 0x10;
    addata = addata / 1024.0 * 2503; //�����ѹ
    return addata;

}


void ADC_show(unsigned int mum)
{
	Nixie(1,mum/1000);
    Nixie(2,mum/100%10);
    Nixie(3,mum/10%10);
    Nixie(4,mum%10);
}
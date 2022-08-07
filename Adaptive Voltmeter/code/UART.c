#include"iom16v.h"
#include"macros.h"
#include"UART.h"



/*** LED��ʼ������ ***/
/******************************************************************************/
void UART_Init(void)
{

    int BAUD;
    DDRD &= 0XFE;
    DDRD |= 0X02;

    UCSRA |= (1 << U2X);                        //����ģʽ
    UCSRB |= ((1 << RXEN )|(1 << TXEN));        //���ͽ���ʹ��
    UCSRB |= ( (1<< RXCIE)| (1<< TXCIE));       //���ͽ��ܽ����ж�ʹ��
    UCSRB &= ~(1 << UCSZ2);
    UCSRC |= ((1 << UCSZ1)|(1 << UCSZ0));       //8λ����λ
    UCSRC &= ~(1 << UMSEL);                     //�첽
    UCSRC &= ~((1 << UPM1)|(1 << UPM0));        //����żУ��λ
    UCSRC &= ~(1 << USBS);                      //1λֹͣλ
    BAUD  = 12;                                 //������9600
    UBRRL = (unsigned char)BAUD;
    UBRRH = (unsigned char)(BAUD>>8);

}


//���ڷ��ͺ���
void USART_Send(unsigned char Data)
{
        while(!(UCSRA&(BIT(UDRE))));        //���ݼĴ���UDR�Ƿ�Ϊ�գ�
        UDR=Data;                            //UDR��ֵ
        while(!(UCSRA&(BIT(TXC))));            //�����Ƿ��Ѿ�������ϣ�
        UCSRA|=BIT(TXC);                    //���������ϱ�־λ
}


/*�����ַ���*/
void UART_Send_String(unsigned char* str, unsigned char length)
{
      //unsigned char i=0;
     while(length--)
     {
            USART_Send(*str);
            *str++;
     }

}

//��ѹ���ͺ���
void USART_Send_voltage(unsigned char voule)
{
    UART_Send_String("���ͨ���ĵ�ѹֵΪ��",20);
	USART_Send(voule/1000+0x30);
	USART_Send('.');
	USART_Send(voule%1000/100+0x30);
	USART_Send(voule%100/10+0x30);
	USART_Send(voule%10+0x30);
	USART_Send('V');                  //���������ϱ�־λ
}
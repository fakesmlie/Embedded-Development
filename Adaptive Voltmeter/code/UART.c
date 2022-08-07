#include"iom16v.h"
#include"macros.h"
#include"UART.h"



/*** LED初始化函数 ***/
/******************************************************************************/
void UART_Init(void)
{

    int BAUD;
    DDRD &= 0XFE;
    DDRD |= 0X02;

    UCSRA |= (1 << U2X);                        //倍速模式
    UCSRB |= ((1 << RXEN )|(1 << TXEN));        //发送接受使能
    UCSRB |= ( (1<< RXCIE)| (1<< TXCIE));       //发送接受结束中断使能
    UCSRB &= ~(1 << UCSZ2);
    UCSRC |= ((1 << UCSZ1)|(1 << UCSZ0));       //8位数据位
    UCSRC &= ~(1 << UMSEL);                     //异步
    UCSRC &= ~((1 << UPM1)|(1 << UPM0));        //无奇偶校验位
    UCSRC &= ~(1 << USBS);                      //1位停止位
    BAUD  = 12;                                 //波特率9600
    UBRRL = (unsigned char)BAUD;
    UBRRH = (unsigned char)(BAUD>>8);

}


//串口发送函数
void USART_Send(unsigned char Data)
{
        while(!(UCSRA&(BIT(UDRE))));        //数据寄存器UDR是否为空？
        UDR=Data;                            //UDR赋值
        while(!(UCSRA&(BIT(TXC))));            //数据是否已经发送完毕？
        UCSRA|=BIT(TXC);                    //清除发送完毕标志位
}


/*发送字符串*/
void UART_Send_String(unsigned char* str, unsigned char length)
{
      //unsigned char i=0;
     while(length--)
     {
            USART_Send(*str);
            *str++;
     }

}

//电压发送函数
void USART_Send_voltage(unsigned char voule)
{
    UART_Send_String("测得通道的电压值为：",20);
	USART_Send(voule/1000+0x30);
	USART_Send('.');
	USART_Send(voule%1000/100+0x30);
	USART_Send(voule%100/10+0x30);
	USART_Send(voule%10+0x30);
	USART_Send('V');                  //清除发送完毕标志位
}

#ifndef ___UART_h
#define ___UART_h

void UART_Init(void);
void USART_Send(unsigned char Data);
void UART_Send_String(unsigned char* str, unsigned char length);
void USART_Send_voltage(unsigned char volue);


#endif
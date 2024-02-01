#ifndef usart_h
#define usart_h

#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_TOL 2

#include <util/setbaud.h>
#include "gpio.h"

void usart_init(void);
void usart_sendChar(unsigned char c);
void usart_sendString(char *str);
unsigned char usart_receive(void);

#endif
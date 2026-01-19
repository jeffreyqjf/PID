#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>
#include <stdarg.h>
extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];
extern uint16_t pRxPacket;
extern uint8_t RxLen;

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(const uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
int fputc(int ch, FILE *f);
void Serial_Printf(char *format, ...);
uint8_t Serial_GetRxFlag(void);
// uint8_t Serial_GetRxFlag(void);
// void DMA_Config(void);


#endif

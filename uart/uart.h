#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>
#include <stdbool.h>

void UART0Send(uint8_t *pui8Buffer, uint32_t ui32Count);
void UART0IntHandler(void);
void Uart0Iint(void);

void UART1Send(uint8_t *pui8Buffer, uint32_t ui32Count);
void UART1IntHandler(void);
void Uart1Iint(void);

void UART2Send(uint8_t *pui8Buffer, uint32_t ui32Count);
void UART2IntHandler(void);
void UART2Iint(void);

void UART3Send(uint8_t *pui8Buffer, uint32_t ui32Count);
void UART3IntHandler(void);
void UART3Iint(void);

#endif


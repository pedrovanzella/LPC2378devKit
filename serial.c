#include <arch/nxp/lpc23xx.h>
#include "serial.h"

void init_serial(void)
{
  PINSEL0 |= 0x00000050;  /* Enable TxD0 and RxD0 */
  U0FCR = 7;              /* Habilita FIFO de TX e RX resetadas*/
  U0FDR = 0;              /* Fractional divider not used */
  U0LCR = 0x83;           /* 8 bits, no Parity, 1 Stop bit */
  U0DLL = 78;             /* 9600 Baud Rate @ 12.0 MHZ PCLK */
  U0DLM = 0;              /* High divisor latch = 0 */
  U0LCR = 0x03;           /* DLAB = 0 */
}

int U0getchar(void)
{
  while(!(U0LSR & 0x01)); // Quando bit 1 de U0LSR for 1 eh porque recebi dados.
  return(U0RBR);
}

void U0putchar(int dado)
{
  while(!(U0LSR & 0x20)); // Quando bit 6 de U0LSR for 1 eh posso enviar
  U0THR = dado;
}

void U0puts(char* txt)
{
  while(*txt) U0putchar(*txt++);
}


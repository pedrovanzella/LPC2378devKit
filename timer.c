#include <arch/nxp/lpc23xx.h>
#include "timer.h"

void init_timer0(void)
{
  PCONP |= 2;	/* Liga energia do Timer 0 */
  PCLKSEL0 = (PCLKSEL0 & (~0x0c)) | 0x04;	/* Divide CCLK por 1 no T0 */
  T0TCR = 0;              /* Desabilita T0 */
  T0PR = CCLK/1000 - 1; /* Incrementa T0TC 1000 vezes por segundo */
  T0TCR = 2;      /* Inicializa T0 */
  T0TCR = 1;      /* Habilita T0  */
}

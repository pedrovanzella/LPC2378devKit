#include <arch/nxp/lpc23xx.h>
#include "ad.h"

void init_ad(void)
{
  AD0CR = 1;            // ADC0 desligado
  PCONP |= 0x00001000;  // Liga energia ADC
  PINSEL1 |= 0x4000;    // Seleciona pino do ADC0
  AD0CR = 0x00200201;   // Configura ADC0
}

int le_ad(void)
{
  int k = 0;
  k = 40000;
  AD0CR |= 0x01000000;           // Inicia a conversao (Liga bit 24:start)
  while(!(AD0GDR & 0x80000000) & k) k--; // Espera terminar a conversao
  k = ((AD0DR0 >> 6) & 0x3ff);   // descarta os primeiros 6 bits
  return k;
}

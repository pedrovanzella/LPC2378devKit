/******************************************
 *      LABORATORIO DE PROCESSADORES      *
 *            TRABALHO FINAL              *
 *                                        *
 *              Bruno Paes                *
 *            Pedro Vanzella              *
 ******************************************/

#include <arch/nxp/lpc23xx.h>
#include <stdio.h>
#include <stdlib.h>
#include "rtc.h"
#include "ad.h"
#include "LCD.h"
#include "io.h"
#include "sensortemp.h"
#include "serial.h"
#include "timer.h"

extern float temp; // Temperatura a ser mantida
extern char should_be_on; // Devo estar monitorando a temperatura? IRQ do RTC muda isso.

int main(void)
{
  should_be_on = 1; // A principio, devemos estar ligados.
  int horaalrm; // Temporario para garantir que nao haja overflow na inicializacao do alarme
  int minalrm;
  temp = 25.0; // Temperatura inicial a ser mantida eh 25 graus

  init_timer0();
  LCDinit();
  init_serial();
  init_ad();
  RTCinit();

  horaalrm = RTC_HOUR;
  horaalrm >= 23? horaalrm = 0 : horaalrm++;
  minalrm = RTC_MIN;
  minalrm >= 59? minalrm = 0 : minalrm++;
  RTCalarm(RTC_HOUR, minalrm, 0); // Alarme comeca setado para daqui a uma hora

  FIO4DIR |= (LED0) | (LED1) | (LED2) | (LED3) | (LED4) | (IO18) | (IO20); // Seta LED0 como saida

  while(1) /* MAIN LOOP */
  {
    LCDcomando(0x80);
    LCDputs("Hora: ");
    escreve2digs(RTC_HOUR);
    LCDputchar(':');
    escreve2digs(RTC_MIN);
    LCDputchar(':');
    escreve2digs(RTC_SEC);
    
    LCDcomando(0xc0);
    LCDputs("Temp: ");
    escreve_float(gettemp());
    LCDputchar(' '); // Limpa o ultimo char

    FIO4CLR = (LED3); // Int dos segundos ta funcionando
    FIO4CLR = (LED4); // Ints em geral estao funcionando
    if(should_be_on) // Se o alarme nao tocou, devo monitorar a temp.
    {
      FIO4CLR = (LED0); // Fica ligado caso estejamos ligados
      if(gettemp() <= temp - 1) // Se estamos um grau ou mais abaixo
      {
        ligalamp();
        desligafan();    
      }
      if(gettemp() >= temp + 1) // Se estamos um grau ou menos abaixo
      {
        desligalamp();
        ligafan();
      }
    }

    /* Setar alarme e temperatura */
    while(!(FIO4PIN & SW4)) // Segurar SW4 para entrar no modo de programacao
    {
      settempal();
    }
  }

  return 0;
}

void UNDEF_Routine(){}
void SWI_Routine(){}

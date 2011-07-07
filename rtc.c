#include <arch/nxp/lpc23xx.h>
#include "rtc.h"
#include "io.h"

char should_be_on;

void RTCinit(void)
{
  RTC_AMR = 0;
  RTC_CIIR = 0;
  RTC_CCR = 0;
  RTC_PREINT = 1; //UTILIZANDO O CRYSTAL DE 32.768KHZ
  RTC_PREFRAC = 1; //UTILIZANDO O CRYSTAL DE 32.768KHZ
  //RTC_PREINT = 365; //UTILIZANDO O CRYSTAL DE 12MHz
  //RTC_PREFRAC = 6912; //UTILIZANDO O CRYSTAL DE 12MHz
  RTCstart();
}

void RTCstart(void)
{
  RTC_CCR |= 0x11; //UTILIZANDO O CRYSTAL DE 32.768KHZ
  //RTC_CCR |= 0x01; //UTILIZANDO O CRYSTAL DE 12MH
}

void RTCstop(void)
{
  RTC_CCR |= 0x10; //UTILIZANDO O CRYSTAL DE 32.768KHZ
  //RTC_CCR |= 0x00; //UTILIZANDO O CRYSTAL DE 12MHZ
}

void RTCconfig(int hora, int minuto, int segundo)
{
  RTCstop();//Parar o RTC para ajuste

  RTC_HOUR = hora;
  RTC_MIN = minuto;
  RTC_SEC = segundo;

  RTCstart();//Reinicia o RT
}

void RTCalarm(int hora, int minuto, int segundo)
{
  RTC_CIIR = 5; // habilita interrupcao das horas e minutos
  RTC_ALSEC = segundo; // seta alarm segundos
  RTC_ALMIN = minuto; // seta alarm minuto
  RTC_ALHOUR = hora; // Seta alarm hora
  RTC_AMR = 0x000000fc; // habilita alarme dos segundos, minutos e horas
  RTC_CISS = 0x85;  // Gera 64 ints por segundo no RTC
  RTC_ILR = 0; // Limpa o id de ints do RTC
  desabilitaIRQ();
  VICVectAddr13 = (int)IRQ_RTC; /* Set Interrupt Vector */
  VICIntSelect &= 0x2000;
  VICIntEnable = 0x2000;
  habilitaIRQ();
}

void IRQ_RTC(void)
{
  short k;
  if(RTC_ILR & 1) // Interrupcao dos segundos
  {
    RTC_ILR = 1; // Limpa flag de interrupcao
    FIO4SET = (LED3);
  }

  if(RTC_ILR & 2) //interrupcao do alarme
  {
    //entra aqui quando o alarme acontece
    should_be_on = 0;
    FIO4SET = (LED0); //desliga led de alarme, nao estamos monitorando mais
    FIO4SET = (LED1);
    FIO4SET = (LED2);
    FIO4SET = (IO18); // Desliga tambem as portas
    FIO4SET = (IO20);
    RTC_ILR = 2; //limpa flag de interrupcao
  }

  FIO4SET = (LED4);
  k = RTC_ILR;
  RTC_ILR = k; // Gambiarra do Stemmer
  VICVectAddr = 0; //atende a interrupcao
}

void FIQ_Routine(){}


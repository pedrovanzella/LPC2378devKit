#include <arch/nxp/lpc23xx.h>
#include "sensortemp.h"
#include "ad.h"
#include "io.h"
#include "LCD.h"
#include "rtc.h"

float temp;

float gettemp()
{
  float temp;
  /* 10mV/C */
  temp = (le_ad() / 0.314) + 5;
  return temp;
}

void settempal()
{
  LCDcomando(0x80); // Vamos reescrever todo o LCD; 
  LCDputs("Alrm: ");
  escreve2digs(RTC_ALHOUR);
  LCDputchar(':');
  escreve2digs(RTC_ALMIN);
  LCDputchar(':');
  escreve2digs(RTC_ALSEC);

  LCDcomando(0xc0); // Segunda linha
  LCDputs("Temp: ");
  escreve_float(temp);
  LCDputchar(' '); // Limpa o ultimo char
  LCDputchar(' '); // Limpa o ultimo char

  if(!(FIO2PIN & SW0)) // SW0 incrementa hora do alarme
  {
    if(RTC_ALHOUR >= 23)
      RTC_ALHOUR = 0;
    else
      RTC_ALHOUR++;
  }

  if(!(FIO2PIN & SW1)) // SW1 incrementa minutos do alarme
  {
    if(RTC_ALMIN >= 59)
      RTC_ALMIN = 0;
    else
      RTC_ALMIN++;
  }

  if(!(FIO0PIN & SW2)) // SW2 decrementa a temp
    temp -= 1.0;

  if(!(FIO4PIN & SW3)) // SW3 incrementa a temp
    temp += 1.0;
}

void ligafan()
{
  FIO4CLR = (LED1);
  FIO4CLR = (IO18);
}

void desligafan()
{
  FIO4SET = (LED1);
  FIO4SET = (IO18);
}

void ligalamp()
{
  FIO4CLR = (LED2);
  FIO4CLR = (IO20);
}

void desligalamp()
{
  FIO4SET = (LED2);
  FIO4SET = (IO20);
}

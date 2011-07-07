#include <arch/nxp/lpc23xx.h>
#include "LCD.h"

/* Espera t milisegundos */
void espera(unsigned int t)
{
  unsigned int tf;
  tf = T0TC + t;          /* tf = Valor futuro do T0TC */
  while(tf != T0TC);      /* espera ate que tf==T0TC */
}

void LCDcomando(int c)
{
  FIO3PIN0 = c;
  FIO2CLR = LCD_RS;
  FIO2SET = LCD_EN;
  FIO2CLR = LCD_EN;
  espera(20);
}

void LCDputchar(int c)
{
  FIO3PIN0 = c;
  FIO2SET = LCD_RS;
  FIO2SET = LCD_EN;
  FIO2CLR = LCD_EN;
  espera(8);
}

void LCDinit(void)
{
  FIO3DIR |= 0xff;	/* P3.0 a P3.7 como saidas (dados do LCD) */
  FIO2DIR |= (LCD_RS | LCD_EN);
  FIO2CLR = LCD_EN;
  espera(20);
  LCDcomando(0x38);
  LCDcomando(1);
  LCDcomando(0x0c);
}

void LCDputs(char *s)
{
  while(*s) LCDputchar(*s++);
}

/* Escreve numero decimal de 2 digitos */
void escreve2digs(int x)
{
  LCDputchar((x/10) + '0');	/* Escreve dezena  */
  LCDputchar((x%10) + '0');	/* Escreve unidade */
}

/* Escreve um numero decimal */
void escreve_num(int num)
{
  char digs[16];
  int nd=0;
  if(num<0)
  {
    LCDputchar('-'); num=-num;
  }
  do	{
    digs[nd++]= (num % 10) + '0';
    num /= 10;
  } while(num);
  while(nd--) LCDputchar(digs[nd]);
}

/* escreve um float com 1 casa apos a virgula */
void escreve_float(float f)
{
 char digs[16];
  int nd = 0;
  int num = (int) (f * 10); // Cast to int with one decimal point
  if(num < 0)
  {
    LCDputchar('-'); num =- num;
  }
  do	{
    digs[nd++]= (num % 10) + '0';
    num /= 10;
  } while(num);
  while(nd--)
  {
    if(nd == 0)
    {
      LCDputchar('.'); // Insere um ponto antes do ultimo digito
    }
    LCDputchar(digs[nd]);
  }
}

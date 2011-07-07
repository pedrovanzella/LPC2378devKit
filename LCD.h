#ifndef LCD_H
#define LCD_H

//Configuração do display LCD
#define LCD_RS (1<<2)
#define LCD_EN (1<<3)
#define LCD_DADO (0xFF)

void LCDinit(void);
void LCDcomando(int c);
void LCDputchar(int c);
void LCDputs(char *s);
void espera(unsigned int t);
void escreve2digs(int x);
void escreve_num(int num);
void escreve_float(float f);

#endif /* LCD_H */

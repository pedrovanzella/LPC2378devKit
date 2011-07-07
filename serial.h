#ifndef SERIAL_H
#define SERIAL_H
#include <arch/nxp/lpc23xx.h>

void init_serial (void);
int U0getchar(void);
void U0putchar(int dado);
void U0puts(char* txt);

#endif /* SERIAL_H */

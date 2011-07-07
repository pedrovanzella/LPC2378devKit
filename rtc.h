#ifndef RTC_H
#define RTC_H
#include <arch/nxp/lpc23xx.h>
#include "vic_cpsr.h"
#include "io.h"

void RTCinit(void);
void RTCstart(void);
void RTCstop(void);
void RTCconfig(int hora, int minuto, int segundo);
void RTCalarm(int hora, int minuto, int segundo);
void IRQ_RTC(void) __attribute__ ((interrupt("IRQ")));

#endif /* RTC_H */

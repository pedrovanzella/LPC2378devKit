#ifndef SENSORTEMP_H
#define SENSORTEMP_H
#include <arch/nxp/lpc23xx.h>
#include "ad.h"
#include "io.h"
#include "LCD.h"
#include "rtc.h"

float gettemp();
void settempal();
void ligafan();
void desligafan();
void ligalamp();
void desligalamp();

#endif /* SENSORTEMP_H */

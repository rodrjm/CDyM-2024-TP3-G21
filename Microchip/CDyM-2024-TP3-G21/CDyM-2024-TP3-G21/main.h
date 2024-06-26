#ifndef MAIN_H_
#define MAIN_H_
#include <avr/interrupt.h>
#include <avr/io.h> // Definición de Registros del microcontrolador
#define F_CPU 16000000UL // Frecuencia de reloj del MCU
#include <util/delay.h> // Retardos por software – Macros: depende de F_CPU
#include "dht11.h"
#include "i2c.h"
#include "rtc.h"
#include "serialPort.h"
#include "timer.h"
#endif /* MAIN_H_ */

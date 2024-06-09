#include "main.h"

uint8_t data[5];
extern uint8_t RTC_flag;

void DHT_init(){
	for (int i=0;i<5;i++) data[i]=0;
	DDRC |= (1<<PORTC0);
	PORTC |= (1<<PORTC0);
	_delay_ms(18);
	PORTC &= ~(1<<PORTC0);
	_delay_ms(18);
	PORTC |= (1<<PORTC0);
	_delay_us(40);
	DDRC &= ~(1<<PORTC0);
	_delay_us(160);
}

void obtenerTemperaturaHumedad(){
	for(int i=0; i<5; i++) {
		for (int j=7; j>=0; j--) {
			while (!((PINC &(1<<PINC0))));
			_delay_us(30);
			if (((PINC &(1<<PINC0)))) {
				data[i] |= (1<<j);
				while (((PINC &(1<<PINC0))));
				} else {
				data[i] |= (0<<j);
			}
		}
	}
	if (data[0] + data[1] + data[2] + data[3] == data [4]) { // Verifico que se hayan mandado correctamente los datos con el checksum
		SerialPort_TX_DHT11(data);
		RTC_flag = 1;
	}
}
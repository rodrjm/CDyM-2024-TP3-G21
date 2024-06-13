#include "main.h"

uint8_t data[5];
extern uint8_t RTC_flag;

void DHT_init(){
	for (int i=0;i<5;i++) data[i]=0; // Inicializo el arreglo donde se van a almacenar los datos del sensor
	DDRC |= (1<<PORTC0); // Seteo al puerto C como salida
	PORTC |= (1<<PORTC0); // Seteo el puerto C en alto
	_delay_ms(18);
	PORTC &= ~(1<<PORTC0); // Seteo el puerto C en bajo
	_delay_ms(18);
	PORTC |= (1<<PORTC0); // Seteo el puerto C en alto
	_delay_us(40);
	DDRC &= ~(1<<PORTC0); // Seteo al puerto C como entrada
	_delay_us(160); // Espero la respuesta del sensor, que debería responder poniendo la señal en bajo 80us, y luego en alto otros 80us
}

void obtenerTemperaturaHumedad(){
	for(int i=0; i<5; i++) { // Para cada byte dentro de los 5 que me envía el sensor
		for (int j=7; j>=0; j--) { // Para cada bit dentro de cada byte
			while (!((PINC &(1<<PINC0)))); // Espero a que la señal se ponga en alto
			_delay_us(30);
			if (((PINC &(1<<PINC0)))) { // Si pasaron 30us y sigue estando la señal en alto, quiere decir que el dato es un 1
				data[i] |= (1<<j); // Seteo el 1 en la posición j del byte i del arreglo
				while (((PINC &(1<<PINC0)))); // Espero a que la señal se ponga en bajo para leer el siguiente bit
			} else { // Si pasaron 30us y la señal está en bajo, quiere decir que el dato es un 0
				data[i] &= ~(1<<j); // Seteo el 0 en la posición j del byte i del arreglo
			}
		}
	}
	if (data[0] + data[1] + data[2] + data[3] == data [4]) { // Verifico que se hayan mandado correctamente los datos con el checksum
		SerialPort_TX_DHT11(data);
		RTC_flag = 1; // Activo el flag del RTC para que se seteen los datos
	}
}
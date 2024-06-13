#include "main.h"

// Utilizada para el Reloj
typedef struct{
	uint8_t	segundos;
	uint8_t minutos;
	uint8_t horas;	
} relojRTC;
static relojRTC reloj;

// Utilizada para la Fecha
typedef struct{
	uint8_t	dia;
	uint8_t mes;
	uint8_t anio;
} fechaRTC;
static fechaRTC fecha;

// Se inicia el RTC con los valores por defecto 23:59:50 y 01/05/24 
void RTC_init(){
	setTime(); // Se asigna el Reloj para el RTC
	setDate(); // Se asigna la Fecha para el RTC
}

// Para establecer los valores del Reloj
void setTime() {
	i2c_init(); 
	i2c_start();
	i2c_write(0b11010000); // Se setea el modo de escritura
	i2c_write(0x00);  // Se posiciona en la posicion para los segundos
	i2c_write(0x50); // Se asignan los segundos 
	i2c_write(0x59); // Se asignan los minutos
	i2c_write(0x23); // Se asigna la hora
	i2c_stop(); // Transmit STOP condition
}

// Para establecer los valores de la Fecha
void setDate() {
	i2c_start();
	i2c_write(0b11010000); // Se setea el modo de escritura
	i2c_write(0x04); // Se posiciona en la posicion para el día 
	i2c_write(0x01); // Se asigna el dia
	i2c_write(0x05); // Se asigna el mes
	i2c_write(0x24); // Se asigna el año 
	i2c_stop(); // Transmit STOP condition
}

// Para leer los valores del Reloj
void getTime() {
	i2c_start();
	i2c_write(0b11010000); // Se setea el modo de escritura
	i2c_write(0x00); // Se posiciona en la posicion para los segundos
	i2c_stop(); // Transmit STOP condition
	i2c_start();
	i2c_write(0b11010001); // Se setea el modo de lectura
	reloj.segundos = i2c_read(0); // Lee los segundos
	reloj.minutos = i2c_read(0); // Lee los minutos
	reloj.horas = i2c_read(1); // Lee la hora
	i2c_stop(); // Transmit STOP condition
}

// Para leer los valores de la Fecha
void getDate() {
	i2c_start();
	i2c_write(0b11010000); // Se setea el modo de escritura
	i2c_write(0x04); // Se posiciona en la posicion para el dia
	i2c_stop(); // Transmit STOP condition
	i2c_start();
	i2c_write(0b11010001); // Se setea el modo de lectura
	fecha.dia = i2c_read(0); // Lee el dia
	fecha.mes = i2c_read(0); // Lee el mes
	fecha.anio = i2c_read(1); // Lee el ano
	i2c_stop(); // Transmit STOP condition
}

// Para obtener el Reloj y la Fecha compleata
void obtenerHoraFecha() {
	getTime(); // Se obtiene el Reloj
	getDate(); // Se obtiene la Fecha
	SerialPort_TX_RTC(reloj.segundos, reloj.minutos, reloj.horas, fecha.dia, fecha.mes, fecha.anio); // Para cargar en el buffer de TX el Reloj y la Fecha
}
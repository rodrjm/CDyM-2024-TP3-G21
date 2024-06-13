#include "main.h"

// Declaración de variables para controlar los flags que van a ser los que manejen el funcionamiento del programa
volatile uint8_t RX_flag = 0;
volatile uint8_t TX_flag = 0;
volatile uint8_t DHT_flag = 0;
volatile uint8_t RTC_flag = 0;

volatile char RX_Buffer = 0; // Variable para el buffer de recepción de la UART

uint8_t estado = 0; // Variable que indica si el sistema está funcionando (0) o detenido (1)

int main(void)
{
	_delay_ms(3000); // Delay para que el sistema se cargue correctamente
	UART_init();
	RTC_init();
	Timer_init();
	sei();
	while (1)
	{
 		if (RX_flag) { // Flag de recepción de la UART
 			if ((RX_Buffer == 's') || (RX_Buffer == 'S')) { // Si recibo el caracter 's' o 'S'
				 if (estado == 0) { // Si el sistema está funcionando, debo detenerlo
					 Timer_stop();
					 mensajeDetenido();
					 estado = 1;
				 } else { // Caso contrario, debo reanudar el funcionamiento del sistema
					 Timer_init();
					 mensajeReanudado();
					 estado = 0;
				 }
			}
			RX_flag = 0; // Desactivo el flag de recepción
 		}
 		if (TX_flag) { // Flag de transmisión de la UART
 			transmitirDatos();
			RTC_flag=0; // Desactivo el flag
 		}
 		if (DHT_flag) { // Flag del DHT11, que indica que debemos obtener datos del sensor
 			DHT_init();
			obtenerTemperaturaHumedad();
			DHT_flag=0; // Desactivo el flag
 		}
 		if (RTC_flag) { // Flag del RTC, que indica que debemos obtener datos del RTC	
			obtenerHoraFecha();
 		}
	}
}
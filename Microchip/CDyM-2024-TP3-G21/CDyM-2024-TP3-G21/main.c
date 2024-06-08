#include "main.h"

volatile uint8_t RX_flag = 0;
volatile uint8_t TX_flag = 0;
volatile uint8_t DHT_flag = 0;
volatile uint8_t RTC_flag = 0;
volatile char RX_Buffer = 0;

uint8_t estado = 0;

int main(void)
{
	_delay_ms(3000);
	UART_init();
	setTime();
	setDate();
// 	getTime();
// 	getDate();
	init_Timer();
	sei();
	/*DHT_flag=1;*/
	while (1)
	{
 		if (RX_flag) {
 			if ((RX_Buffer == 's') || (RX_Buffer == 'S')) {
				 if (estado == 0) {
					 mensajeDetenido();
					 estado = 1;
				 } else {
					 mensajeReanudado();
					 estado = 0;
				 }
			}
			RX_flag = 0;
 		}
 		if (TX_flag) {
			RTC_flag=0;
 			transmitirDatos();
 		}
 		if (DHT_flag) {
 			inicializacion();
			obtenerTemperaturaHumedad();
			/*DHT_flag=0;*/
 		}
 		if (RTC_flag) {
			DHT_flag = 0;	
			obtenerHoraFecha();
 		}
	}
}
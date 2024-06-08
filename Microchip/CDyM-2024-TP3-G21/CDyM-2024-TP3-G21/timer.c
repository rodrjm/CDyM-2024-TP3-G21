#include "timer.h"

static uint16_t cont=0; //Variable para saber cuando se llego a los 2 segundos 
extern volatile uint8_t DHT_flag;

void init_Timer(){
	OCR0A = 249; // Cargamos el valor para la comparacion (Para poder realizar interrupcion cada 1ms)
	TCCR0A = (1<<WGM01); // Configucion el modo CTC para el timer0
	TCCR0B = (1<<CS00)|(1<<CS01); // Configuracion del preescalador en 64
	TIMSK0 |= (1<<OCIE0A); // Configuracion las interrupciones por comparacion
}
void stop_Timer(){
	TCCR0B = 0;
}
//Interrupcion del Timer 
ISR(TIMER0_COMPA_vect){
	if (++cont==2000) //Al llegar a los 2 seg 
	{ 
		DHT_flag=1;
		cont=0;
	}
}
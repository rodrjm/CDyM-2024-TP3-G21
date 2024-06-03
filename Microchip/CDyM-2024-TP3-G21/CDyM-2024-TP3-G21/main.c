#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

uint8_t data[5];

int main(void)
{
	DDRC |= (1<<PORTC0);
	
	while (1)
	{
		PORTB |= (1<<PORTB0);
		PORTC |= (1<<PORTC0);
		_delay_ms(18);
		PORTC &= ~(1<<PORTC0);
		_delay_ms(18);
		PORTC |= (1<<PORTC0);
		_delay_us(40);
		DDRC &= ~(1<<PORTC0);
		_delay_us(160);
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
	}
}
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	uint8_t e;
	DDRC |= (1<<PORTC0);
	
	while (1)
	{
		PORTB|=(1<<PORTB0);
		PORTC |= (1<<PORTC0);
		_delay_ms(18);
		PORTC &= ~(1<<PORTC0);
		_delay_ms(18);
		PORTC |= (1<<PORTC0);
		_delay_us(40);
		DDRC &= ~(1<<PORTC0);
		_delay_us(180);
		for(int i=0;i<8;i++){
			if (PINC &(1<<PINC0))
			{
				_delay_us(30);
			}
			if (PINC &(1<<PINC0))
			{
				PORTB =0;
			} else PORTB =1;
		}
	}
}
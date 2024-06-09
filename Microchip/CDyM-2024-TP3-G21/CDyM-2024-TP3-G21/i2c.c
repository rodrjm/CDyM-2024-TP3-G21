#include "main.h"

void i2c_init(void){
	TWSR=0x00;
	TWBR=152;
	TWCR=0x04;
}

void i2c_start(void){
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR&(1<<TWINT))==0);
}

void i2c_write(unsigned char data){
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR&(1<<TWINT))==0);
}

unsigned char i2c_read(unsigned char isLast){
	if (isLast==0) TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	else TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR&(1<<TWINT))==0);
	return TWDR;
}

void i2c_stop(){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
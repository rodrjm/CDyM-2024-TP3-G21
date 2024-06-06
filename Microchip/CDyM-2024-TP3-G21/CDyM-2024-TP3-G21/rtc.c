#include "main.h"
uint8_t	data=0;
uint8_t data1=0;
uint8_t data2=0;
void setTime(){
	i2c_init();
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x00);
	i2c_write(0x50);
	i2c_write(0x59);
	i2c_write(0x23);
	//i2c_wriete(0b11110000);
	i2c_stop(); //transmit STOP condition
}

void setDate(){
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x04);
	i2c_write(0x01);
	i2c_write(0x05);
	i2c_write(0x24);
	//i2c_wriete(0b11110000);
	i2c_stop(); //transmit STOP condition
}
void getTime(){
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x00);
	i2c_stop();
	i2c_start();
	i2c_write(0b11010001);
	data = i2c_read(0); //Lee los segundos
	data1= i2c_read(0); //Lee los minutos
	data2 = i2c_read(1); //Lee la hora
	i2c_stop();
}

void getDate(){
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0x04);
	i2c_stop();
	i2c_start();
	i2c_write(0b11010001);
	data = i2c_read(0); //Lee el día
	data1= i2c_read(0); //Lee el mes
	data2 = i2c_read(1); //Lee el año
	i2c_stop();
}
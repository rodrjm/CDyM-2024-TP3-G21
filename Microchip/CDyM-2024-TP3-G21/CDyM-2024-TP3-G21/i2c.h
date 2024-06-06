#ifndef I2C_H_
#define I2C_H_
void i2c_init(void);
void i2c_start(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char isLast);
void i2c_stop();
#endif /* I2C_H_ */
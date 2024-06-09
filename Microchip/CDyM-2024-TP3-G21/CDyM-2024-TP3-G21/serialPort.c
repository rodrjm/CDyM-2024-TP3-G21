/*
 * serialPort.c
 *
 * Created: 07/10/2020 03:02:18 p. m.
 *  Author: vfperri
 */ 

#include "SerialPort.h"

#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz
#define TX_BUFFER_LENGTH 52

// Mensajes de bienvenida, de detención y reanudación del programa
char msg1[] = "Bienvenido al registrador de temperatura y humedad relativa ambiente\n\r";
char msg2[] = "Para detenerlo presione la tecla 's' o 'S'\n\r";
char msg3[] = "SISTEMA DETENIDO\n\r";
char msg4[] = "Para reanudarlo presione la tecla 's' o 'S'\n\r";
char msg5[] = "SISTEMA REANUDADO\n\r";

extern uint8_t RX_flag;
extern uint8_t TX_flag;

volatile static unsigned char TXindice_lectura;

static char TX_Buffer [TX_BUFFER_LENGTH] = 
	{'T','E','M','P',':',' ','0','0',' ','°','C',' ',
	'H','U','M',':',' ','0','0','%',' ',
	'F','E','C','H','A',':',' ','0','0','/','0','0','/','0','0',' ',
	'H','O','R','A',':','0','0',':','0','0',':','0','0','\r','\n'};
extern char RX_Buffer;

// ------ Definiciones de Funciones Públicas -------------------

// Inicialización de Puerto Serie

void SerialPort_Init(uint8_t config){
	// config = 0x33 ==> Configuro UART 9600bps, 8 bit data, 1 stop @ F_CPU = 8MHz.
	// config = 0x25 ==> Configuro UART 9600bps, 8 bit data, 1 stop @ F_CPU = 4Hz.
	UCSR0B = 0;
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	UBRR0H = (unsigned char)(config>>8);
	UBRR0L = (unsigned char)config;
}


// Inicialización de Transmisor

void SerialPort_TX_Enable(void){
	UCSR0B |= (1<<TXEN0);
}

void SerialPort_TX_Interrupt_Enable(void){
	UCSR0B |= (1<<UDRIE0);
	//UCSR0B |=(1<<TXCIE0); //interrupcion TXC

}

void SerialPort_TX_Interrupt_Disable(void)
{
	UCSR0B &=~(1<<UDRIE0);
	//UCSR0B &=~(1<<TXCIE0); //interrupcion TXC

}


// Inicialización de Receptor

void SerialPort_RX_Enable(void){
	UCSR0B |= (1<<RXEN0);
}

void SerialPort_RX_Interrupt_Enable(void){
	UCSR0B |= (1<<RXCIE0);
}


// Transmisión

// Espera hasta que el buffer de TX este libre.
void SerialPort_Wait_For_TX_Buffer_Free(void){
	// Pooling - Bloqueante hasta que termine de transmitir.
	while(!(UCSR0A & (1<<UDRE0)));
}

void SerialPort_Send_Data(char data){
	UDR0 = data;
}

void SerialPort_Send_String(char * msg){ //msg -> "Hola como andan hoy?" 20 ASCII+findecadena, tardo=20ms
	uint8_t i = 0;
	//'\0' = 0x00
	while(msg[i]){ // *(msg+i)
		SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms 
		SerialPort_Send_Data(msg[i]);
		i++;
	}
}


// Recepción

// Espera hasta que el buffer de RX este completo.
void SerialPort_Wait_Until_New_Data(void){
	// Pooling - Bloqueante, puede durar indefinidamente!
	while(!(UCSR0A & (1<<RXC0)));
}


char SerialPort_Recive_Data(void){
	return UDR0;
}


void SerialPort_Send_uint8_t(uint8_t num){
	
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0'+num/100);
	
	num-=100;
	
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0'+num/10);
	
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0'+ num%10);
}

/***************************************************************
	This function writes a integer type value to UART
	Arguments:
	1)int val	: Value to print
	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val
****************************************************************/
void SerialPort_send_int16_t(int val,unsigned int field_length)
{
	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) {
		SerialPort_Wait_For_TX_Buffer_Free();
		SerialPort_Send_Data('-');
		}
	for(i=j;i<5;i++)
	{
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0'+str[i]);
	}
}

// Inicialización de la UART
void UART_init() {
	SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();			// Activo el transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el receptor del Puerto Serie
	SerialPort_Send_String(msg1);   // Envío el mensaje de Bienvenida
	SerialPort_Send_String(msg2);   // Envío el mensaje para detener el sistema
	SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion
}

// Funciones para mostrar los mensajes en cada estado
void mensajeDetenido() {
	SerialPort_Send_String(msg3);   // Envío el mensaje de Bienvenida
	SerialPort_Send_String(msg4);   // Envío el mensaje para reanudar el sistema
}

void mensajeReanudado() {
	SerialPort_Send_String(msg5);   // Envío el mensaje de Bienvenida
	SerialPort_Send_String(msg2);   // Envío el mensaje para detener el sistema
}

// Transmisión de datos
void transmitirDatos() {
	SerialPort_Send_Data(TX_Buffer[TXindice_lectura++]); // Enviar un caracter
	if (TXindice_lectura < TX_BUFFER_LENGTH) { // Si hay mas datos en el buffer
		SerialPort_TX_Interrupt_Enable();
	} else {
		TXindice_lectura = 0;
	}
	TX_flag = 0; // Desactivar flag de transmision
}

// Seteo de datos del DHT11
void SerialPort_TX_DHT11(uint8_t data[]) {
	// Seteo de los datos de la Temperatura
	TX_Buffer[6] = '0'+data[2]/10;
	TX_Buffer[7] = '0'+data[2]%10;
	
	// Seteo de los datos de la Humedad
	TX_Buffer[17] = '0'+data[0]/10;
	TX_Buffer[18] = '0'+data[0]%10;
}

// Seteo de datos del RTC
void SerialPort_TX_RTC(uint8_t segundos, uint8_t minutos, uint8_t horas, uint8_t dia, uint8_t mes, uint8_t anio) {
	TX_Buffer[48] = '0'+segundos/16;
	TX_Buffer[49] = '0'+segundos%16;
		
	TX_Buffer[45] = '0'+minutos/16;
	TX_Buffer[46] = '0'+minutos%16;
		
	TX_Buffer[42] = '0'+horas/16;
	TX_Buffer[43] = '0'+horas%16;
		
	TX_Buffer[28] = '0'+dia/16;
	TX_Buffer[29] = '0'+dia%16;
		
	TX_Buffer[31] = '0'+mes/16;
	TX_Buffer[32] = '0'+mes%16;
		
	TX_Buffer[34] = '0'+anio/16;
	TX_Buffer[35] = '0'+anio%16;
		
	SerialPort_TX_Interrupt_Enable();
}

// Interrupción de transmisión
ISR(USART_UDRE_vect) {
	if (TXindice_lectura < TX_BUFFER_LENGTH) { // Si hay datos para enviar, dejo el flag activado
 		TX_flag = 1;
 	}
	 
	SerialPort_TX_Interrupt_Disable(); // Deshabilitar la interrupcion de transmisión	
}

// Interrupción de recepción
ISR(USART_RX_vect){
	RX_Buffer = SerialPort_Recive_Data();
	RX_flag = 1;
}
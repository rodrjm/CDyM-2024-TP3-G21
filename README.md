# Registrador de Temperatura y Humedad relativa ambiente

## Materia
- Circuitos Digitales y Microcontroladores de la carrera Ingeniería en Computación de la Universidad Nacional de La Plata

## Grupo
- G21 

## Integrantes
- Ivan Sandoval 
- Juan Manuel Rodriguez 

## En el siguiente proyecto se trata de resolver un sistema, en el cuál se pueda registrar la temperatura y la humedad relativa del ambiente junto a la hora y la fecha de dicho registro

## Las tecnologías utilizados fueron 
- placa Arduino uno
- atmega382p
- lenguaje de programación C
- Proteus
- Sensor de Temperatura y Humedad DHT11
- Sensor de Tiempo Real RTC DS3231


## Instalación 
1. Instalar el Microchip Studio
2. Instalar Proteus
3. Clonar el repositorio 
4. Abrir el archivo del proyecto denominado CDyM-2024-TP3-G21 ubicado en la carpeta de directorios CDyM-2024-TP3-G21\Microchip\CDyM-2024-TP3-G21
5. Realizar la compilación del proyecto 
6. Abrir el archivo de la simulación en Proteus denominado CDyM-2024-TP3-G21 que se ubica en la carpeta de directorios CDyM-2024-TP3-G21\Proteus
7. Ejecutar el la simulación en Proteus

## Requerimientos a verificar en el proyecto
- El microcontrolador Atmega328p deberá encuestar al sensor DHT11 para obtener una medida de la temperatura y la humedad relativa cada
2seg.
- Utilizando el sensor RTC DS3231 el atmega328p completará el registro agregando la fecha y hora actual a cada una de las
medidas obtenidas con el sensor DHT11.
- Por último realizará un formateo de los datos para transmitir el mensaje a una terminal serie en PC. Por
ejemplo, el formato puede ser “TEMP: 20 °C HUM: 40% FECHA: 10/06/24 HORA:15:30:56\r\n”
- El envío de datos se podrá detener o reanudar desde la PC presionando la tecla ‘s’ o ‘S’ sucesivamente.
- La comunicación serie asincrónica deberá implementarse utilizando interrupciones de recepción y transmisión del periférico UART0

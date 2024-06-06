#include "main.h"
int main(void)
{
	setTime();
	setDate();
	getTime();
	getDate();
	while (1)
	{
		inicializacion();
		obtenerDatos();
	}
}
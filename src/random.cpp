#include "random.h"

GeneradorAleatorios::GeneradorAleatorios(double min, double max) {
	// Iniciamos el generador de números aleatorios
	srand(time(0));
	rand();

	// Establecemos los valores máximo y mínimo
	minimo = min;
	maximo = max;
}

double GeneradorAleatorios::Genera() {
	// Ajustamos cada aleatorio a las condiciones pedidas
	double aleatorio = rand()*(maximo - minimo)/RAND_MAX + minimo;
	return aleatorio;
}

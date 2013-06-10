#include "Aleatorio.h"

GeneradorAleatorios::GeneradorAleatorios() {
	// Iniciamos el generador de números aleatorios
	srand(time(0));
	rand();
}

int GeneradorAleatorios::genera(int max) {
	// Ajustamos cada aleatorio a las condiciones pedidas
	int aleatorio = int(max*(rand()/(RAND_MAX+1.0)));
	return aleatorio;
}

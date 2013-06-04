#ifndef ALEATORIO
#define ALEATORIO
#include <cstdlib>
#include <ctime>

class GeneradorAleatorios {
public:
	GeneradorAleatorios();
	
	/**
	 * Método que devuelve un número aleatorio entre 0 y max
	 * @return número aleatorio
	 */
	int genera(int max);
};

#endif

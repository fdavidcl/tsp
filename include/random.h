#include <cstdlib>
#include <ctime>

class GeneradorAleatorios {
	double minimo, maximo;
public:
	GeneradorAleatorios(double min, double max);
	
	/**
	 * Método que devuelve un número aleatorio
	 * @return número aleatorio
	 */
	double Genera();
};

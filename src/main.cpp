/*
 * El problema del viajante de comercio (TSP)
 *
 * Asignatura:   Metodologia de la Programacion (1º DGIIM)
 *
 * Autores:      Oscar Bermudez Garrido y Francisco David Charte Luque
 */

#include <stdlib.h>
#include <iostream>
#include "LectorArchivos.h"
#include "Ciudad.h"
#include "Recorrido.h"
#include "Problema.h"
#include "Heuristica.h"

using namespace std;

int main(int argc, char *argv[]){
   // Comprobamos que se han introducido dos argumentos,
   // en caso contrario informamos al usuario
	if (argc > 1) {
	   // Obtenemos los datos del archivo y creamos el objeto
	   // de Problema
	   LectorArchivos lector;
	   
	   if (lector.comprueba_existencia(argv[1])) {
	      Problema instancia(lector.lee(argv[1]));
	      Heuristica estrategia;
	      
	      // Creamos un objeto de Recorrido a partir de la solucion
	      // que proporcione el objeto de Heuristica
	      Recorrido solucion(estrategia.vecino_mas_cercano(instancia));
	      
	      int num_ciudades = solucion.consulta_cantidad();
	      
	      // Mostramos por salida el camino y el coste asociado
	      cout << "# TSP: El problema del viajante de comercio" << endl;
	      cout << "# Utilice plot.sh para generar un grafico con la solucion" << endl << "# Recorrido:" << endl;
	      cout << solucion << endl;
	      cout << "# Coste del recorrido: " << solucion.calcula_coste() << endl;
	   }
	   else {
	      cout << argv[0] << ": El archivo " << argv[1] << " no existe. Saliendo." << endl;
	      exit(3);
	   }
	}
	else {
	   cout << "Uso: " << argv[0] << " <NOMBRE_ARCHIVO>" << endl;
	   exit(1);
	}
}

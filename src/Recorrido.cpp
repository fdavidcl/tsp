/**
 * Implementacion de la clase Recorrido
 */

#include "Recorrido.h"

Recorrido::Recorrido()
   :cantidad(0), distancia_recorrida(0) {  
   camino = 0;
}

void Recorrido::agrega(Ciudad *nueva) {
   // Creamos el array de punteros que contenga
   // punteros a todas las ciudades almacenadas
   Ciudad** nuevo_camino = new Ciudad *[cantidad + 1];
   
   for (int i = 0; i < cantidad; i++)
      nuevo_camino[i] = camino[i];
   
   nuevo_camino[cantidad] = nueva;
   
   delete []camino;
   
   camino = nuevo_camino;
   
   // Anotamos lo que aumenta el coste del recorrido
   // al agregar la ciudad
   if (cantidad > 1)
      distancia_recorrida += nueva->calcula_distancia_con( camino[cantidad - 1] );
   
   cantidad++;
}

Ciudad * Recorrido::obten_ciudad(int indice) {
   return camino[indice];
}

int Recorrido::consulta_cantidad() {
   return cantidad;
}

double Recorrido::calcula_coste() {
   return distancia_recorrida;
}

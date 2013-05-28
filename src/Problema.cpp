/**
 * Implementacion de la clase Problema
 */

#include "Problema.h"

Problema::Problema(Ciudad** const ptr_lista, const int CANTIDAD)
   :NUM_CIUDADES(CANTIDAD) {
   mapa = ptr_lista;
   
   distancias = new double* [NUM_CIUDADES];
   
   // Creamos un array con la capacidad necesaria para una
   // matriz triangular, sin diagonal
   distancias[0] = new double [(NUM_CIUDADES*(NUM_CIUDADES-1))/2];
   
   for (int i = 0; i < NUM_CIUDADES - 1; i++) {
      // Saltamos tantos elementos como tenga la fila anterior
      distancias[i + 1] = distancias[i] + i;
   }
   
   // Almacenamos las distancias entre ciudades
   for (int i = 0; i < NUM_CIUDADES; i++) {
      for (int j = 0; j < i; j++) {
         distancias[i][j] = mapa[i]->calcula_distancia_con(mapa[j]);
      }
   }
}

int Problema::consulta_cantidad() {
   // Informamos de la cantidad de ciudades
   return NUM_CIUDADES;
}

double Problema::obten_distancia(int i, int j) {
   // Seleccionamos la distancia entre las dos ciudades
   // segun la relacion entre los indices y la devolvemos
   
   return i > j ? distancias[i][j] : i < j ? distancias[j][i] : 0;
}


Ciudad* Problema::operator[](int indice) {
   // Devolvemos el puntero a la ciudad pedida
   return mapa[indice];
}


Problema::~Problema(){
   delete[] distancias[0];
   delete[] distancias;
   
   for (int i = 0; i < NUM_CIUDADES; i++) {
      // Liberamos la memoria de cada puntero de los arrays
      delete mapa[i];
   }
   
   delete[] mapa;
}

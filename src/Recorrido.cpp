/**
 * Implementacion de la clase Recorrido
 */

#include "Recorrido.h"

Recorrido::Recorrido()
   :cantidad(0), distancia_recorrida(0) {  
   camino = 0;
}

Recorrido::Recorrido(const Recorrido& a_copiar) {
   cantidad = a_copiar.cantidad;
   distancia_recorrida = a_copiar.distancia_recorrida;
   camino = new Ciudad* [cantidad];
   
   for (int i = 0; i < cantidad; i++) {
      camino[i] = a_copiar.camino[i];
   }
}

Recorrido& Recorrido::operator+(Ciudad *nueva) const {
   // Creamos el array de punteros que contenga
   // punteros a todas las ciudades almacenadas
   Recorrido* devuelto = new Recorrido;
   devuelto->camino = new Ciudad* [cantidad + 1];
   
   for (int i = 0; i < cantidad; i++)
      devuelto->camino[i] = camino[i];
   
   devuelto->camino[cantidad] = nueva;
   
   // Anotamos lo que aumenta el coste del recorrido
   // al agregar la ciudad
   if (cantidad > 1)
      devuelto->distancia_recorrida = distancia_recorrida + nueva->calcula_distancia_con( camino[cantidad - 1] );
   
   devuelto->cantidad = cantidad + 1;
   
   return *devuelto;
}

Recorrido& Recorrido::operator=(Recorrido& a_asignar) {
   Ciudad** nuevo_camino = new Ciudad* [a_asignar.cantidad];
   
   for (int i = 0; i < a_asignar.cantidad; i++) {
      nuevo_camino[i] = a_asignar[i];
   }
   
   delete[] camino;
   camino = nuevo_camino;
   
   distancia_recorrida = a_asignar.distancia_recorrida;
   cantidad = a_asignar.cantidad;
   
   return *this;
}

Recorrido& Recorrido::operator+=(Ciudad* nueva) {
   return insertar(nueva, cantidad);
}
/*
Recorrido& Recorrido::insertar(Ciudad* nueva, int indice) {
   if (indice < 0) {
      indice = 0;
   } else if (indice > cantidad) {
      indice = cantidad;
   }
   
   cantidad++;
   
   Ciudad** nuevo_camino = new Ciudad* [cantidad];
   
   for (int i = 0; i < indice; i++)
      nuevo_camino[i] = camino[i];
   
   nuevo_camino[indice] = nueva;
   
   for (int i = indice + 1; i < cantidad; i++)
      nuevo_camino[i] = camino[i - 1];
   
   delete[] camino;
   camino = nuevo_camino;
   
   // Anotamos lo que aumenta el coste del recorrido al agregar la ciudad
   if (indice == 0) {
      distancia_recorrida += nueva->calcula_distancia_con(camino[1]);
   } else if (indice == cantidad - 1) {
      distancia_recorrida += nueva->calcula_distancia_con(camino[indice - 1]);
   } else {
      distancia_recorrida += nueva->calcula_distancia_con(camino[indice - 1])
         + nueva->calcula_distancia_con(camino[indice + 1])
         - camino[indice - 1]->calcula_distancia_con(camino[indice + 1]);
   }
   
   return *this;
}*/

Recorrido& Recorrido::insertar(Ciudad* nueva, int indice) {
   Ciudad** nuevo_camino = new Ciudad* [cantidad + 1];
   
   for (int i = 0; i < indice; i++) {
      nuevo_camino[i] = camino[i];
   }
   
   nuevo_camino[indice] = nueva;
   
   for (int i = indice + 1; i <= cantidad; i++) {
      nuevo_camino[i] = camino[i - 1];
   }
   
   delete[] camino;
   camino = nuevo_camino;
   
   cantidad++;
   
   distancia_recorrida = 0;
   
   for (int i = 0; i < cantidad - 1; i++) {
      distancia_recorrida += camino[i]->calcula_distancia_con(camino[i+1]);
   }
   
   return *this;
}

Recorrido& Recorrido::borrar(int indice) {
   if (indice < cantidad) {      
      for (int i = indice; i < cantidad - 1; i++) {
         camino[i] = camino[i+1];
      }
      
      cantidad--;
   }
   
   return *this;
}

Recorrido& Recorrido::intercambiar(int ind1, int ind2) {
   if (ind1 < cantidad && ind2 < cantidad) {
      Ciudad* temporal = camino[ind1];
      camino[ind1] = camino[ind2];
      camino[ind2] = temporal;
   }
   
   return *this;
}

Recorrido& Recorrido::transferir(int a_cambiar, int ind_nuevo) {
   if (a_cambiar < cantidad && ind_nuevo < cantidad) {
      insertar(camino[a_cambiar], ind_nuevo+1);
      borrar(a_cambiar > ind_nuevo ? a_cambiar + 1 : a_cambiar);
   }
   
   return *this;
}

Ciudad* Recorrido::operator[](int indice) const {
   return camino[indice];
}

int Recorrido::consulta_cantidad() {
   return cantidad;
}

double Recorrido::calcula_coste() {
   return distancia_recorrida;
}

std::ostream& operator<<(std::ostream& output, const Recorrido& a_mostrar) {
   for (int i = 0; i < a_mostrar.cantidad; i++) {
      output << a_mostrar.camino[i]->consulta_x() << "  " << a_mostrar.camino[i]->consulta_y() << std::endl;
   }
   
   return output;
}

Recorrido::~Recorrido() {
   // Liberamos el array
   delete[] camino;
}

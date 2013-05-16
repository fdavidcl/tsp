
#include "Heuristica.h"

Recorrido Heuristica::vecino_mas_cercano_desde(int indice) {
   Recorrido intento;
   int num_ciudades = a_resolver->consulta_cantidad();
   bool *visitadas = new bool[num_ciudades];
   double min_distancia;
   int mas_cercana, ultima_visitada = indice;
   
   // Inicializamos visitadas a falso
   for (int i = 0; i < num_ciudades; i++) {
      visitadas[i] = false;
   }
   
   // Agregamos la primera ciudad
   intento.agrega(a_resolver->obten_ciudad(indice));
   visitadas[indice] = true;
   
   // Para cada ciudad agregada, buscamos la mas cercana
   // de entre las no visitadas y la agregamos al recorrido
   for (int i = 1; i < num_ciudades; i++) {
      min_distancia = -1;
      
      for (int j = 0; j < num_ciudades; j++) {
         if (visitadas[j] == false && (min_distancia < 0 || a_resolver->obten_distancia(ultima_visitada, j) < min_distancia)) {
            min_distancia = a_resolver->obten_distancia(ultima_visitada, j);
            mas_cercana = j;
         }
      }
      
      intento.agrega(a_resolver->obten_ciudad(mas_cercana));
      visitadas[mas_cercana] = 1;
      ultima_visitada = mas_cercana;
   }
   
   intento.agrega(a_resolver->obten_ciudad(indice));
   
   // Liberamos memoria
   delete []visitadas;
   
   // Devolvemos el Recorrido construido
   return intento;
}

Recorrido Heuristica::soluciona(Problema *a_resolver) {
   this->a_resolver = a_resolver;
   Recorrido solucion;
   double min_coste = -1;
   int num_ciudades = a_resolver->consulta_cantidad();
   
   // Calculamos los recorridos que empiezan por distintas
   // ciudades y elegimos el de menor coste
   for (int i = 0; i < num_ciudades; i++) {
      Recorrido posible(vecino_mas_cercano_desde(i));
      
      if (min_coste < 0 || posible.calcula_coste() < min_coste) {
         min_coste = posible.calcula_coste();
         solucion = posible;
      }
   }
   
   // Devolvemos el mejor recorrido
   return solucion;
}

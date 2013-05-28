#include "Heuristica.h"

/*Recorrido Heuristica::vecino_mas_cercano_desde(int indice) {
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
   intento += (*a_resolver)[indice];
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
      
      intento += (*a_resolver)[mas_cercana];
      visitadas[mas_cercana] = 1;
      ultima_visitada = mas_cercana;
   }
   
   // Volvemos a la primera ciudad
   intento += (*a_resolver)[indice];
   
   // Liberamos memoria
   delete [] visitadas;
   
   // Devolvemos el Recorrido construido
   return intento;
}*/

Recorrido Heuristica::vecino_mas_cercano(Problema& a_resolver) {
   Recorrido solucion;
   double min_coste = -1;
   int num_ciudades = a_resolver.consulta_cantidad();
   bool *visitadas = new bool[num_ciudades];
   double min_distancia;
   int mas_cercana, ultima_visitada;
   
   // Calculamos los recorridos que empiezan por distintas
   // ciudades y elegimos el de menor coste
   for (int k = 0; k < num_ciudades; k++) {
      Recorrido intento;
      ultima_visitada = k;
      
      // Inicializamos visitadas a falso
      for (int i = 0; i < num_ciudades; i++) {
         visitadas[i] = false;
      }
      
      // Agregamos la primera ciudad
      intento += a_resolver[k];
      visitadas[k] = true;
      
      // Para cada ciudad agregada, buscamos la mas cercana
      // de entre las no visitadas y la agregamos al recorrido
      for (int i = 1; i < num_ciudades; i++) {
         min_distancia = -1;
         
         for (int j = 0; j < num_ciudades; j++) {
            if (visitadas[j] == false && (min_distancia < 0 || a_resolver.obten_distancia(ultima_visitada, j) < min_distancia)) {
               min_distancia = a_resolver.obten_distancia(ultima_visitada, j);
               mas_cercana = j;
            }
         }
         
         intento += a_resolver[mas_cercana];
         visitadas[mas_cercana] = 1;
         ultima_visitada = mas_cercana;
      }
      
      // Volvemos a la primera ciudad
      intento += a_resolver[k];
         
      if (min_coste < 0 || intento.calcula_coste() < min_coste) {
         min_coste = intento.calcula_coste();
         solucion = intento;
      }
   }
   
   // Liberamos memoria
   delete []visitadas;
   
   // Devolvemos el mejor recorrido
   return solucion;
}

Recorrido Heuristica::soluciona_con_insercion(Problema &a_resolver) {
   int num_ciudades = a_resolver.consulta_cantidad();
   int mas_oeste, mas_este = 0, mas_norte = 0;
   int mejor_ciudad, mejor_posicion;
   double min_dist, dist_intento;
   bool *visitadas = new bool[num_ciudades];
   Recorrido solucion, intento;
   
   this->a_resolver = &a_resolver;
   
   // Inicializamos visitadas a falso y buscamos las ciudades que están en los extremos del mapa
   for (int i = 0; i < num_ciudades; i++) {
      visitadas[i] = false;      

      if(a_resolver[i]->consulta_x() < a_resolver[mas_oeste]->consulta_x())
         mas_oeste = i;
      if(a_resolver[i]->consulta_x() > a_resolver[mas_este]->consulta_x())
         mas_este = i;
      if(a_resolver[i]->consulta_y() < a_resolver[mas_norte]->consulta_y() && i != mas_oeste && i != mas_este)
         mas_norte = i;
   }
   
   // Agregamos las primeras ciudades(la mas al norte, la mas al este y la mas al oeste)
   solucion += a_resolver[mas_oeste];
   solucion += a_resolver[mas_este];
   solucion += a_resolver[mas_norte];
   visitadas[mas_oeste] = true;
   visitadas[mas_este] = true;
   visitadas[mas_norte] = true;
   
   // Buscamos las mejores ciudades y sus mejores posiciones para añadirlas al recorrido
   while(solucion.consulta_cantidad() < num_ciudades){
      min_dist = -1;

      //Podría ir como un método o dos, distintos
      for(int i = 0; i < num_ciudades; i++){
         if(!visitadas[i]){
            for(int pos_intento= 0; pos_intento < solucion.consulta_cantidad(); pos_intento++){
               //Lo copiamos para que no se modifique solucion
               intento = solucion;

               dist_intento = intento.insertar(a_resolver[i], pos_intento).calcula_coste();

               if(min_dist < 0 || dist_intento < min_dist){
                  min_dist = dist_intento;
                  mejor_ciudad = i;
                  mejor_posicion = pos_intento;
               }
            }
         }         
      }

      solucion.insertar(a_resolver[mejor_ciudad], mejor_posicion);
      visitadas[mejor_ciudad] = true;      
   }

   solucion += a_resolver[mas_oeste];

   // Devolvemos el mejor recorrido
   return solucion;
}

Recorrido Heuristica::evolucion(Problema& a_resolver) {
   int num_ciudades = a_resolver.consulta_cantidad();
}

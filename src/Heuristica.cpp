
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
   delete []visitadas;
   
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

Recorrido& Heuristica::genera_recorrido_aleatorio(Problema& ciudades) {
   int tope = ciudades.consulta_cantidad();
   GeneradorAleatorios random;
   bool* visitadas = new bool[tope];
   int indice, max = tope;
   Recorrido* nuevo = new Recorrido;
   
   for (int i = 0; i < tope; i++) {
      indice = random.genera(max);
      
      for (int k = 0; k < tope; k++) {
         visitadas[k] ? indice++ : 0;
      }
      
      *nuevo += ciudades[indice];
      visitadas[indice] = true;
      max--;
   }
   
   delete[] visitadas;
   
   return *nuevo;
}

/*
Recorrido Heuristica::genera_mutacion(Recorrido& actual) {
   Recorrido nuevo(actual);
}*/

Recorrido Heuristica::evolucion(Problema& a_resolver) {
   Recorrido solucion;
   int num_ciudades = a_resolver.consulta_cantidad();
   GeneradorAleatorios random;
   Recorrido intento;
   int g = num_ciudades, e = num_ciudades*1000;
   int swap_a, swap_b;
   
   int menor_coste = -1;
   
   // Primero generamos un recorrido aleatorio lo mejor posible
   for (int i = 0; i < g; i++) {
      intento = genera_recorrido_aleatorio(a_resolver);
      
      if (intento.calcula_coste() < menor_coste || menor_coste == -1) {
         menor_coste = intento.calcula_coste();
         solucion = intento;
      }
   }
   
   // Ahora realizamos "mutaciones" sobre el recorrido, para 
   // tratar de mejorarlo
   // Una generacion consta de g recorridos, y se realiza una
   // evolucion con e generaciones
   
   for (int i = 0; i < e; i++) {
      swap_a = random.genera(num_ciudades);
      swap_b = random.genera(num_ciudades);
      
      if (intento.calcula_coste() < menor_coste || menor_coste == -1) {
         menor_coste = intento.calcula_coste();
         solucion = intento;
      }
   }
}

   #include "Heuristica.h"

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

Recorrido Heuristica::insercion(Problema& a_resolver) {
   int num_ciudades = a_resolver.consulta_cantidad();
   int primera=0, segunda=0, tercera=0;
   bool* visitadas = new bool[num_ciudades];
   Recorrido triangulo;
   
   // Inicializamos visitadas a falso y buscamos las ciudades que estan en los extremos del mapa
   for (int i = 0; i < num_ciudades; i++) {
      visitadas[i] = false;

   // La que esta mas a la izquierda
      if (a_resolver[i]->consulta_x() < a_resolver[primera]->consulta_x())
         primera = i;
      // La que esta mas a la derecha
      if (a_resolver[i]->consulta_x() > a_resolver[segunda]->consulta_x())
         segunda = i;
   }

   // La que esta mas abajo
   for (int i = 0; i < num_ciudades; i++) {
      if (a_resolver[i]->consulta_y() < a_resolver[tercera]->consulta_y() && i != primera && i != segunda)
         tercera = i;
   }
   
   // Agregamos las primeras ciudades
   triangulo += a_resolver[primera];
   triangulo += a_resolver[segunda];
   triangulo += a_resolver[tercera];
   visitadas[primera] = true;
   visitadas[segunda] = true;
   visitadas[tercera] = true;

   Recorrido solucion(insercion_completa(a_resolver, triangulo, visitadas));
   
   // Liberamos memoria
   delete[] visitadas;

   // Devolvemos el mejor recorrido
   return solucion;
}
   
Recorrido Heuristica::insercion_completa(Problema& a_resolver, Recorrido parcial, bool* visitadas) {
   int num_ciudades = a_resolver.consulta_cantidad();
   int mejor_ciudad, mejor_posicion;
   double min_dist, dist_intento;
   Recorrido solucion(parcial), intento;
   
   // Buscamos las mejores ciudades y sus mejores posiciones para agregarlas al recorrido
   for (int k = solucion.consulta_cantidad(); k < num_ciudades; k++) {
      min_dist = -1;
      
      for (int i = 0; i < num_ciudades; i++) {
         if (!visitadas[i]) {
            for (int pos_intento = 0; pos_intento < solucion.consulta_cantidad(); pos_intento++) {
               // Lo copiamos para que no se modifique solucion
               intento = solucion;

               dist_intento = (intento.insertar(a_resolver[i], pos_intento)+=intento[0]).calcula_coste();

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

   // Agregamos la primera ciudad para cerrar el ciclo
   solucion += solucion[0];

   // Devolvemos el mejor recorrido
   return solucion;
}

Recorrido Heuristica::comparacion(Problema& a_resolver) {
   // Declaracion de variables
   Recorrido mejor_solucion;
   int num_ciudades = a_resolver.consulta_cantidad(),
      ciudades_abajo,
      ciudades_arriba;
   double mas_baja = -1,
      mas_alta = -1,
      menor_coste = -1;
   int proxima;
   double a, b, x, y, tope_prm = 10, avance_prm = 0.5;
   
   // Reservamos memoria para almacenar las ciudades visitadas,
   // las que hallaremos como extremos de la recta divisoria
   // y las operaciones sobre las coordenadas
   bool* visitadas = new bool[num_ciudades];
   
   Ciudad** extremos = new Ciudad* [2];
   
   double* operaciones = new double[num_ciudades];
   
   // Distintos parametros se adaptan a distintos mapas. Mediante
   // estos bucles encontramos los mejores para la instancia dada
   for (double param1 = 0; param1 <= tope_prm; param1 += avance_prm) {
      for (double param2 = 0; param2 <= tope_prm; param2 += avance_prm) {
         Recorrido solucion, abajo, arriba;
         
         // Por un lado establecemos cada Ciudad como no visitada.
         // Además, calculamos las operaciones de acuerdo con los parametros
         // establecidos y a la vez hallamos los dos extremos de la recta
         // divisoria del mapa
         for (int i = 0; i < num_ciudades; i++) {
            visitadas[i] = false;
            
            x = a_resolver[i]->consulta_x();
            y = a_resolver[i]->consulta_y();
            operaciones[i] = param1 * (x + y) * (y / x) - param2 * (x - y) * (x / y);
            
            if (operaciones[i] < mas_baja || mas_baja < 0) {
               mas_baja = operaciones[i];
               extremos[0] = a_resolver[i];
            }
            
            if (operaciones[i] > mas_alta || mas_alta < 0) {
               mas_alta = operaciones[i];
               extremos[1] = a_resolver[i];
            }
         }
         
         // Calculamos los coeficientes de la recta y = ax+b
         a = (extremos[1]->consulta_y() - extremos[0]->consulta_y())/(extremos[1]->consulta_x() - extremos[0]->consulta_x());
         b = extremos[0]->consulta_y() - extremos[0]->consulta_x() * a;
         
         // Ordenando las operaciones de menor a mayor, generamos dos recorridos:
         // uno que pasa por debajo de la recta (desde el extremo inferior al superior),
         // y otro que va por encima (del extremo superior de vuelta al inferior), cerrando
         // el recorrido
         for (int k = 0; k < num_ciudades; k++) {
            mas_baja = -1;
            
            for (int i = 0; i < num_ciudades; i++) {
               if (!visitadas[i] && (operaciones[i] <= mas_baja || mas_baja < 0)) {
                  mas_baja = operaciones[i];
                  proxima = i;
               }
            }
            
            if (a_resolver[proxima]->consulta_y() <= a*a_resolver[proxima]->consulta_x()+b) {
               abajo += a_resolver[proxima];
            } else {
               arriba += a_resolver[proxima];
            }
            
            visitadas[proxima] = true;
         }
         
         // Generamos el recorrido completo
         ciudades_abajo = abajo.consulta_cantidad();
         ciudades_arriba = arriba.consulta_cantidad();
         
         for (int i = 0; i < ciudades_abajo; i++) {
            solucion += abajo[i];
         }
         
         for (int i = 0; i < ciudades_arriba; i++) {
            solucion += arriba[ciudades_arriba - i - 1];
         }
         
         solucion += extremos[0];
         
         // Comparamos el coste de este recorrido con el mejor ya generado
         if (solucion.calcula_coste() < menor_coste || menor_coste < 0) {
            menor_coste = solucion.calcula_coste();
            mejor_solucion = solucion;
         }
      }
   }
   
   // Liberamos memoria
   delete[] visitadas;
   delete[] operaciones;
   delete[] extremos;
   
   // Devolvemos la solucion
   return mejor_solucion;
}


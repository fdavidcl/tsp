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


Recorrido Heuristica::insercion(Problema &a_resolver) {
   int num_ciudades = a_resolver.consulta_cantidad();
   int mas_oeste = 0, mas_este = 0, mas_norte = 0;
   /*int mas_noroeste = 0, mas_noreste = 0, mas_sur = 0;
   double a, b;*/
   int mejor_ciudad, mejor_posicion;
   double min_dist= -1, dist_intento;
   bool *visitadas = new bool[num_ciudades];
   Recorrido solucion, intento;
   
   //this->a_resolver = &a_resolver;
   
   // Inicializamos visitadas a falso y buscamos las ciudades que están en los extremos del mapa
   for (int i = 0; i < num_ciudades; i++) {
      visitadas[i] = false;      

      
      /*if((a_resolver[i]->consulta_x()/(a_resolver[i]->consulta_y()+1)) < a)
         mas_noroeste = i;
         a = a_resolver[i]->consulta_x()/(a_resolver[i]->consulta_y()+1);
      if(pow(a_resolver[i]->consulta_x(),2)+pow(a_resolver[i]->consulta_y(),2) < b)
         mas_noreste = i;
         b = (a_resolver[i]->consulta_x(),2)+pow(a_resolver[i]->consulta_y(),2);
      if(a_resolver[i]->consulta_y() > a_resolver[mas_sur]->consulta_y())
         mas_sur = i;

      // Agregamos las primeras ciudades(la mas al norte, la mas al este y la mas al oeste)
      solucion += a_resolver[mas_noroeste];
      solucion += a_resolver[mas_noreste];
      solucion += a_resolver[mas_sur];
      visitadas[mas_noroeste] = true;
      visitadas[mas_noreste] = true;
      visitadas[mas_sur] = true;
*/
      if(a_resolver[i]->consulta_x() < a_resolver[mas_oeste]->consulta_x())
         mas_oeste = i;
      if(a_resolver[i]->consulta_x() > a_resolver[mas_este]->consulta_x())
         mas_este = i;
   }

   //Esto es complicado de explicar, si lo ponemos en el otro bucle, puede ser que la ciudad mas 
   //al norte de todo el mapa sea la mas al oeste(o al este) de las anteriores pero no del mapa,
   //luego no se registraria como la mas al norte(en pr1002.tsp ocurre)
   for (int i = 0; i < num_ciudades; i++) {
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
   for(int k = solucion.consulta_cantidad(); k < num_ciudades; k++){
      min_dist = -1;

      //Podría ir como un método o dos, distintos
      for(int i = 0; i < num_ciudades; i++){
         if(!visitadas[i]){
            for(int pos_intento = 0; pos_intento < solucion.consulta_cantidad(); pos_intento++){
               //Lo copiamos para que no se modifique solucion
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

   //Añadimos la primera ciudad para cerrar el ciclo
   solucion+=solucion[0];

   // Liberamos memoria
   delete[] visitadas;

   // Devolvemos el mejor recorrido
   return solucion;
}


Recorrido& Heuristica::genera_recorrido_aleatorio(Problema& ciudades) {
   int tope = ciudades.consulta_cantidad();
   //GeneradorAleatorios random;
   bool* visitadas = new bool[tope];
   int indice, max = tope;
   Recorrido* nuevo = new Recorrido;
   Ciudad* primera = 0;
   
   for (int i = 0; i < tope; i++)
      visitadas[i] = false;
   
   for (int i = 0; i < tope; i++) {
      indice = int(max*(rand()/(RAND_MAX+1.0)));
      
      for (int k = 0; k <= indice; k++) {
         visitadas[k] ? indice++ : 0;
      }
      
      if (primera == 0)
         primera = ciudades[indice];
      
      *nuevo += ciudades[indice];
      visitadas[indice] = true;
      max--;
   }
   
   *nuevo += primera;
   
   delete[] visitadas;
   
   return *nuevo;
}

Recorrido Heuristica::evolucion(Problema& a_resolver) {
   Recorrido solucion;
   int num_ciudades = a_resolver.consulta_cantidad();
   //GeneradorAleatorios random;
   Recorrido intento;//(vecino_mas_cercano(a_resolver)), nuevo;
   int g = 10000, e = 100000000/num_ciudades/num_ciudades, c = num_ciudades/10;
   int swap_a, swap_b;
   srand(time(0));
   
   int menor_coste = -1;
   solucion = intento;
   //srand(time(0));
   
   // Primero generamos un recorrido aleatorio lo mejor posible
   for (int i = 0; i < g; i++) {
      intento = genera_recorrido_aleatorio(a_resolver);
      
      if (intento.calcula_coste() < menor_coste || menor_coste == -1) {
         menor_coste = intento.calcula_coste();
         solucion = intento;
      }
   }
   
   //intento = ;
   
   // Ahora realizamos "mutaciones" sobre el recorrido, para 
   // tratar de mejorarlo
   // Una generacion consta de g recorridos, y se realiza una
   // evolucion con e generaciones
   
   /** Version 1: Vamos modificando solucion constantemente **/
   for (int i = 0; i < e; i++) {
      Recorrido copia(intento);
      
      for (int j = 0; j < c; j++) {
         //swap_b = int(5*(rand()/(RAND_MAX+1.0)));
         swap_a = int((num_ciudades-swap_b)*(rand()/(RAND_MAX+1.0)));
         swap_b = int(num_ciudades*(rand()/(RAND_MAX+1.0)));
         //swap_b = swap_a + swap_b;
         
         intento.intercambiar(swap_a, swap_b);
      }
      
      if (intento.calcula_coste() < menor_coste || menor_coste == -1) {
         menor_coste = intento.calcula_coste();
         solucion = intento;
      } else {
         intento = copia;
      }
   }
   
   /** Version 2: modificamos solucion tras cada generacion /
   for (int i = 0; i < e; i++) {
      for (int k = 0; k < g; k++) {
         swap_a = int(num_ciudades*(rand()/(RAND_MAX+1.0)));
         swap_b = int(num_ciudades*(rand()/(RAND_MAX+1.0)));
         
         nuevo = intento;
         nuevo.intercambiar(swap_a, swap_b);
         
         if (nuevo.calcula_coste() < menor_coste || menor_coste == -1) {
            menor_coste = nuevo.calcula_coste();
            solucion = nuevo;
         }
      }
      
      intento = solucion;
   }**/
   
   /** Version 3: Tratamos de hacer mutaciones no aleatorias /
   for (int m = 0; m < e; m++) {
      for (int i = 0; i < num_ciudades; i++) {
         for (int j = 0; j < num_ciudades; j++) {
            if (intento.intercambiar(i, j).calcula_coste() < menor_coste || menor_coste == -1) {
               menor_coste = intento.calcula_coste();
               solucion = intento;
            }
            else {
               intento.intercambiar(i, j);
            }
         }
      }
   }*/
   
   return solucion;
}

Recorrido Heuristica::suma(Problema& a_resolver) {
   Recorrido mejor_solucion;
   int num_ciudades = a_resolver.consulta_cantidad(),
      ciudades_abajo,
      ciudades_arriba;
   double mas_baja = -1,
      mas_alta = -1,
      menor_coste = -1;
   int proxima;
   double a, b, x, y;
   
   bool* visitadas = new bool[num_ciudades];
   
   Ciudad** extremos = new Ciudad* [2];
   
   double* sumas = new double[num_ciudades];
   
   for (double prm = 0; prm <= 5; prm += 0.1) {
      Recorrido solucion, abajo, arriba;
      
      for (int i = 0; i < num_ciudades; i++) {
         x = a_resolver[i]->consulta_x();
         y = a_resolver[i]->consulta_y();
         sumas[i] = prm * (x + y) * (y / x) - (5 - prm) * (x - y) * (x / y);
         visitadas[i] = false;
         
         if (sumas[i] < mas_baja || mas_baja < 0) {
            mas_baja = sumas[i];
            extremos[0] = a_resolver[i];
         }
         
         if (sumas[i] > mas_alta || mas_alta < 0) {
            mas_alta = sumas[i];
            extremos[1] = a_resolver[i];
         }
      }
      
      // Calculamos los coeficientes de la recta y = ax+b
      a = (extremos[1]->consulta_y() - extremos[0]->consulta_y())/(extremos[1]->consulta_x() - extremos[0]->consulta_x());
      b = extremos[0]->consulta_y() - extremos[0]->consulta_x() * a;
      
      for (int k = 0; k < num_ciudades; k++) {
         mas_baja = -1;
         
         for (int i = 0; i < num_ciudades; i++) {
            if (!visitadas[i] && (sumas[i] <= mas_baja || mas_baja < 0)) {
               mas_baja = sumas[i];
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
      
      ciudades_abajo = abajo.consulta_cantidad();
      ciudades_arriba = arriba.consulta_cantidad();
      
      //std::cout << num_ciudades << " " << ciudades_abajo + ciudades_arriba << std::endl;
      
      //std::cout << "ABAJO" << std::endl;
      for (int i = 0; i < ciudades_abajo; i++) {
         solucion += abajo[i];
         //std::cout << abajo[i]->consulta_x() << " " << abajo[i]->consulta_y() << "  ";
      }
      
      //std::cout << "ARRIBA" << std::endl;
      
      for (int i = 0; i < ciudades_arriba; i++) {
         solucion += arriba[ciudades_arriba - i - 1];
         //std::cout << arriba[ciudades_arriba - i - 1]->consulta_x() << " " << arriba[ciudades_arriba - i - 1]->consulta_y() << "  ";
      }
      
      solucion += extremos[0];
      
      //std::cout << solucion.calcula_coste() << std::endl;
      
      if (solucion.calcula_coste() < menor_coste || menor_coste < 0) {
         menor_coste = solucion.calcula_coste();
         mejor_solucion = solucion;
      }
   }
   
   delete[] visitadas;
   delete[] sumas;
   delete[] extremos;
   
   return mejor_solucion;
}


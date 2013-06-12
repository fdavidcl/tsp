/**
 * ## El problema del viajante de comercio (TSP) ampliado
 *********
 * **Asignatura** Metodologia de la Programacion (1º DGIIM)
 *********
 * **Autores** Oscar Bermudez Garrido y Francisco David Charte Luque
 *********
 */
#ifndef HEURISTICA
#define HEURISTICA
#include "Recorrido.h"
#include "Problema.h"

/**
 * ### Clase Heuristica
 * Se responsabiliza de recibir objetos
 * de la clase Problema y, mediante la estrategia utilizada,
 * devolver un objeto de la clase Recorrido con una solucion
 * adecuada a cada uno.
 */

class Heuristica {
   /**
    * Dato miembro que almacena un puntero al problema que ha de ser
    * resulto por Heuristica
    */
   Problema* a_resolver;
   
   /**
    * Este metodo toma el objeto de la clase Problema, y un recorrido
    * incompleto (y las ciudades visitadas) y devuelve la
    * mejor solucion obtenida por la estrategia de insercion
    * @param *a_resolver Puntero a un Problema
    * @param parcial Recorrido que no pasa por todas las ciudades
    * @param *visitadas Puntero a las ciudades ya visitadas
    * @return Recorrido que soluciona el problema
    */
   Recorrido insercion_completa(Problema &a_resolver, Recorrido parcial, bool *visitadas);

public:
   /**
    * Este metodo toma el objeto de la clase Problema y devuelve la
    * mejor solucion obtenida por la estrategia del vecino mas cercano
    * @param *a_resolver Puntero a un Problema
    * @return Recorrido que soluciona el problema
    */
   Recorrido vecino_mas_cercano(Problema& a_resolver);

   /**
    * Este metodo toma el objeto de la clase Problema y devuelve la
    * mejor solucion obtenida por la estrategia de insercion
    * @param *a_resolver Puntero a un Problema
    * @return Recorrido que soluciona el problema
    */
   Recorrido insercion(Problema &a_resolver);
   
   /**
    * Esta heuristica trata de generar un camino lo mas adecuado
    * posible simplemente realizando operaciones aritmeticas y de
    * comparacion sobre las coordenadas de cada nodo (ciudad) a
    * visitar.
    * @param *a_resolver Puntero a un Problema
    * @return Recorrido que soluciona el problema
    */
   Recorrido comparacion(Problema& a_resolver);
};

#endif

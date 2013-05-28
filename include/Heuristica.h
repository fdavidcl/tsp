/**
 * ## El problema del viajante de comercio (TSP)
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
#include "Aleatorio.h"

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
    * Este metodo obtiene el recorrido para, empezando por una ciudad
    * dada y pasando por la ciudad mas cercana (no visitada) en cada
    * paso, pasar por todas las ciudades y volver a la ciudad de inicio
    * @param indice Indice de la ciudad de inicio
    * @return Objeto de Recorrido que se ha construido
    */ 
    
   
   Recorrido& genera_recorrido_aleatorio(Problema&);
   //Recorrido genera_mutacion(Recorrido& actual);
public:
   /**
    * Este metodo toma el objeto de la clase Problema y devuelve la
    * mejor solucion obtenida por la estrategia del vecino mas cercano
    * @param *a_resolver Puntero a un Problema
    * @return Recorrido que soluciona el problema
    */
   Recorrido vecino_mas_cercano(Problema& a_resolver);
   Recorrido evolucion(Problema& a_resolver);
};

#endif

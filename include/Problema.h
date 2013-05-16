/**
 * ## El problema del viajante de comercio (TSP)
 *********
 * **Asignatura** Metodologia de la Programacion (1º DGIIM)
 *********
 * **Autores** Oscar Bermudez Garrido y Francisco David Charte Luque
 *********
 */
#ifndef PROBLEMA
#define PROBLEMA
#include "Ciudad.h"

/**
 * ### Clase Problema
 * Contiene la descripcion de una instancia
 * del TSP, es decir, sus ciudades y distancias
 */

class Problema {
   /**
    * Contiene la cantidad de ciudades a considerar en el problema
    */
   const int NUM_CIUDADES;
   
   /**
    * Lista de punteros a objetos de la clase Ciudad
    */
   Ciudad ** mapa;
   
   /**
    * Matriz triangular inferior que contiene las distancias entre
    * los diferentes objetos de la clase Ciudad
    */
   double ** distancias;
   
public:
   /**
    * El constructor se encarga de inicializar mapa y de calcular las
    * distancias para almacenarlas en la matriz de distancias
    * @param **ptr_lista Lista de punteros a Ciudad
    * @param NUM_CIUDADES Cantidad de ciudades del problema
    */
   Problema(Ciudad ** const ptr_lista, const int NUM_CIUDADES);
   
   /**
    * Informa de la cantidad de ciudades del problema
    * @return Cantidad de ciudades
    */
   int consulta_cantidad();
   
   /**
    * Metodo que extrae de la matriz de distancias la correspondiente
    * a las ciudades cuyos indices se pasaron como parametros
    * @param i Indice de la primera ciudad
    * @param j Indice de la segunda ciudad
    * @return Distancia entre las ciudades
    */
   double obten_distancia(int i, int j);
   
   /**
    * Metodo que devuelve un puntero a la Ciudad correspondiente
    * al indice dado
    * @param indice Indice de la ciudad pedida
    * @return Puntero al objeto de Ciudad correspondiente
    */
   Ciudad * obten_ciudad(int indice);
};

#endif

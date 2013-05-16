/**
 * ## El problema del viajante de comercio (TSP)
 *********
 * **Asignatura** Metodologia de la Programacion (1º DGIIM)
 *********
 * **Autores** Oscar Bermudez Garrido y Francisco David Charte Luque
 *********
 */
#ifndef RECORRIDO
#define RECORRIDO
#include "Ciudad.h"

/**
 * ### Clase Recorrido
 * Permite almacenar un posible
 * recorrido de las ciudades, no necesariamente todas
 * las de la instancia.
 */

class Recorrido {
   /**
    * Dato miembro que almacena una lista de punteros
    * a objetos de Ciudad
    */
   Ciudad **camino;
   
   /**
    * Contiene la cantidad actual de objetos de la
    * clase Ciudad en el camino
    */
   int cantidad;
   
   /**
    * Resultado del calculo de la distancia total recorrida
    */
   double distancia_recorrida;
   
public:
   /**
    * El constructor se encarga de preparar los datos
    * miembro antes de su uso
    */
   Recorrido();
   
   /**
    * Este metodo agrega un nuevo puntero a un objeto
    * de la clase Ciudad al camino 
    * @param *nueva Puntero a Ciudad
    */
   void agrega(Ciudad *nueva);
   
   /**
    * Metodo que devuelve un puntero a un objeto de
    * la clase Ciudad segun el indice dado
    * @param indice Posicion de la ciudad a devolver
    * @return Puntero a la Ciudad correspondiente
    */
   Ciudad * obten_ciudad(int indice);
   
   /**
    * Informa de la cantidad de ciudades almacenadas
    * @return Cantidad de ciudades
    */
   int consulta_cantidad();
   
   /**
    * Metodo que devuelve la distancia total del recorrido
    * @return Distancia recorrida
    */
   double calcula_coste();
};

#endif

/**
 * ## El problema del viajante de comercio (TSP) ampliado
 *********
 * **Asignatura** Metodologia de la Programacion (1º DGIIM)
 *********
 * **Autores** Oscar Bermudez Garrido y Francisco David Charte Luque
 *********
 */
#ifndef CIUDAD
#define CIUDAD
#include <cmath>

/**
 * ### Clase Ciudad
 * Representa un punto geografico con unas coordenadas concretas
 */
class Ciudad{
private:
   /**
    * Almacena la primera coordenada
    */
   double coord_x;
   /**
    * Almacena la segunda coordenada
    */
   double coord_y;
public:
   /**
    * El constructor se encarga de inicializar los datos miembro
    * @param set_x Valor de la primera coordenada
    * @param set_y Valor de la segunda coordenada
    */
   Ciudad(double set_x, double set_y);
   
   /**
    * Informa de la primera coordenada
    * @return Devuelve el valor de la primera coordenada
    */
   double consulta_x();
   
   /**
    * Informa de la segunda coordenada
    * @return Devuelve el valor de la segunda coordenada
    */
   double consulta_y();
   
   /**
    * Metodo que calcula la distancia de otro objeto de la clase Ciudad a este objeto
    * @param *otra Puntero a otro objeto de la clase Ciudad
    * @return Devuelve la distancia a la ciudad dada como parametro
    */
   double calcula_distancia_con(Ciudad *otra);
};
#endif


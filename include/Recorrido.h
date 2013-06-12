/**
 * ## El problema del viajante de comercio (TSP) ampliado
 *********
 * **Asignatura** Metodologia de la Programacion (1º DGIIM)
 *********
 * **Autores** Oscar Bermudez Garrido y Francisco David Charte Luque
 *********
 */
#ifndef RECORRIDO
#define RECORRIDO
#include <ostream>
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
   Ciudad** camino;
   
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
    * El constructor de copia genera un recorrido identico
    * al recibido
    * @param a_copiar Recorrido a copiar
    */
   Recorrido(const Recorrido& a_copiar);
   
   /**
    * Sobrecarga del operador + que permite agregar una nueva
    * Ciudad al Recorrido actual, devolviendo una referencia
    * al nuevo Recorrido (sin modificar el actual)
    * @param nueva Ciudad a agregar
    * @return Referencia al Recorrido resultado
    */
   Recorrido& operator+(Ciudad* nueva) const;
   
   /**
    * Sobrecarga del operador = que permite asignar un Recorrido
    * al actual
    * @param a_asignar Recorrido a copiar
    * @return Referencia al Recorrido resultado
    */
   Recorrido& operator=(Recorrido& a_asignar);
   
   /**
    * Sobrecarga del operador += que permite agregar una nueva
    * Ciudad al Recorrido actual modificando el actual
    * @param nueva Ciudad a agregar
    * @return Referencia al Recorrido resultado
    */
   Recorrido& operator+=(Ciudad* nueva);
   
   /**
    * Metodo que inserta un puntero a una Ciudad en la posicion
    * especificada
    * @param nueva Ciudad a agregar
    * @param indice Posicion en la que se quiere insertar
    * @return Referencia al Recorrido resultado
    */
   Recorrido& insertar(Ciudad* nueva, int indice);
   
   /**
    * Metodo que devuelve un puntero a un objeto de
    * la clase Ciudad segun el indice dado. No permite la
    * modificacion del recorrido de esta forma.
    * @param indice Posicion de la ciudad a devolver
    * @return Puntero a la Ciudad correspondiente
    */
   Ciudad* operator[](int indice) const;
   
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
   
   /**
    * Sobrecarga del operador << que permite la salida por 
    * pantalla de las coordenadas del Recorrido, de forma
    * sencilla.
    ********
    * Declarada funcion amiga de la clase para proporcionar
    * acceso a los datos miembro
    */
   friend std::ostream& operator<<(std::ostream& output, const Recorrido& a_mostrar); 
   
   /**
    * Destructor de la clase Recorrido
    */
   ~Recorrido();
};


#endif

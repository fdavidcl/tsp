/**
 * ## El problema del viajante de comercio (TSP) ampliado
 *********
 * **Asignatura** Metodologia de la Programacion (1º DGIIM)
 *********
 * **Autores** Oscar Bermudez Garrido y Francisco David Charte Luque
 *********
 */
#ifndef GESTORARCHIVOS
#define GESTORARCHIVOS
#include <iostream>
#include <fstream>
#include <string>
#include "Ciudad.h"
#include "Problema.h"
#include "Recorrido.h"

using namespace std;

/**
 * ### Clase LectorArchivos
 * Se encarga de extraer los datos necesarios de
 * un archivo y proporcionar un objeto de la clase Problema
 */
class GestorArchivos {
   /**
    * Array de punteros a objetos de Ciudad
    */
   Ciudad** conjunto_ciudades;
   
   /**
    * Cantidad de ciudades
    */
   int num_ciudades;
public:
   /**
    * Metodo que crea un objeto de la clase Problema a partir de los
    * datos que hay en el archivo cuyo nombre fue pasado como parametro
    * @param nombre_archivo Nombre del archivo en el que estan los datos
    * @return Objeto de la clase Problema
    */
   Problema lee(char* nombre_archivo);
   
   /**
    * Metodo que crea un archivo y escribe sobre el los datos del recorrido
    * pasado como argumento
    * @param nombre_archivo Nombre del archivo a generar
    * @param solucion Recorrido a escribir
    */
   void escribe(const char* nombre_archivo, Recorrido& solucion);
   
   /**
    * Este metodo trata de acceder a un archivo dado y devuelve true en
    * caso de que exista y sea correcto, false en caso contrario
    * @param nombre Nombre del archivo a examinar
    * @return Validez del archivo
    */
   bool comprueba_existencia(char* nombre);
};

#endif

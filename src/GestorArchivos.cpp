#include "GestorArchivos.h"

Problema GestorArchivos::lee(char* nombre_archivo){
   int idCiudad,num_ciudades;
   double x,y;
   ifstream archi;
   string head;
   archi.open(nombre_archivo);
   
   // Leemos la palabra DIMENSION
   archi >> head;
   // Leemos el numero de ciudades
   archi >> num_ciudades;
   
   conjunto_ciudades = new Ciudad* [num_ciudades];

   // Leemos coordenadas con un bucle.
   // Son 3 valores en cada fila
   for(int i = 0; i < num_ciudades; i++){
      archi >> idCiudad;
      archi >> x;
      archi >> y;
      
      conjunto_ciudades[i] = new Ciudad(x, y);
   }
   
   return Problema(conjunto_ciudades, num_ciudades);
}

bool GestorArchivos::comprueba_existencia(char* nombre) {
   ifstream archi(nombre);
   
   // El metodo good nos informa de la existencia del archivo
   return archi.good();
}

void GestorArchivos::escribe(const char* nombre_archivo, Recorrido& solucion) {
   // Abrimos el archivo
   ofstream salida;
   salida.open(nombre_archivo);
   
   // Guardamos los datos del recorrido: coste y coordenadas
   salida << "# TSP: El problema del viajante de comercio" << endl;
   salida << "# Utilice gentables.sh para generar tablas de resultados y graficos" << endl;
   salida << "# Coste del recorrido: " << solucion.calcula_coste() << endl << "# Recorrido:" << endl;
   salida << solucion << endl;
}


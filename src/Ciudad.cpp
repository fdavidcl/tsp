#include "Ciudad.h"

Ciudad::Ciudad(double set_x, double set_y){
   // Inicializamos los datos miembro
   coord_x = set_x;
   coord_y = set_y;
};

double Ciudad::consulta_x(){
   return coord_x;
};

double Ciudad::consulta_y(){
   return coord_y;
};

double Ciudad::calcula_distancia_con(Ciudad *otra){
   // Calculamos y devolvemos la distancia entre las dos ciudades
   return sqrt(pow(otra->consulta_x() - coord_x, 2) + pow(otra->consulta_y() - coord_y,2)); 
};

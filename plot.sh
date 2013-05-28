# Oscar Bermudez y F. David Charte
#!/bin/bash
# Titulo: plot.sh
# Descripcion: Facilita la generacion de un grafico con la solucion
# que proporcione bin/tsp para el problema del viajante de comercio

PROGRAMA='bin/tsp'
SCRIPT="script_`date +%s%N`.gnup"

# Comprobamos que se ha introducido el argumento del archivo
[[ $# -eq 1 ]] && {
   # Comprobamos que se ha compilado el programa
   [[ -f $PROGRAMA ]] && {
      # Comprobamos que la instancia del TSP existe 
      [[ -f $1 ]] && {
         
         # Ejecutamos el programa
         $PROGRAMA $1 > "$1.data" && {
            # Generamos el script de Gnuplot
            printf 'set xlabel "Coordenada X"
               set ylabel "Coordenada Y"
               set title "Problema TSP : ".basename
               unset key
               set grid
               set terminal png
               set output basename.".png"
               plot basename.".data" with linespoints' > $SCRIPT;
            
            # Generamos el grafico y lo abrimos
            gnuplot -e "basename='$1'" $SCRIPT && {
               rm $SCRIPT;
               echo "$0: Gráfico generado en $1.png"
               (xdg-open "$1.png" &> /dev/null)&
            } || echo "$0: gnuplot ha fallado."
         };
      } || {
         echo "$0: $1 no existe o no es un archivo regular.";
         exit 3;
      }
   } || {
      echo "$0: Antes de generar un gráfico necesita compilar el código (make)";
      exit 2;
   }
} || {
   echo "$0: No se ha proporcionado una instancia del TSP";
   echo "Uso: $0 <NOMBRE_ARCHIVO>";
   exit 1;
}

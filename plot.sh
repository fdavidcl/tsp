# Oscar Bermudez y F. David Charte
#!/bin/bash
# Titulo: plot.sh
# Descripcion: Facilita la generacion de un grafico con la solucion
# que proporcione bin/tsp para el problema del viajante de comercio

PROGRAMA='bin/tsp'
SCRIPT="script_`date +%s%N`.gnup"

# Comprobamos que se ha introducido el argumento del archivo
[[ $# -eq 2 ]] && {
   # Comprobamos que se ha compilado el programa
   [[ -f $PROGRAMA ]] && {
      # Comprobamos que la instancia del TSP existe 
      [[ -f $1 ]] && {
         
         # Ejecutamos el programa
         $PROGRAMA $1 $2 > "$1.data" && {
            # Generamos el script de Gnuplot
            printf 'set xlabel "Coordenada X"
               set ylabel "Coordenada Y"
               set title "Problema TSP : ".basename
               unset key
               set grid
               set terminal png
               set output basename.".png"
               plot basename.".data" with linespoints' > $SCRIPT
            
            gnuplot -e "basename='$1'" $SCRIPT && {
               rm $SCRIPT;
               echo "$0: Gráfico generado en $1.png"
               (xdg-open "$1.png" 2> /dev/null)&
            } || echo "$0: gnuplot ha fallado."
         } || {
            echo "$0: El programa ha fallado."
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
   echo "$0: Número incorrecto de argumentos";
   echo "Uso: $0 <NOMBRE_ARCHIVO> <NUM_HEURISTICA>";
   exit 1;
}

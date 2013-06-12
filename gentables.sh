#!/bin/bash
# Titulo: gentables.sh
# Descripcion: Genera tablas de resultados en formato HTML
# Autores: Oscar Bermudez y F. David Charte

# Declaramos las variables
MAPAS=(small10 berlin52 eil101 KROA200 a280 pr1002)
OFILE="tablas.html"
SCRIPT="script_`date +%s%N`.gnup"
PROG="bin/tspAmpliado"
HEUR="1
2
3"

# Comprobamos que existe el programa y las instancias
[[ -d instancias ]] || {
   echo "$0: No se encuentra el directorio instancias/. Abortando."
   exit -1
}

[[ -e $PROG ]] || {
   echo "$0: No se encuentra el ejecutable. Abortando."
   exit -2
}

# Preparamos el documento HTML
printf "
<!DOCTYPE html>
<html>
   <head>
      <title>TSP: Tablas de resultados</title>
      <style>
         body {
            margin: 0;
            font-family: sans-serif;
            background: #555;
         }
         article {
            min-width: 1100px;
            max-width: 1900px;
            margin: 0 60px;
            padding: 20px 40px 40px;
            background: #f0f0f0;
            box-shadow: 0 0 40px rgba(0,0,0,0.3);
         }
         h2 {
            text-align: center;
            font-weight: normal;
         }
         table {
            border-collapse: collapse;
            border: 2px solid silver;
            margin: 0 auto;
         }
         tr {
            border: 1px solid #c0c0c0;
         }
         tr:first-child {
            font-weight: bold;
            color: #555;
         }
         td {
            padding: 3px 6px;
            min-width: 100px;
         }
         tr:first-child td {
            border: 1px solid #c0c0c0;
         }
         td:first-child {
            font-weight: bold;
            border: 1px solid #c0c0c0;
         }
         td.best {
            background: #aeb;
         }
         td img {
            max-width: 300px;
         }
         .coste:before, .tiempo:before {
            content: 'Coste';
            text-transform: uppercase;
            color: #888;
            font-size: 12px;
            margin-right: .4em;
         }
         .tiempo:before {
            content: 'Tiempo';
            margin-left: .6em;
         }
      </style>
      <script>
         window.onload = function() {
            var rows = document.querySelectorAll('table tr');
            
            for (var i = 1; i < rows.length; i++) {
               var cells = rows[i].querySelectorAll('td .coste');
               var best = 0;
               
               for (var j = 1; j < cells.length; j++) {
                  if (parseFloat(cells[j].textContent) < parseFloat(cells[best].textContent)) {
                     best = j;
                  }
               }
               
               cells[best].parentNode.classList.add('best');
            }
         };
      </script>
   </head>
   <body>
      <article>
         <h2>TSP: Tablas de resultados</h2>
         <table>
            <tr>
               <td>Mapas</td>
               <td>Vecino m&aacute;s cercano</td>
               <td>Inserci&oacute;n m&aacute;s econ&oacute;mica</td>
               <td>Comparaci&oacute;n de coordenadas</td>
            </tr>" > $OFILE

# Ejecutamos cada heuristica sobre cada mapa, generando
# el codigo HTML adecuado
for MAP in ${MAPAS[*]}
do
   printf "
            <tr>
               <td>$MAP</td>" >> $OFILE
   
   for H in $HEUR; do
      printf "
               <td>" >> $OFILE
      printf "Generando solución $H para el mapa $MAP"
      TIMEB=`date +"%s.%N"`
      RESULT=`$PROG instancias/$MAP.tsp $H`
      TIME=`echo "\`date +\"%s.%N\"\` - $TIMEB" | bc | cut -c-7`
      printf "<span class='coste'>$RESULT</span> <span class='tiempo'>$TIME</span> <br />" >> $OFILE
      printf "   [ $RESULT / $TIME ]\n"
      
      # Generamos el grafico con gnuplot
      ARCH="instancias/$MAP.tsp.$H"
      
      printf 'set xlabel "Coordenada X"
         set ylabel "Coordenada Y"
         unset key
         set grid
         set terminal png
         set output basename.".png"
         plot basename.".data" with linespoints' > $SCRIPT
      
      gnuplot -e "basename='$ARCH'" $SCRIPT && {
         rm $SCRIPT;
         echo "Gráfico generado en $ARCH.png"
      } || echo "$0: gnuplot ha fallado."
      
      printf " <img src=\"$ARCH.png\" />" >> $OFILE
      printf "</td>" >> $OFILE
   done
   
   printf "
            </tr>" >> $OFILE
done

printf "
      </article>
   </body>
</html>" >> $OFILE

echo "Terminada la generación. Abriendo el archivo $OFILE"
(xdg-open $OFILE &> /dev/null)&

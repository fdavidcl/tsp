#!/bin/bash
# Titulo: gentables.sh
# Descripcion: Genera tablas de resultados en formato HTML
# Autores: Oscar Bermudez y F. David Charte

MAPAS=(small10 berlin52 eil101 KROA200 a280)
OFILE="resultado.html"
SCRIPT="script_`date +%s%N`.gnup"
PROG="bin/tsp"
HEUR="1
2
3"

[[ -d instancias ]] || {
   echo "$0: No se encuentra el directorio instancias/. Abortando."
   exit -1
}

[[ -e $PROG ]] || {
   echo "$0: No se encuentra el ejecutable. Abortando."
   exit -2
}

[[ -f $OFILE ]] && printf "" > $OFILE
touch $OFILE

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
            min-width: 900px;
            max-width: 1900px;
            margin: 0 40px;
            padding: 20px 40px 40px;
            background: #f0f0f0;
            box-shadow: 0 0 40px rgba(0,0,0,0.3);
         }
         table {
            border-collapse: collapse;
            border: 2px solid silver;
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
         }
         td.best {
            background: #cfc;
         }
         td img {
            max-width: 300px;
         }
      </style>
      <script>
         window.onload = function() {
            var rows = document.querySelectorAll('table tr');
            
            for (var i = 1; i < rows.length; i++) {
               var cells = rows[i].querySelectorAll('td');
               var best = 1;
               
               for (var j = 1; j < cells.length; j++) {
                  if (parseFloat(cells[j].textContent) < parseFloat(cells[best].textContent)) {
                     best = j;
                  }
               }
               
               cells[best].classList.add('best');
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
            </tr>" >> $OFILE

for MAP in ${MAPAS[*]}
do
   printf "
            <tr>
               <td>$MAP</td>" >> $OFILE
   
   for H in $HEUR; do
      printf "
               <td>" >> $OFILE
      printf "Generando solución $H para el mapa $MAP"
      RESULT=`$PROG instancias/$MAP.tsp $H`
      printf "$RESULT <br />" >> $OFILE
      printf "   [ $RESULT ]\n"
      
      ARCH="instancias/$MAP.tsp.$H"
      
      printf 'set xlabel "Coordenada X"
         set ylabel "Coordenada Y"
         set title "Problema TSP : ".basename
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

(xdg-open $OFILE &> /dev/null)&

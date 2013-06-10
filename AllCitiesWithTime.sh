#! /bin/bash

cities=(small10.tsp berlin52.tsp eil101.tsp KROA200.TSP a280.tsp pr1002.tsp)

rm ./resultado.txt
touch ./resultado.txt

date +%T
 
for city in ${cities[*]}
do
   ./plot.sh ./instancias/$city && date +%T && ./bin/tsp ./instancias/$city >> ./resultado.txt && date +%T
done


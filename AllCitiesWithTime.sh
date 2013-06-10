#! /bin/bash

cities=(small10.tsp berlin52.tsp eil101.tsp KROA200.TSP a280.tsp pr1002.tsp)

rm ./resultado.txt
touch ./resultado.txt

date +%T
 
for city in ${cities[*]}
do
   for i in {1,2,3}
   do
      ./plot.sh ./instancias/$city $i
      date +%T
      ./bin/tsp ./instancias/$city >> ./resultado.txt $i 
      echo "./bin/tsp ./instancias/$city" $i  
      date +%T
   done
done


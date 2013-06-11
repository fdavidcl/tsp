BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src

all: $(OBJ)/Ciudad.o $(OBJ)/Heuristica.o $(OBJ)/LectorArchivos.o $(OBJ)/main.o $(OBJ)/Problema.o $(OBJ)/Recorrido.o
	g++ -o $(BIN)/tsp $^ && cat README
$(OBJ)/Ciudad.o: $(SRC)/Ciudad.cpp $(INCLUDE)/Ciudad.h
	g++ -o $@ -c $< -I$(INCLUDE)
$(OBJ)/Heuristica.o: $(SRC)/Heuristica.cpp $(INCLUDE)/Heuristica.h
	g++ -o $@ -c $< -I$(INCLUDE)
$(OBJ)/LectorArchivos.o: $(SRC)/LectorArchivos.cpp $(INCLUDE)/LectorArchivos.h
	g++ -o $@ -c $< -I$(INCLUDE)
$(OBJ)/main.o: $(SRC)/main.cpp 
	g++ -o $@ -c $< -I$(INCLUDE)
$(OBJ)/Problema.o: $(SRC)/Problema.cpp $(INCLUDE)/Problema.h
	g++ -o $@ -c $< -I$(INCLUDE)
$(OBJ)/Recorrido.o: $(SRC)/Recorrido.cpp $(INCLUDE)/Recorrido.h
	g++ -o $@ -c $< -I$(INCLUDE)
clean:
	rm $(OBJ)/*.o
documentacion:
	doxygen $(DOC)/doxys/Doxyfile

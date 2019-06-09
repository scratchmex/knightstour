#Makefile Generico Simple 
# Especifica el compilador que quiero usar:
CC = g++
# Banderas que se dan como opcion al compilador:
CC_FLAGS = -Wall -std=c++11 -pedantic

#Path
EXEC_PATH = %tmp%
# Nombre del ejecutable 
EXEC = knightstour
# Para tomar todos los archivos cpp del directorio:
SRC = $(wildcard *.cpp)
# Toma solo los archivos cpp que aqui se indican:
#Object path
OBJ_PATH=o/

# Especifica que los nombres de los objetos sera igual al nombre de cada archivo cpp
OBJ = $(SRC:%.cpp=$(OBJ_PATH)%.o)

# Este es el target que Makefile toma por default 
all: $(EXEC)
	echo @$(OBJ)

run: $(EXEC)
	$(EXEC)

# Reglas para generar el ejecutable usando los OBJ como dependencia 
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regla para generar los archivos objeto utilizando los archivos cpp
%.o : %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
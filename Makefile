#Makefile Generico Simple 
#notdir spaces safe
s? = $(subst $(empty) ,?,$1)
?s = $(subst ?, ,$1)
notdirx = $(call ?s,$(notdir $(call s?,$1)))

#Paths
BUILD_PATH=build
BIN_PATH = $(BUILD_PATH)/bin
SRC_PATH = .

# Nombre del ejecutable 
BIN_NAME = $(call notdirx,$(CURDIR)).out
# Para tomar todos los archivos cpp del directorio:
SRCS = $(wildcard $(SRC_PATH)/*.cpp)
# Especifica que los nombres de los objetos sera igual al nombre de cada archivo cpp
OBJS = $(SRCS:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)

# Especifica el compilador que quiero usar:
CC = g++
# Banderas que se dan como opcion al compilador:
CC_FLAGS = -Wall -std=c++11 -pedantic -g

#recipes
# Este es el target que Makefile toma por default
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making all... $(OBJS)"
	@echo "Making symlink: $(BIN_NAME) -> $@"
	@ln -fs $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

dirs:
	@echo "Creating directories"
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(BIN_PATH)

clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@rm -f $(BIN_NAME)
	@echo "Deleting directories"
	@rm -r $(BIN_PATH)
	@rm -r $(BUILD_PATH)

run: $(BIN_PATH)/$(BIN_NAME)
	$(BIN_PATH)/$(BIN_NAME)

# Reglas para generar el ejecutable usando los OBJS como dependencia 
$(BIN_PATH)/$(BIN_NAME):$(OBJS)
	@echo "Making: $(BIN_NAME)"
	$(CC) $(OBJS) -o $@

# Regla para generar los archivos objeto utilizando los archivos cpp
$(BUILD_PATH)/%.o:$(SRC_PATH)/%.cpp
	@echo "Compiling: $< -> $@"
	$(CC) -c $(CC_FLAGS) $< -o $@
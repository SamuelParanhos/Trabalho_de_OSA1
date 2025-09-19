# Arquivo principal 
MAIN := main

# Pastas
INCLUDES := includes
SRC := src

# Objetos a compilar
OBJECTS := $(MAIN).o $(SRC)/Registro.o $(SRC)/Buffer.o $(SRC)/Arquivo.o

# Flags do compilador
FLAGS := -Wall -Wextra -std=c++17 -pedantic-errors -I$(INCLUDES)

# Debug
DEBUG := -g

# Bibliotecas extras
MATH := -lm

# Compilador
CC := g++

# ajustando alguns parâmetros/comandos ao sistema operacional
ifeq ($(OS), Windows_NT)
OUTPUTMAIN := $(MAIN).exe
else
OUTPUTMAIN := $(MAIN).out
endif

# Alvo principal
all: $(OUTPUTMAIN)
	@echo Compiling 'all' complete!

# Linkagem final
$(OUTPUTMAIN): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(OUTPUTMAIN) $(MATH)

# Regras de compilação dos objetos
$(MAIN).o: $(MAIN).cpp $(INCLUDES)/Arquivo.hpp $(INCLUDES)/Registro.hpp $(INCLUDES)/Buffer.hpp
	$(CC) $(FLAGS) -c $(MAIN).cpp -o $(MAIN).o

$(SRC)/Registro.o: $(SRC)/Registro.cpp $(INCLUDES)/Registro.hpp
	$(CC) $(FLAGS) -c $(SRC)/Registro.cpp -o $(SRC)/Registro.o

$(SRC)/Buffer.o: $(SRC)/Buffer.cpp $(INCLUDES)/Buffer.hpp $(INCLUDES)/Registro.hpp $(INCLUDES)/Arquivo.hpp
	$(CC) $(FLAGS) -c $(SRC)/Buffer.cpp -o $(SRC)/Buffer.o

$(SRC)/Arquivo.o: $(SRC)/Arquivo.cpp $(INCLUDES)/Arquivo.hpp $(INCLUDES)/Registro.hpp $(INCLUDES)/Buffer.hpp
	$(CC) $(FLAGS) -c $(SRC)/Arquivo.cpp -o $(SRC)/Arquivo.o

# Limpeza
clean:
	rm -rf $(OBJECTS)
	rm -rf $(OUTPUTMAIN)
	@echo Cleanup complete!!!

# Executar
run: all
	./$(OUTPUTMAIN)
	@echo Executing 'all' complete!!!

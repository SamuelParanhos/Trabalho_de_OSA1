
MAIN := main

# Pastas
INCLUDES := includes
SRC := src

# Objetos a compilar
OBJECTS := $(MAIN).o $(SRC)/Buffer.o $(SRC)/RegistroAluno.o

# Flags do compilador
FLAGS := -Wall -Wextra -std=c++17 -pedantic-errors -I$(INCLUDES)

# Debug
DEBUG := -g

# Bibliotecas extras
MATH := -lm

# Compilador
CC := g++

# Ajuste para SO
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
$(MAIN).o: $(MAIN).cpp $(INCLUDES)/Arquivo.hpp $(INCLUDES)/Buffer.hpp $(INCLUDES)/Registro.hpp $(INCLUDES)/RegistroAluno.hpp
	$(CC) $(FLAGS) -c $(MAIN).cpp -o $(MAIN).o

$(SRC)/Buffer.o: $(SRC)/Buffer.cpp $(INCLUDES)/Buffer.hpp $(INCLUDES)/Registro.hpp $(INCLUDES)/Arquivo.hpp
	$(CC) $(FLAGS) -c $(SRC)/Buffer.cpp -o $(SRC)/Buffer.o

$(SRC)/RegistroAluno.o: $(SRC)/RegistroAluno.cpp $(INCLUDES)/RegistroAluno.hpp $(INCLUDES)/Registro.hpp
	$(CC) $(FLAGS) -c $(SRC)/RegistroAluno.cpp -o $(SRC)/RegistroAluno.o

# Limpeza
clean:
	rm -rf $(OBJECTS)
	rm -rf $(OUTPUTMAIN)
	@echo Cleanup complete!!!

# Executar
run: all
	./$(OUTPUTMAIN)
	@echo Executing 'all' complete!!!

# Nome do executável
EXEC = Grafos-1-Parking-lot

# Pasta com os arquivos-fonte
SRC_DIR = Projeto

# Busca automaticamente todos os .cpp dentro da pasta Projeto/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Regra principal
all: $(EXEC)

$(EXEC): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC)

# Limpa o executável
clean:
	rm -f $(EXEC)

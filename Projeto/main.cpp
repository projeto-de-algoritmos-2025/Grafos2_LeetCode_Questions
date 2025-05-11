#include "estacionamento.hpp"

void inicializarGrafo();
void executarMenu();

int main() {
    inicializarLojas();
    inicializarVagas();
    inicializarGrafo();
    executarMenu();
    return 0;
}
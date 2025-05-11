#ifndef ESTACIONAMENTO_HPP
#define ESTACIONAMENTO_HPP

#include <vector>
#include <string>
using namespace std;

struct Vaga {
    int id;
    bool ocupada;
    string nomeLoja;  
};

extern vector<string> lojas;
extern vector<Vaga> vagas;

void inicializarLojas();
void inicializarVagas();
void mostrarMenu();
void mostrarLojas();
void gerarGrafoCaminho(const vector<int>& caminho, int vaga);

#endif
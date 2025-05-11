#include "estacionamento.hpp"
#include <iostream>

vector<string> lojas;
vector<Vaga> vagas(18);

void inicializarLojas() {
    lojas = {"Renner", "C&A", "Sodiê", "Chiquinho", "Ciatoy", "Samgung"};
}

void inicializarVagas() {
    int vagaPorLoja = 3;
    for (int i = 0; i < 18; ++i) {
        vagas[i].id = i + 1;
        vagas[i].ocupada = false;
        vagas[i].nomeLoja = lojas[i / vagaPorLoja]; 
    }
}

void mostrarMenu() {
    cout << "\n===== SISTEMA DE ESTACIONAMENTO =====\n";
    cout << "1. Escolher loja e estacionar\n";
    cout << "2. Ver mapa de estacionamento\n";
    cout << "3. Ver desenho do estacionamento vazio\n";
    cout << "4. Sair\n";
    cout << "======================================\n";
    cout << "ESCOLHA UMA OPÇÃO (1-4): ";
}

void mostrarLojas() {
    cout << "\n======================================\n";
    cout << "LOJAS DISPONÍVEIS:\n";
    for (size_t i = 0; i < lojas.size(); ++i) {
        cout << i + 1 << ". " << lojas[i] << endl;
    }
    cout << "======================================\n";
    cout << "ESCOLHA UMA LOJA (1-6): ";
}
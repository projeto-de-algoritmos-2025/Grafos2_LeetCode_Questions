#include "estacionamento.hpp"
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>   
#include <cstdlib>   
#include <iostream>  
#include <sstream> 

using namespace std;

vector<vector<int>> adjacencia(18);

void inicializarGrafo() {
    // Configuração do fluxo direcional do estacionamento
    adjacencia[0].push_back(1);   // Vaga 1 → Vaga 2
    adjacencia[1].push_back(2);   // Vaga 2 → Vaga 3
    adjacencia[2].push_back(3);   // Vaga 3 → Vaga 4
    adjacencia[3].push_back(4);   // Vaga 4 → Vaga 5
    adjacencia[3].push_back(6);   // Vaga 4 → Vaga 7
    adjacencia[4].push_back(5);   // Vaga 5 → Vaga 6
    adjacencia[4].push_back(7);   // Vaga 5 → Vaga 8
    adjacencia[5].push_back(6);   // Vaga 6 → Vaga 7
    adjacencia[5].push_back(8);   // Vaga 6 → Vaga 9
    adjacencia[6].push_back(7);   // Vaga 7 → Vaga 8
    adjacencia[7].push_back(8);   // Vaga 8 → Vaga 9

    adjacencia[8].push_back(11);  // Vaga 9 → Vaga 12
    adjacencia[11].push_back(10); // Vaga 12 → Vaga 11
    adjacencia[11].push_back(17); // Vaga 12 → Vaga 18
    adjacencia[10].push_back(9);  // Vaga 11 → Vaga 10
    adjacencia[10].push_back(16); // Vaga 11 → Vaga 17
    adjacencia[9].push_back(15);  // Vaga 10 → Vaga 16
    adjacencia[17].push_back(16); // Vaga 18 → Vaga 17
    adjacencia[16].push_back(15); // Vaga 17 → Vaga 16
    adjacencia[15].push_back(14); // Vaga 16 → Vaga 15
    adjacencia[14].push_back(13); // Vaga 15 → Vaga 14
    adjacencia[13].push_back(12); // Vaga 14 → Vaga 12

    
    
}

pair<int, vector<int>> buscarVagaPorBFS(const vector<Vaga>& vagas, const string& nomeLojaDesejada) {
    vector<bool> visitado(18, false);
    queue<int> fila;
    unordered_map<int, int> predecessor;
    vector<int> caminho;

    fila.push(0); // Começa na Vaga 1
    visitado[0] = true;
    predecessor[0] = -1;

    int count_vagas_loja = 0;
    int vagaEncontrada = -1;

    while (!fila.empty()) {
        int vagaAtual = fila.front();
        fila.pop();

        if (!vagas[vagaAtual].ocupada) {
            if (vagas[vagaAtual].nomeLoja == nomeLojaDesejada) {
                vagaEncontrada = vagaAtual;
                break;
            } else if (count_vagas_loja >= 2) {
                vagaEncontrada = vagaAtual;
                break;
            }
        } else {
            if (vagas[vagaAtual].nomeLoja == nomeLojaDesejada) {
                count_vagas_loja++;
            }
        }

        for (int vizinho : adjacencia[vagaAtual]) {
            if (!visitado[vizinho]) {
                fila.push(vizinho);
                visitado[vizinho] = true;
                predecessor[vizinho] = vagaAtual;
            }
        }
    }

    if (vagaEncontrada != -1) {
        int v = vagaEncontrada;
        while (v != -1) {
            caminho.insert(caminho.begin(), v); 
            v = predecessor[v];
        }
    }

    return {vagaEncontrada, caminho};
}


pair<int, vector<int>> encontrarVagaProximaComBFS(const string& nomeLoja) {
    return buscarVagaPorBFS(vagas, nomeLoja);
}

void gerarGrafoCaminho(const vector<int>& caminho, int vaga) {
    stringstream nomeArquivo;
    nomeArquivo << "caminho_para_vaga_" << vaga << ".dot"; 
    string arquivoDot = nomeArquivo.str();

    ofstream dotFile(arquivoDot);
    dotFile << "digraph G {\n";
    dotFile << "  rankdir=LR;\n"; 
    dotFile << "  node [shape=circle, style=filled, fillcolor=lightblue];\n";

    for (size_t i = 0; i < caminho.size(); ++i) {
        dotFile << "  " << caminho[i] + 1 << ";\n";
        if (i < caminho.size() - 1) {
            dotFile << "  " << caminho[i] + 1 << " -> " << caminho[i + 1] + 1 << ";\n";
        }
    }

    dotFile << "}\n";
    dotFile.close();

    stringstream nomeImagem;
    nomeImagem << "caminho_para_vaga_" << vaga << ".png";  
    string arquivoPng = nomeImagem.str();

    string comando = "dot -Tpng " + arquivoDot + " -o " + arquivoPng;
    system(comando.c_str()); 

// Abre a imagem (Linux: xdg-open, Windows: start, Mac: open)
#ifdef _WIN32
    system(("start " + arquivoPng).c_str());
#elif __APPLE__
    system(("open " + arquivoPng).c_str());
#else
    system(("feh " + arquivoPng).c_str());
#endif
}
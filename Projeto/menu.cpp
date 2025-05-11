#include <iostream>
#include "estacionamento.hpp"
using namespace std;

extern void inicializarGrafo();
extern pair<int, vector<int>> encontrarVagaProximaComBFS(const string& nomeLoja);

void executarMenu() {
    int opcao;
    do {
        mostrarMenu();
        cin >> opcao;

        switch (opcao) {
            case 1: {
                mostrarLojas();
                int escolha;
                cin >> escolha;
                if (escolha >= 1 && escolha <= 6) {
                    string nomeLoja = lojas[escolha - 1];
                    pair<int, vector<int>> resultado = encontrarVagaProximaComBFS(nomeLoja);
                    int vaga = resultado.first;
                    if (vaga != -1) {
                        vagas[vaga].ocupada = true;
                        cout << "\nEstacione na vaga " << vagas[vaga].id
                             << " (próxima à loja " << nomeLoja << ")\n";

                        cout << "\nCaminho até a vaga: ";
                        for (int i : resultado.second) {
                            cout << (i + 1) << " "; 
                        }
                        cout << endl;
                        gerarGrafoCaminho(resultado.second, vagas[vaga].id);
                    } else {
                        cout << "\nNão há vagas disponíveis próximas à loja " << nomeLoja << endl;
                    }
                } else {
                    cout << "\nLoja inválida.\n";
                }
                break;
            }
            case 2: {
                cout << "\nMAPA DO ESTACIONAMENTO\n";
                cout << "-----------------------\n";
                for (const Vaga& v : vagas) {
                    cout << "Vaga " << v.id << " - "
                         << (v.ocupada ? "OCUPADA" : "LIVRE ")
                         << " (Loja: " << v.nomeLoja << ")\n";
                }
                break;
            }
            case 3:
                #ifdef _WIN32
                    system("start Desenho.png");
                #elif __APPLE__
                    system("open Desenho.png");
                #else
                    system("feh Desenho.png");
                #endif

            case 4:
                cout << "\nSaindo do sistema...\n";
                break;
            default:
                cout << "\nOpção inválida. Tente novamente.\n";
        }

    } while (opcao != 4);
}
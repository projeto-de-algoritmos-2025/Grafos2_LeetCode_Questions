class Solution {
public:
    // Verifica se a posição está nos limites
    bool ehValido(int linha, int coluna, int linhas, int colunas) {
        return linha >= 0 && coluna >= 0 && linha < linhas && coluna < colunas;
    }

    int deltaLinha[4] = {0,  0, 1, -1};
    int deltaColuna[4] = {1, -1, 0,  0};

    int minCost(vector<vector<int>>& grade) {
        int linhas = grade.size();
        int colunas = grade[0].size();

        // Matriz de distâncias
        vector<vector<int>> distancia(linhas, vector<int>(colunas, INT_MAX));

        // Min-Heap
        priority_queue<
            pair<int, pair<int, int>>, 
            vector<pair<int, pair<int, int>>>, 
            greater<pair<int, pair<int, int>>>>
        filaPrioridade;

        // Inicia no canto superior esquerdo com custo 0
        distancia[0][0] = 0;
        filaPrioridade.push({0, {0, 0}});

        // Dijkstra
        while (!filaPrioridade.empty()) {
            auto topo = filaPrioridade.top();
            filaPrioridade.pop();

            int custoAtual = topo.first;
            int linhaAtual = topo.second.first;
            int colunaAtual = topo.second.second;

            // Retorna o custo mínimo
            if (linhaAtual == linhas - 1 && colunaAtual == colunas - 1) {
                return custoAtual;
            }

            for (int indiceMovimento = 0; indiceMovimento < 4; indiceMovimento++) {
                int novaLinha = linhaAtual + deltaLinha[indiceMovimento];
                int novaColuna = colunaAtual + deltaColuna[indiceMovimento];

                if (ehValido(novaLinha, novaColuna, linhas, colunas)) {
                    int custoMovimento = (indiceMovimento + 1 == grade[linhaAtual][colunaAtual]) ? 0 : 1;
                    int novoCusto = custoAtual + custoMovimento;

                    if (distancia[novaLinha][novaColuna] > novoCusto) {
                        distancia[novaLinha][novaColuna] = novoCusto;
                        filaPrioridade.push({novoCusto, {novaLinha, novaColuna}});
                    }
                }
            }
        }

        return distancia[linhas - 1][colunas - 1];
    }
};

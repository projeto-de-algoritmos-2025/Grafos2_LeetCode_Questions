class Solution {
public:
    int reachableNodes(vector<vector<int>>& arestas, int movimentosMaximos, int totalNos) {
        // Lista de adjacência com pares (vizinho, custo)
        vector<vector<pair<int, int>>> grafo(totalNos);
        for (auto &aresta : arestas) {
            int origem = aresta[0], destino = aresta[1], subnos = aresta[2];
            grafo[origem].push_back({destino, subnos + 1});
            grafo[destino].push_back({origem, subnos + 1});
        }

        // Dijkstra: fila de prioridade (distância, nó)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
        vector<int> distancia(totalNos, INT_MAX);
        distancia[0] = 0;
        fila.push({0, 0});

        while (!fila.empty()) {
            auto [distAtual, noAtual] = fila.top();
            fila.pop();

            if (distAtual > distancia[noAtual]) continue;

            for (auto& [vizinho, custo] : grafo[noAtual]) {
                int novaDist = distAtual + custo;
                if (novaDist < distancia[vizinho]) {
                    distancia[vizinho] = novaDist;
                    fila.push({novaDist, vizinho});
                }
            }
        }

        int resposta = 0;
        // Contar nós originais alcançáveis
        for (auto &dist : distancia) {
            if (dist <= movimentosMaximos) resposta += 1;
        }

        // Contar subnós alcançáveis em cada aresta
        for (auto &aresta : arestas) {
            int origem = aresta[0], destino = aresta[1], subnos = aresta[2];
            int alcanceOrigem = max(0, movimentosMaximos - distancia[origem]);
            int alcanceDestino = max(0, movimentosMaximos - distancia[destino]);
            resposta += min(subnos, alcanceOrigem + alcanceDestino);
        }

        return resposta;
    }
};

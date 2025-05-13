class Solution {
public:
    // Calcula o menor caminho de um nó origem até todos os outros usando Dijkstra
    vector<int> menorCaminho(vector<vector<pair<int,long long>>>& grafo, int origem, int n) {
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> fila;
        vector<int> distancias(n, INT_MAX);
        vector<int> visitado(n, 0);
        distancias[origem] = 0;
        fila.push({0, origem});

        while(!fila.empty()) {
            int tamanho = fila.size();
            while(tamanho--) {
                long long pesoAtual = fila.top().first;
                int noAtual = fila.top().second;
                fila.pop();

                if(visitado[noAtual])
                    continue;

                for(auto adjacente : grafo[noAtual]) {
                    int proximoNo = adjacente.first;
                    long long pesoAresta = adjacente.second;

                    if(distancias[proximoNo] > pesoAtual + pesoAresta) {
                        distancias[proximoNo] = pesoAtual + pesoAresta;
                        fila.push({pesoAtual + pesoAresta, proximoNo});
                    }
                }

                visitado[noAtual] = 1;
            }
        }

        return distancias;
    }

    // Constrói o grafo como lista de adjacência a partir da lista de arestas
    vector<vector<pair<int,long long>>> criaGrafo(int n, vector<vector<int>>& arestas) {
        vector<vector<pair<int,long long>>> grafo(n);

        for(auto aresta : arestas) {
            grafo[aresta[0]].push_back({aresta[1], aresta[2]});
            grafo[aresta[1]].push_back({aresta[0], aresta[2]});
        }

        return grafo;
    }

    // Verifica quais arestas podem estar presentes em algum caminho mais curto entre 0 e n-1
    vector<bool> findAnswer(int n, vector<vector<int>>& arestas) {
        vector<vector<pair<int,long long>>> grafo = criaGrafo(n, arestas);

        // Menores distâncias a partir do início e do fim
        vector<int> doInicio = menorCaminho(grafo, 0, n);
        vector<int> doFim = menorCaminho(grafo, n - 1, n);         

        vector<bool> resposta(arestas.size(), false); 

        for(int i = 0 ; i < arestas.size() ; i++) {  
            long long distInicio = doInicio[arestas[i][0]];
            long long distFim = doFim[arestas[i][1]];
            long long pesoMeio = arestas[i][2];

            // Verifica se a aresta está em algum caminho mais curto possível
            if(distInicio + distFim + pesoMeio == doInicio[n - 1])
                resposta[i] = true;

            distInicio = doInicio[arestas[i][1]];
            distFim = doFim[arestas[i][0]];

            if(distInicio + distFim + pesoMeio == doInicio[n - 1])
                resposta[i] = true;
        }

        return resposta;
    }
};

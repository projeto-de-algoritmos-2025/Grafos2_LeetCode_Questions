#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int LARGE_VALUE = 2e9;
    typedef pair<long, long> P;

    long long dijkstra(vector<vector<int>>& edges, int n, int src, int dest) {
        // grafo excluindo as arestas -1
        unordered_map<long long, vector<pair<long long, long long>>> adj; // lista de adjacencia

        for(vector<int>& edge : edges) {
            if(edge[2] != -1) {
                int u  = edge[0];
                int v  = edge[1];
                int wt = edge[2];

                adj[u].push_back({v, wt});
                adj[v].push_back({u, wt});
            }
        }

        priority_queue<P, vector<P>, greater<P>> minHeap;
        vector<long long> distance(n, INT_MAX); // distance[i] = menor caminho do source até o i-ésimo nó

        distance[src] = 0;
        minHeap.push({0, src});

        while(!minHeap.empty()) {
            long long currDist = minHeap.top().first;
            long long currNode = minHeap.top().second;
            minHeap.pop();

            for(auto&[v, wt] : adj[currNode]) {
                if(distance[v] > currDist + wt) {
                    distance[v] = currDist + wt;
                    minHeap.push({distance[v], v});
                }
            }
        }

        return distance[dest];
    }

    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        long long currShortestDist = dijkstra(edges, n, source, destination);

        if(currShortestDist < target) {
            return {};
        }

        bool matchedTarget = (currShortestDist == target);

        for(vector<int>& edge : edges) {
            if(edge[2] == -1) {
                edge[2] = (matchedTarget == true) ? LARGE_VALUE : 1; // caso o menor caminho já seja o target

                if(matchedTarget != true) {
                    long long newShortestDist = dijkstra(edges, n, source, destination);

                    if(newShortestDist <= target) {
                        matchedTarget = true;
                        edge[2] += (target - newShortestDist);
                    }
                }
            }
        }

        if(matchedTarget == false) {
            return {};
        }
        return edges;
    }
};

// exemplo na main
int main() {
    Solution s;
    int n = 4, source = 2, destination = 3, target = 8;
    vector<vector<int>> edges = {
        {0,1,-1},
        {1,2,-1},
        {3,1,-1},
        {3,0,2},
        {0,2,5}
    };
    auto ans = s.modifiedGraphEdges(n, edges, source, destination, target);
    if (ans.empty())
        cout << "[]\n";
    else {
        cout << "[";
        for (int i = 0; i < ans.size(); ++i) {
            cout << "["<<ans[i][0]<<","<<ans[i][1]<<","<<ans[i][2]<<"]";
            if (i+1<ans.size()) cout << ",";
        }
        cout << "]\n";
    }
}

